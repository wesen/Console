#include <QImage>
#include <QDebug>

#include "lcdinterpreter.h"
#include "helpers.h"
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
    connect(this, SIGNAL(commandReceived(unsigned char,QByteArray,unsigned char)), this, SLOT(onCommandReceived(unsigned char,QByteArray,unsigned char)));
}

LCDInterpreter::~LCDInterpreter()
{

}

void LCDInterpreter::cmdKey()
{
    CHECK_PORT_OPEN();
    QByteArray data("!K\n");
    qDebug() << "write " << qHexdump(data);
    port->write(data);

}

void LCDInterpreter::cmdInfo()
{
    CHECK_PORT_OPEN();
    QByteArray data("!I\n");
    qDebug() << "write " << qHexdump(data);
    port->write(data);
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
            float red = qRed(pixel);
            float green = qGreen(pixel);
            float blue = qBlue(pixel);
            red /= 42.7;
            green /= 42.7;
            blue /= 42.7;
            int v = (int)red * 36 + (int)green * 6 + (int)blue;
//            qDebug() << "pixel " << pixel << " v " << (unsigned char)v;
            data.append((unsigned char)v);
        }
    }
    const char *_data = data.constData();
    char output[data.size()];
    int len = LZ4_compress(_data, output, data.size());
    if (len <= 0) {
        emit write(QString("Could not lZ4 compress image\n"));
        return;
    }
    qDebug() << "orig data " << qHexdump(data);
    qDebug() << "compressed " << data.size() << " bytes to " << len;

    QByteArray d2;
    d2.append('!');
    d2.append('F');
    d2.append(len >> 24);
    d2.append(len >> 16);
    d2.append(len >> 8);
    d2.append(len >> 0);
    d2.append(output, len);
    d2.append('\n');
    qDebug() << "write " << qHexdump(d2);
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
    qDebug() << "write " << qHexdump(data);
    port->write(data);
}

void LCDInterpreter::cmdOpen(QString device)
{
    if (port != NULL) {
        emit(write(QString("Close serial port first.\n")));
        return;
    }

    PortSettings settings = {
        BAUD115200,
        DATA_8,
        PAR_NONE,
        STOP_1,
        FLOW_OFF
    };
    port = new QextSerialPort(device, settings, QextSerialPort::EventDriven, this);
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
    processBytes(port->readAll());

}

void LCDInterpreter::processBytes(QByteArray data)
{
    qDebug() << "read\n" << qHexdump(data);
    foreach(const char &c, data)
    {
        processByte((unsigned char)c);
    }
}

void LCDInterpreter::processByte(unsigned char c)
{
//    qDebug() << "process " << c << " state " << state << "length " << cmdLength;
//    qDebug() << "data " << qHexdump(data);
    switch (state) {
    case NONE:
    case CMD_START:
        if (c == '!') {
            state = CMD_LEN0;
        }
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
    {
        unsigned char cmd = data[0];
        data.remove(0, 1);
        emit commandReceived(cmd, data, crc);
    }
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
    qDebug() << "command received " << CommandToString((LCD_COMMAND)cmd);
    QString s;
    switch ((LCD_COMMAND)cmd)
    {
    case KEY_INFO_CMD:
        emit writeAsync(s.sprintf("key info received: %x %x\n", (unsigned char )data[0], (unsigned char )data[1]));
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
