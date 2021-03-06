/*
 * Copyright (C) 2013  Khryukin Evgeny
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef YANDEXMUSICGETTUNSDLG_H
#define YANDEXMUSICGETTUNSDLG_H

#include "qompplugingettunesdlg.h"

class QAbstractItemModel;

enum YandexMusicTabKind { TabArtist = 0, TabAlbum = 1, TabTrack = 2 };

class YandexMusicGettunsDlg : public QompPluginGettunesDlg
{
	Q_OBJECT
public:
	explicit YandexMusicGettunsDlg();
	~YandexMusicGettunsDlg();

	void setCuuretnTab(YandexMusicTabKind kind);
	void setModel(QAbstractItemModel* model, YandexMusicTabKind kind);
	int currentTabRows() const;
	

private:
	class Private;
	Private* p;
	friend class Private;
};

#endif // YANDEXMUSICGETTUNSDLG_H
