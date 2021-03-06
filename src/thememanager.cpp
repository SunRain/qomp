/*
 * Copyright (C) 2014  Khryukin Evgeny
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

#include "thememanager.h"

#include <QApplication>
#include <QFile>
#include <QDir>

ThemeManager *ThemeManager::instance_ = 0;


ThemeManager *ThemeManager::instance()
{
	if(!instance_)
		instance_ = new ThemeManager;
	return instance_;
}

void ThemeManager::setTheme(const QString &theme)
{
	if(currentTheme_ == theme)
		return;

	if(!theme.isEmpty() && themes_.contains(theme)) {
		QFile file(themes_.value(theme));
		if(file.exists() && file.open(QFile::ReadOnly | QFile::Text)) {
			currentTheme_ = theme;
			const QByteArray content = file.readAll();
			qApp->setStyleSheet(content);
		}
	}
}

void ThemeManager::loadThemes()
{
	foreach(const QString& d, themeFolders()) {
		QDir dir(d);
		if(dir.exists()) {
			foreach(QString file, dir.entryList(QDir::Files)) {
				if(!file.endsWith(".thm"))
					continue;
				const QString path = d + '/' + file;
				file.chop(4);
				themes_.insert(file, path);
			}
		}
	}
}

QStringList ThemeManager::availableThemes() const
{
	return themes_.keys();
}

ThemeManager::ThemeManager() :
	QObject(qApp)
{
	loadThemes();
}

QStringList ThemeManager::themeFolders()
{
	QStringList list;
	list << ":/themes/";
#ifdef Q_OS_WIN
	list.append(qApp->applicationDirPath()+"/themes");
#elif defined (HAVE_X11)
	list.append(QString(QOMP_DATADIR) + "/themes");
#elif defined (Q_OS_MAC)
	QDir appDir = qApp->applicationDirPath();
	appDir.cdUp();
	appDir.cd("Themes");
	list.append(appDir.absolutePath());
#elif defined (Q_OS_ANDROID)
	list.append("assets:/themes");
#endif
	return list;
}
