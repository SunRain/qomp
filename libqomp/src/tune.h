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

#ifndef TUNE_H
#define TUNE_H

#include <QUrl>
#include <QPointer>

#include "libqomp_global.h"

class Tune;

class LIBQOMPSHARED_EXPORT TuneURLResolveStrategy : public QObject
{
	Q_OBJECT
public:
	explicit TuneURLResolveStrategy(QObject* p = 0);

	virtual QUrl getUrl(const Tune* t) = 0;
	virtual QString name() const = 0;
};

class LIBQOMPSHARED_EXPORT Tune
{
public:
	explicit Tune(bool canSave = true);
	QString artist;
	QString title;
	QString trackNumber;
	QString album;
	QString duration;
	QString url;
	QString file;
	QString bitRate;

	QString displayString() const;
	/**
	 * Synchronously get tune url
	 * This may call some network requests
	 * Blocks caller thread
	 * If possible, use GetTuneUrlHelper instead
	 */
	QUrl getUrl() const;

	QString toString() const;
	bool fromString(const QString& str);
	int id() const;
	bool canSave() const { return canSave_; }

	void setUrlResolveStrategy(TuneURLResolveStrategy* strategy) const;
	TuneURLResolveStrategy* strategy() const;

	bool operator==(const Tune& other) const;

	static QList<Tune*> tunesFromFile(const QString& fileName);

	static const Tune* emptyTune() { return empty_; }

private:
	Q_DISABLE_COPY(Tune)
	static int lastId_;
	int id_;
	bool canSave_;
	mutable QPointer<TuneURLResolveStrategy> strategy_;

	static const Tune* empty_;
};

#endif // TUNE_H
