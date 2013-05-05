#ifndef LCDINTERPRETER_H
#define LCDINTERPRETER_H

#include <QObject>

#include "commandinterpreter.h"

class QextSerialPort;

class LCDInterpreter : public Console::CommandInterpreter
{
    Q_OBJECT
public:
    LCDInterpreter(QObject *parent = NULL);
    virtual ~LCDInterpreter();

    enum LCD_COMMAND {
        GET_KEY_CMD = 'K',
        KEY_INFO_CMD = 'k',
        GET_INFO_CMD = 'I',
        SCREEN_INFO_CMD = 'i',
        SET_SCREEN_CMD = 'F',
        SET_SCREEN_OK_CMD = 'f'
    };

    static QString CommandToString(LCD_COMMAND cmd);

public slots:
    void cmdOpen(QString);
    void cmdList();
    void cmdClose();

    void cmdKey();
    void cmdInfo();
    void cmdImage(QString fileName);
    void cmdSetLed(int led, int red, int green);

protected slots:
    void onBytesAvailable();
    void onCommandReceived(unsigned char cmd, const QByteArray &data, unsigned char crc);

signals:
    void commandReceived(unsigned char c, const QByteArray &data, unsigned char crc);

protected:
    void processBytes(QByteArray data);
    void processByte(unsigned char c);

    enum PARSE_STATE {
        NONE = 0,
        CMD_START = 1,
        CMD_LEN0 = 2,
        CMD_LEN1 = 3,
        CMD_LEN2 = 4,
        CMD_LEN3 = 5,
        CMD_DATA = 6,
        CMD_CRC = 7
    } state;

    unsigned char leds[16];

    LCD_COMMAND cmd;
    unsigned int cmdLength;
    QByteArray data;
    unsigned char crc;

    QextSerialPort *port;
};

#endif // LCDINTERPRETER_H
