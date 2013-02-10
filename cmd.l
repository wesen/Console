%{
#include <stdexcept>

#include <QDebug>
#include <QString>
#include <QVariant>

#include "console.h"

static QVariantList result;
static bool lexWhitespace = false;

%}

%%

[a-zA-Z/]([a-zA-Z\-_0-9/]|\\.)* {
  result.append(QVariant(yytext));
}
-?[0-9]+ {
  result.append(QVariant(yytext));
  bool ok = false;
  long long _i = QString(yytext).toLongLong(&ok);
  if (!ok) {
     throw std::runtime_error(QString("Could not parse number: %1").arg(yytext).toStdString());
  } else {
     result.append(QVariant(_i));
   }
}
(-?[0-9]*\.[0-9]+|[0-9]+\.) {
  bool ok = false;
  double _i = QString(yytext).toDouble(&ok);
  if (!ok) {
     throw std::runtime_error(QString("Could not parse double number: %1").arg(yytext).toStdString());
  } else {
     result.append(QVariant(_i));
   }
}
0x[0-9a-fA-F]+ {
  bool ok = false;
  long long _i = QString(yytext).toLongLong(&ok, 16);
  if (!ok) {
     throw std::runtime_error(QString("Could not parse hexadecimal number: %1").arg(yytext).toStdString());
  } else {
     result.append(QVariant(_i));
   }
}

([^ \t\n]|(\\\ ))+ {
  QString s(yytext);
  result.append(QVariant(s));
}

[ \t\n]+ {
  if (lexWhitespace) {
    result.append(QVariant());
  }
}

%%

     namespace Console {
// not reentrant, kthx
QVariantList Console::lex(const QString &cmd) {
   lexWhitespace = false;
   result.clear();
   YY_BUFFER_STATE buf = yy_scan_string(cmd.toStdString().c_str());
   yy_switch_to_buffer(buf);
   yylex();
   yy_delete_buffer(buf);
   return result;
}

// not reentrant, kthx
QVariantList Console::lexWithWhitespace(const QString &cmd) {
   lexWhitespace = true;
   result.clear();
   YY_BUFFER_STATE buf = yy_scan_string(cmd.toStdString().c_str());
   yy_switch_to_buffer(buf);
   yylex();
   yy_delete_buffer(buf);
   return result;
}
     }
