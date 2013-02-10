
#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QList>
#include <QMetaMethod>
#include <QScriptEngine>
#include <QVariant>

#include "filelogger.h"

namespace Console {
class Console;

class CommandInterpreter : public QObject
{
    Q_OBJECT
public:
    explicit CommandInterpreter(QObject *parent = 0);
    virtual ~CommandInterpreter();

    typedef void (CommandInterpreter::*CommandMethod)(QList<QString>);

    virtual void populateMetaMethods();

    void listCommands();
    friend class Console;

signals:
    void write(QString s);
    void writeAsync(QString s);
    void exit();

public slots:
    virtual void handleLine(QString s, QVariantList args);

    virtual void cmdExit();
    virtual void cmdHelp(QString cmd);
    virtual void cmdLog(QString filename);
    virtual void cmdCloseLog();
    virtual void cmdRun(QString fileName);
    virtual void cmdEval(QString code);


protected:
    QMap<QString, QMetaMethod> dispatch;
    QScriptEngine engine;
    FileLogger fileLogger;
};

}

#endif // COMMANDINTERPRETER_H
