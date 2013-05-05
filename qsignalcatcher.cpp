#include <signal.h>
#include <stdio.h>

#include "qsignalcatcher.h"

namespace Console {

QSignalCatcher signalCatcher;

static void on_sigint(int sig) {
    signalCatcher.onSignal(sig);
}

QSignalCatcher::QSignalCatcher(QObject *parent) :
    QObject(parent)
{
}

void QSignalCatcher::init() {
    prev_sigint = signal(SIGINT, on_sigint);
}

void QSignalCatcher::restore() {
    signal(SIGINT, prev_sigint);
}

void QSignalCatcher::onSignal(int signal) {
    switch (signal) {
    case SIGINT:
        emit sigint();
        break;

    default:
        break;
    }
}

}
