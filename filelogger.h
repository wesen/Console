#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <QObject>
#include <QString>
#include <QFile>

namespace Console {

class FileLogger : public QObject
{
    Q_OBJECT
public:
    explicit FileLogger(QObject *parent = 0);
    virtual ~FileLogger();
    
signals:
    
public slots:
    void writeLine(QString);
    void close();
    bool openFile(QString filename);
    
protected:
    QFile file;
};

}

#endif // FILELOGGER_H
