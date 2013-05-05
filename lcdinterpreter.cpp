#include "lcdinterpreter.h"
#include "vendor/qextserialport/src/qextserialport.h"
#include "vendor/qextserialport/src/qextserialenumerator.h"


#define CHECK_PORT_OPEN() { \
    if (port == NULL) { \
    emit(write(QString("Serial port has not been opened."))); \
    return; \
    } \
}


LCDInterpreter::LCDInterpreter(QObject *parent) :
    Console::CommandInterpreter(parent),
    port(NULL),
    state(NONE)
{
    populateMetaMethods();
}

LCDInterpreter::~LCDInterpreter()
{

}

void LCDInterpreter::cmdKey()
{
    CHECK_PORT_OPEN();

}

void LCDInterpreter::cmdInfo()
{
    CHECK_PORT_OPEN();

}

void LCDInterpreter::cmdImage(QString image)
{
    CHECK_PORT_OPEN();

}

void LCDInterpreter::cmdOpen(QString device)
{

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
