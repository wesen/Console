#include <QDebug>
#include <QTextStream>

#include "filelogger.h"

namespace Console {

FileLogger::FileLogger(QObject *parent) :
    QObject(parent)
{
}

FileLogger::~FileLogger() {
    close();
}

void FileLogger::writeLine(QString line) {
    if (file.isWritable()) {
        QTextStream out(&file);
        out << line;
        out.flush();
    }
}

void FileLogger::close() {
    if (file.isOpen()) {
        file.close();
    }
}

bool FileLogger::openFile(QString filename) {
    close();
    file.setFileName(filename);
    return file.open(QIODevice::Append);
}

}
