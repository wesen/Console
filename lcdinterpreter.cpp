#include <QImage>
#include <QDebug>

#include "lcdinterpreter.h"
#include "vendor/lz4.h"
#include "vendor/qextserialport/src/qextserialport.h"
#include "vendor/qextserialport/src/qextserialenumerator.h"


#define CHECK_PORT_OPEN() { \
    if (port == NULL) { \
    emit(write(QString("Serial port has not been opened.\n"))); \
    return; \
    } \
}


LCDInterpreter::LCDInterpreter(QObject *parent) :
    Console::CommandInterpreter(parent),
    state(NONE),
    port(NULL)
{
    populateMetaMethods();
}

LCDInterpreter::~LCDInterpreter()
{

}

void LCDInterpreter::cmdKey()
{
    CHECK_PORT_OPEN();
    port->write("!K\n");

}

void LCDInterpreter::cmdInfo()
{
    CHECK_PORT_OPEN();
    port->write("!I\n");
}

void LCDInterpreter::cmdImage(QString fileName)
{
    CHECK_PORT_OPEN();
    QImage image(fileName);
    if ((image.width() != 800) ||
            (image.height() != 480)) {
        emit write(QString("Image has the wrong format, %1x%2 should be 800x480\n").arg(image.width()).arg(image.height()));
        return;
    }

    QByteArray data;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb pixel = image.pixel(x, y);
            data.append(qRed(pixel));
            data.append(qGreen(pixel));
            data.append(qBlue(pixel));
        }
    }
    const char *_data = data.constData();
    char output[data.size()];
    int len = LZ4_compress(_data, output, data.size());
    if (len <= 0) {
        emit write(QString("Could not lZ4 compress image\n"));
        return;
    }

    QByteArray d2;
    d2.append('!');
    d2.append('f');
    d2.append(len >> 24);
    d2.append(len >> 16);
    d2.append(len >> 8);
    d2.append(len >> 0);
    d2.append(output, len);
    d2.append('\n');
    port->write(d2);

}

void LCDInterpreter::cmdSetLed(int led, int red, int green)
{
    CHECK_PORT_OPEN();
    QByteArray data;
    data.append('!');
    data.append('E');
    leds[led] = (red & 0xF) << 4 | (green & 0xF);
    for (int i = 0; i < 16; i++)
    {
        data.append(leds[i]);
    }
    data.append('\n');
    port->write(data);
}

void LCDInterpreter::cmdOpen(QString device)
{
    if (port != NULL) {
        emit(write(QString("Close serial port first.\n")));
        return;
    }

    port = new QextSerialPort(device, QextSerialPort::EventDriven, this);
    connect(port, SIGNAL(readyRead()), this, SLOT(onBytesAvailable()));
    port->open(QIODevice::ReadWrite);
    state = NONE;
    cmdLength = 0;
    crc = 0;
    for (int i = 0; i < 16; i++) {
        leds[i] = 0;
    }
}

void LCDInterpreter::cmdList()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    int i = 0;
    foreach (QextPortInfo info, ports) {
        emit write(QString("%1) %2\n").arg(i).arg(info.portName));
        i++;
    }
}

void LCDInterpreter::cmdClose()
{
    CHECK_PORT_OPEN();

    port->close();
    delete port;
    port = NULL;

}

void LCDInterpreter::onBytesAvailable()
{
    CHECK_PORT_OPEN();

}

void LCDInterpreter::processBytes(QByteArray data)
{
    foreach(const char &c, data)
    {
        processByte((unsigned char)c);
    }
}

void LCDInterpreter::processByte(unsigned char c)
{
    switch (state) {
    case NONE:
    case CMD_BYTE:
        cmd = (LCD_COMMAND)c;
        state = CMD_LEN0;
        cmdLength = 0;
        break;

    case CMD_LEN0:
        cmdLength = (c << 24);
        state = CMD_LEN1;
        break;

    case CMD_LEN1:
        cmdLength |= (c << 16);
        state = CMD_LEN2;
        break;

    case CMD_LEN2:
        cmdLength |= (c << 8);
        state = CMD_LEN3;
        break;

    case CMD_LEN3:
        cmdLength |= c;
        data = QByteArray();
        state = CMD_DATA;
        break;

    case CMD_DATA:
        data.append(c);
        if (cmdLength-- == 0) {
            state = CMD_CRC;
        }
        break;

    case CMD_CRC:
        crc = c;
        state = NONE;
        emit commandReceived((unsigned char)cmd, data, crc);
        break;

    }
}

QString LCDInterpreter::CommandToString(LCD_COMMAND cmd)
{
    switch (cmd) {
    case GET_KEY_CMD:
        return "getKey";

    case KEY_INFO_CMD:
        return "keyInfo";

    case GET_INFO_CMD:
        return "getInfo";

    case SCREEN_INFO_CMD:
        return "screenInfo";

    case SET_SCREEN_CMD:
        return "setScreen";

    case SET_SCREEN_OK_CMD:
        return "setScreenOK";

    default:
        return "unknowNCmd";

    }
}

void LCDInterpreter::onCommandReceived(unsigned char cmd, const QByteArray &data, unsigned char crc)
{
    QString s;
    switch ((LCD_COMMAND)cmd)
    {
    case KEY_INFO_CMD:
        emit writeAsync(s.sprintf("key info received: %x %x\n", data[0], data[1]));
        break;

    case SCREEN_INFO_CMD:
        emit writeAsync("screen info\n");
        break;

    case SET_SCREEN_OK_CMD:
        emit writeAsync("set screen ok\n");

    default:
        emit writeAsync("received command " + CommandToString((LCD_COMMAND)cmd) + "\n");
        break;
    }
}
