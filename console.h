#ifndef CONSOLE_H
#define CONSOLE_H

#include <QThread>
#include <QString>

#include "commandinterpreter.h"

namespace Console {

class Console : public QThread
{
    Q_OBJECT

public:
    Console(QString name, CommandInterpreter *interpreter);
    virtual ~Console();

    static char **ReadlineCompletion(const char *text, int start, int end);
    static char *ReadlineCompleteCommands(const char *text, int state);

    void run();

    static QVariantList lex(const QString &cmd);
    static QVariantList lexWithWhitespace(const QString &cmd);

signals:
    void read(QString);

public slots:
    void write(QString);
    void writeAsync(QString);
    void _quit();
    void terminate();

protected:
    CommandInterpreter *interpreter;
    bool stopping;
    QString historyFile;
    QString name;
};

}
#endif // CONSOLE_H
