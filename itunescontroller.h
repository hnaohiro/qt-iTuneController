#ifndef ITUNESCONTROLLER_H
#define ITUNESCONTROLLER_H

#include <QObject>

class iTunesController : public QObject
{
    Q_OBJECT
public:
    explicit iTunesController(QObject *parent = 0);

public slots:
    void play();
    void pause();
    void playpause();
    void stop();
    void next();
    void back();
    void setVolume(int value);

    void runScript(const QString &script);
};

#endif // ITUNESCONTROLLER_H
