#include <QtCore/QCoreApplication>
#include <QDebug>

#include <stdio.h>
#include <signal.h>

#include "console.h"
#include "lcdinterpreter.h"
#include "qsignalcatcher.h"
#include <QDebug>

#include <readline/readline.h>

void real_exit()
{
    exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int ret = 0;

    Console::signalCatcher.init();

    QObject::connect(&Console::signalCatcher, SIGNAL(sigint()), &a, SLOT(quit()));

    LCDInterpreter *interpreter = new LCDInterpreter();
    Console::Console *console = new Console::Console("lcd", interpreter);

    QObject::connect(&a, SIGNAL(aboutToQuit()), console, SLOT(terminate()));

    console->start();

    ret = a.exec();

    console->_quit();
//    console->wait();
    delete console;
    delete interpreter;


    rl_free_line_state();
    rl_cleanup_after_signal();

    return ret;
}

