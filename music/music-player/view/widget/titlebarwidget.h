/*
 * Copyright (C) 2016 ~ 2018 Wuhan Deepin Technology Co., Ltd.
 *
 * Author:     Iceyer <me@iceyer.net>
 *
 * Maintainer: Iceyer <me@iceyer.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <DWidget>

#include "../core/playlist.h"

DWIDGET_USE_NAMESPACE

class SearchResult;
class TitlebarWidgetPrivate;
class TitlebarWidget : public DWidget
{
    Q_OBJECT
public:
    explicit TitlebarWidget(QWidget *parent = Q_NULLPTR);
    ~TitlebarWidget() override;

    void exitSearch();
    void clearSearch();
    void setSearchEnable(bool enable = true);
    void setResultWidget(SearchResult *);
    void setViewname(const QString &viewname);

    void setEditStatus();

public slots:
    void selectPlaylist(PlaylistPtr playlistPtr);
    void onSearchAborted();
signals:
    void searchExited();
    void searchText(const QString &id, const QString &text);
    void searchCand(const QString &text);//查询候选
    void locateMusicInAllMusiclist(const QString &hash);

protected:
    virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    QScopedPointer<TitlebarWidgetPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), TitlebarWidget)
};
