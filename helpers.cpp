#include <QTextStream>
#include "helpers.h"

static void _hexdump(QTextStream &o, const unsigned char *buffer, unsigned long index) {
    unsigned long width = 16;
    unsigned long i;
    for (i = 0; i < index; i++) {
        hex(o) << qSetFieldWidth(2) << buffer[i] << qSetFieldWidth(0) << " ";
    }
    for (unsigned long spacer = index; spacer < width; spacer++) {
        o << "   ";
    }
    o << ": ";
    for (i = 0; i < index; i++) {
        if (buffer[i] < 32 || buffer[i] >= 127) {
            o << ".";
        } else {
            o << QChar(buffer[i]);
        }
    }
    o << "\n";
}


QString qHexdump(QByteArray a) {
    QString res;
    QTextStream o;
    o.setString(&res);
    o.setPadChar(QChar('0'));

    const unsigned char *ptr = (const unsigned char *)a.constData();

    for (long i = 0; i < a.size(); i += 16) {
        _hexdump(o, ptr + i, qMin((long int)16, a.size() - i));
    }

    o.flush();

    return res;
}

QString qHexdumpShort(QByteArray a, int pad) {
    QString res;
    QTextStream o;
    o.setString(&res);
    o.setPadChar(QChar('0'));

    const unsigned char *ptr = (const unsigned char *)a.constData();

    long i;
    for (i = 0; i < a.size(); i++) {
        hex(o) << qSetFieldWidth(2) << ptr[i] << qSetFieldWidth(0) << " ";
    }

    for (; i < pad; i++) {
        o << "   ";
    }

    o.flush();

    return res;
}
