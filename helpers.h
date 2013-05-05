#ifndef HELPERS_H
#define HELPERS_H

#include <QString>

/** Compile-time assertion in C. **/
#ifndef C_ASSERT
#define C_ASSERT(e) extern char __C_ASSERT__[(e)?1:-1] __attribute__((unused))
#endif

/** Compress a C structure to byte aligned boundaries. **/
#ifndef PACKED
#define PACKED __attribute__ ((packed))
#endif

#define countof( array ) ( sizeof( array )/sizeof( array[0] ) )

#define Q(string) ((QString)string).toStdString().c_str()

QString qHexdump(QByteArray a);
QString qHexdumpShort(QByteArray a, int pad = 16);


#endif // HELPERS_H
