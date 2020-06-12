/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Maintainer: Peng Hui<penghui@deepin.com>
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

#include "shortcut.h"
#include "./core/musicsettings.h"
#include <QVariant>
Shortcut::Shortcut(QObject *parent) : QObject(parent)
{
    ShortcutGroup group1;
    ShortcutGroup group2;
    ShortcutGroup group3;
    ShortcutGroup group4;

    group1.groupName = tr("Play");
    group2.groupName = tr("Songs");
    group3.groupName = tr("Playlists");
    group4.groupName = tr("Settings");

    group1.groupItems <<
                      ShortcutItem(tr("Play/Pause"),       MusicSettings::value("shortcuts.all.play_pause").toString()) <<
                      ShortcutItem(tr("Previous"),   MusicSettings::value("shortcuts.all.previous").toString()) <<
                      ShortcutItem(tr("Next"),   MusicSettings::value("shortcuts.all.next").toString()) <<
                      ShortcutItem(tr("Volume Up"),   MusicSettings::value("shortcuts.all.volume_up").toString()) <<
                      ShortcutItem(tr("Volume Down"),   MusicSettings::value("shortcuts.all.volume_down").toString()) <<
                      ShortcutItem(tr("Mute"),   "M");

    group2.groupItems <<
                      ShortcutItem(tr("Favorite"), "Ctrl+K") <<
                      ShortcutItem(tr("Unfavorite"),  "Ctrl+Shift+K") <<
                      ShortcutItem(tr("Song info"),   "Alt+Enter");

    group3.groupItems <<
                      ShortcutItem(tr("New playlist"), "Ctrl+Shift+N") <<
                      ShortcutItem(tr("Add music"), "Ctrl+I") <<
                      ShortcutItem(tr("Rename playlist"), "F2") <<
                      ShortcutItem(tr("Remove from playlist"), "Delete");

    group4.groupItems <<
                      ShortcutItem(tr("Help"),  "F1") <<
                      ShortcutItem(tr("Display shortcuts"), "Ctrl+Shift+?");

    m_shortcutGroups << group1 << group2 << group3 << group4;

    //convert to json object
    QJsonArray jsonGroups;
    for (auto scg : m_shortcutGroups) {
        QJsonObject jsonGroup;
        jsonGroup.insert("groupName", scg.groupName);
        QJsonArray jsonGroupItems;
        for (auto sci : scg.groupItems) {
            QJsonObject jsonItem;
            jsonItem.insert("name", sci.name);
            jsonItem.insert("value", sci.value);
            jsonGroupItems.append(jsonItem);
        }
        jsonGroup.insert("groupItems", jsonGroupItems);
        jsonGroups.append(jsonGroup);
    }
    m_shortcutObj.insert("shortcut", jsonGroups);
}
QString Shortcut::toStr()
{
    QJsonDocument doc(m_shortcutObj);
    return doc.toJson().data();
}
