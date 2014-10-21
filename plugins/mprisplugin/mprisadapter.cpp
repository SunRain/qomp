/*
 * Copyright (C) 2013  Khryukin Evgeny, Vitaly Tonkacheyev
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

#include "mprisadapter.h"
#include "tune.h"

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QStringList>

MprisAdapter::MprisAdapter(QObject* p) :
	QDBusAbstractAdaptor(p),
	playerStatus_("Stopped"),
	statusChanged_(false),
	metadataChanged_(false)
{
}

void MprisAdapter::setStatus(const QString &status)
{
	if (!status.isEmpty() && (status != playerStatus_)) {
		playerStatus_ = status;
		statusChanged_ = true;
	}
	else {
		statusChanged_ = false;
	}
}

void MprisAdapter::setMetadata(const QompMetaData &tune)
{
	metaDataMap_.clear();
	if (!tune.title.isEmpty()) {
		metaDataMap_["xesam:title"] = QStringList() << tune.title;
	}
	else {
		return;
	}
	if (!tune.album.isEmpty()) {
		metaDataMap_["xesam:album"] = tune.album;
	}
	if (!tune.artist.isEmpty()) {
		metaDataMap_["xesam:artist"] = QStringList() << tune.artist;
	}
	metaDataMap_["xesam:url"] = tune.url;
	metaDataMap_["xesam:trackNumber"] = tune.trackNumber;
	metadataChanged_ = true;
}

QVariantMap MprisAdapter::metadata() const
{
	return metaDataMap_;
}

QString MprisAdapter::playbackStatus() const
{
	return playerStatus_;
}

void MprisAdapter::updateProperties()
{
	QVariantMap map;
	if (!playerStatus_.isEmpty() && statusChanged_) {
		map.insert("PlaybackStatus", playbackStatus());
	}
	if (!metadata().isEmpty() && metadataChanged_) {
		map.insert("Metadata", metadata());
		metadataChanged_ = false;
	}
	if (map.isEmpty()) {
		return;
	}
	QDBusMessage msg = QDBusMessage::createSignal("/org/mpris/MediaPlayer2",
						      "org.freedesktop.DBus.Properties",
						      "PropertiesChanged");
	QVariantList args = QVariantList() << "org.mpris.MediaPlayer2.Player" << map << QStringList();
	msg.setArguments(args);
	QDBusConnection::sessionBus().send(msg);
}
