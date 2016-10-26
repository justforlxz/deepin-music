/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef PLAYER_H
#define PLAYER_H

#include <QSharedPointer>
#include <QMediaPlayer>

#include "../model/musiclistmodel.h"

class Playlist;

class Player : public QMediaPlayer
{
    Q_OBJECT
public:

    enum PlayStatus {
        Invaild = 0,
        Stop,
        Playing,
        Pause
    };
    Q_ENUM(PlayStatus)

    enum PlayMode {
        Order = 0,
        RepeatAll = 1,
        RepeatSingle = 2,
        Shuffle = 3,
    };
    Q_ENUM(PlayMode)

    static Player *instance()
    {
        static auto s_app = new Player;
        return s_app;
    }

    void setPlaylist(QSharedPointer<Playlist> playlist);
    void setMode(PlayMode mode);

    void init() {}
signals:
    void progrossChanged(qint64 value, qint64 range);
public slots:
    void setMedia(const MusicInfo &info);
    void changeProgress(qint64 value, qint64 range);

private:
    void selectNext();
    explicit Player(QObject *parent = 0);

    MusicInfo                   m_info;
    QStringList                 m_historyIDs;
    QSharedPointer<Playlist>    m_playlist;
    QMap<QString, MusicInfo>    musicMap;
    qint64                      m_duration = -1;
    PlayMode                    m_mode;
};

#endif // PLAYER_H
