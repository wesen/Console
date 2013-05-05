#include <iostream>
#include <string>

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include <QCoreApplication>
#include <QtGlobal>
#include <QFile>
#include <QDir>
#include <QDebug>

#ifdef WIN32
#include <windows.h>
#endif

#include "console.h"
#include "helpers.h"

namespace Console {

static int poll()
{
    QCoreApplication::processEvents();
#if defined(WIN32)
    Sleep(100);
#else
//    usleep(10000);
#endif
    return 0;
}

static Console *rl_console = NULL;

int skip_double_quoted(QString s, int i)
{
    bool isEscaped = false;
    for (; i < s.length(); i++)
    {
        QChar c = s.at(i);
        if (isEscaped)
        {
            isEscaped = false;
            continue;
        }
        else if (c == '\\')
        {
            isEscaped = true;
            continue;
        }
        else if (c == '"')
        {
            break;
        }
    }

    return i;
}

int char_is_quoted(char *string, int index)
{
    QString s(string);
    bool isEscaped = false;
    for (int i = 0; i <= index; i++)
    {
        QChar c = s.at(i);

        if (isEscaped)
        {
            if (i >= index)
            {
                return 1;
            }
            isEscaped = false;
            continue;
        }

        if (c == '\\')
        {
            isEscaped = true;
            continue;
        }
        else if ((c == '\'') || (c == '\"'))
        {
            if (c == '\'')
            {
                i = s.indexOf(c, i + 1);
            }
            else
            {
                i = skip_double_quoted(s, i + 1);
            }
            if ((i == -1) || (i > index))
            {
                return 1;
            }
        }
    }

    return 0;
}

char *quote_filename(char *s, int rtype, char *qcp)
{
    return s;
}

char *dequote_filename(char *s, int quote_char)
{
    return s;
}

Console::Console(QString _name, CommandInterpreter *_interpreter) :
    name(_name),
    interpreter(_interpreter),
    stopping(false)
{
    QObject::connect(interpreter, SIGNAL(write(QString)),
                     this, SLOT(write(QString)));
    QObject::connect(interpreter, SIGNAL(writeAsync(QString)),
                     this, SLOT(writeAsync(QString)));
    QObject::connect(interpreter, SIGNAL(exit()), this, SLOT(_quit()));


    /** allow conditional parsing of the inputrc file */
    rl_readline_name = Q(name);
    /** tell the completer that we want a crack first. */
    rl_console = this;
    rl_attempted_completion_function = &Console::ReadlineCompletion;
    rl_event_hook = poll;
    rl_catch_signals = 0;
    rl_filename_quote_characters = " \t\n\\\"'@<>=;|&()#$`?*[!:{~";
    rl_filename_quoting_function = quote_filename;
    rl_filename_dequoting_function = dequote_filename;
    rl_char_is_quoted_p = char_is_quoted;

    using_history();
    historyFile = QDir::homePath() + Q(QString("/.%1_history").arg(name));
    QFile f(historyFile);
    if (!f.exists()) {
        if (!f.open(QIODevice::ReadWrite)) {
            qDebug() << "Could not create history file";
        } else {
            f.close();
        }
    }
    if (f.exists()) {
        read_history(historyFile.toAscii().constData());
    }

    moveToThread(this);
//    rl_bind_key('\t', readline_completion);
}

Console::~Console()
{
}

char **Console::ReadlineCompletion(const char *text, int start, int end)
{
    /* if this is the first word, complete with word names */
    rl_attempted_completion_over = 1;
    QVariantList args = lexWithWhitespace(rl_line_buffer);
    if (args.isEmpty())
    {
        return NULL;
    }
    QString toComplete = args.last().toString();
    if (args.last().isNull())
    {
        toComplete = "";
    }

    if (args.length() == 1)
    {
        return rl_completion_matches(toComplete.toStdString().c_str(), Console::ReadlineCompleteCommands);
    }
    else
    {
        int paramCount = 0;
        for (int i = 1; i < args.length(); i++)
        {
            if (!args.at(i).isNull())
            {
                paramCount++;
            }
        }
        if (!args.last().isNull())
        {
            paramCount--;
        }

        QString cmd = args.first().toString();
        if (rl_console != NULL)
        {
            QMetaMethod method = rl_console->interpreter->dispatch[cmd];
            QList<QByteArray> names = method.parameterNames();
            if (names.length() < paramCount)
            {
                qDebug() << "too many parameters for command";
            }
            else
            {
                //                    qDebug() << "completing parameter name " << QString(names.at(paramCount));
                return rl_completion_matches(toComplete.toStdString().c_str(), rl_filename_completion_function);
//                return NULL;
            }
        }
    }
    return NULL;
}

static char *dupstr(QString &s)
{
    QByteArray ascii = s.toAscii();
    char *res = (char *)malloc(ascii.size() + 1);
    strncpy(res, ascii.constData(), ascii.size());
    res[ascii.size()] = '\0';
    return res;
}

char *Console::ReadlineCompleteCommands(const char *text, int state)
{
    if (rl_console == NULL)
    {
        return NULL;
    }

    static QList<QString>::iterator i;
    static QList<QString> keys;
    if (!state)
    {
        keys = rl_console->interpreter->dispatch.keys();
        i = keys.begin();
    }

    while (i != keys.end())
    {
        QString s = *i++;
        if (s.startsWith(text))
        {
            return dupstr(s);
        }
    }

    return NULL;
}

void Console::run()
{
    while (!stopping)
    {
        QCoreApplication::processEvents();
        char *s = readline(Q(QString("%1> ").arg(name)));
        if (s && *s)
        {
            add_history(s);
            int ret;
            if ((ret = append_history(1, historyFile.toAscii().constData())))
            {
                qDebug() << "Could not append to histoy file " << historyFile.toAscii().constData() << " " << strerror(ret);
            }
        }
        QVariantList args = lex(s);
        interpreter->handleLine(s, args);
        free(s);
    }

    QCoreApplication::quit();
}

void Console::write(QString string)
{
    std::cout << string.toStdString();
}

void Console::writeAsync(QString string)
{
    int need_hack = (rl_readline_state & RL_STATE_READCMD) > 0;

    char *saved_line = NULL;
    int saved_point = 0;
    if (need_hack)
    {
        saved_point = rl_point;
        saved_line = rl_copy_text(0, rl_end);
        rl_save_prompt();
        rl_replace_line("", 0);
        rl_redisplay();
    }

    std::cout << "\r" << string.toStdString();

    if (need_hack)
    {
        rl_restore_prompt();
        rl_replace_line(saved_line, 0);
        rl_point = saved_point;
        rl_redisplay();
        free(saved_line);
    }
}

void Console::terminate()
{
    stopping = true;
    rl_free_line_state();
    rl_cleanup_after_signal();
    ::exit(0);
}

void Console::_quit()
{
    stopping = true;
    this->exit(0);
}

}
