#include "itunescontroller.h"

#include <QDebug>
#include <QProcess>
#include <QStringList>

iTunesController::iTunesController(QObject *parent) :
    QObject(parent)
{
}

void iTunesController::play()
{
    runScript("play");
}

void iTunesController::pause()
{
    runScript("pause");
}

void iTunesController::playpause()
{
    runScript("playpause");
}

void iTunesController::stop()
{
    runScript("stop");
}

void iTunesController::next()
{
    runScript("next track");
}

void iTunesController::back()
{
    runScript("back track");
}

void iTunesController::setVolume(int value)
{
    runScript(QString("set sound volume to %1").arg(value));
}

void iTunesController::runScript(const QString &command)
{
    QString script = QString("tell application \"iTunes\"\n"
                             "   %1\n"
                             "end tell").arg(command);

    QProcess process;
    process.start("osascript", QStringList() << "-l" << "AppleScript");
    process.write(script.toUtf8());
    process.closeWriteChannel();
    process.waitForReadyRead(-1);
}
