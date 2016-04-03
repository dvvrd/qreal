/* Copyright 2013-2016 Yurii Litvinov, Dmitry Mordvinov, CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "imagesCache.h"

#include <qrkernel/platformInfo.h>

#include <QtCore/QDir>
#include <QtGui/QPainter>

using namespace qReal;

inline uint qHash(const QRect &rect)
{
	return qHash(rect.width()) ^ qHash(rect.height()) ^ qHash(rect.top()) ^ qHash(rect.left());
}

ImagesCache::ImagesCache()
{
}

ImagesCache::~ImagesCache()
{
}

ImagesCache &ImagesCache::instance()
{
	static ImagesCache instance;
	return instance;
}

void ImagesCache::drawImage(const QString &fileName, QPainter &painter, const QRect &rect, qreal zoom)
{
	if (mFileNamePixmapMap.contains(fileName)) {
		painter.drawPixmap(rect, mFileNamePixmapMap.value(fileName));
		return;
	}

	QTransform scale;
	scale.scale(zoom, zoom);
	auto scaledRect = scale.mapRect(rect);
	auto savePrerenderedSvg = [this, &fileName, &scaledRect] (QSvgRenderer &renderer) {
		QPixmap pixmap(scaledRect.size());
		pixmap.fill(Qt::transparent);
		QPainter pixmapPainter(&pixmap);
		renderer.render(&pixmapPainter, scaledRect.translated(-scaledRect.topLeft()));
		mPrerenderedSvgs[fileName].insert(scaledRect, pixmap);
	};

	if (mFileNameSvgRendererMap.contains(fileName)) {
		if (!mPrerenderedSvgs.contains(fileName) || !mPrerenderedSvgs[fileName].contains(scaledRect)) {
			savePrerenderedSvg(*mFileNameSvgRendererMap.value(fileName));
		}

		painter.drawPixmap(rect, mPrerenderedSvgs[fileName][scaledRect]);
	} else {
		// Cache miss - finding best file to load and loading it.
		const QFileInfo actualFile = selectBestImageFile(PlatformInfo::invariantPath(fileName));
		const QByteArray rawImage = loadPixmap(actualFile);

		if (actualFile.suffix() == "svg") {
			QSharedPointer<QSvgRenderer> renderer(new QSvgRenderer(rawImage));
			mFileNameSvgRendererMap.insert(fileName, renderer);
			savePrerenderedSvg(*renderer);
			painter.drawPixmap(rect, mPrerenderedSvgs[fileName][scaledRect]);
		} else {
			QPixmap pixmap;
			pixmap.loadFromData(rawImage);
			mFileNamePixmapMap.insert(fileName, pixmap);
			painter.drawPixmap(rect, pixmap);
		}
	}
}

QFileInfo ImagesCache::selectBestImageFile(const QString &filePath)
{
	const QFileInfo originalFileInfo(filePath);
	const QFileInfo svgVersion(originalFileInfo.path() + originalFileInfo.completeBaseName() + "svg");

	if (svgVersion.exists()) {
		return svgVersion;
	}

	const QFileInfo fileInfo(filePath);
	if (fileInfo.exists() && fileInfo.isFile()) {
		return fileInfo;
	}

	QDir dir(fileInfo.absolutePath());
	auto candidates = dir.entryInfoList({fileInfo.completeBaseName() + ".*"}, QDir::Files);
	if (!candidates.empty()) {
		return candidates.at(0);
	}

	if (fileInfo.completeBaseName() != "default") {
		return selectBestImageFile(fileInfo.absolutePath() + "/default.svg");
	}

	return QFileInfo(":/pluginManager/images/default.svg");
}

QByteArray ImagesCache::loadPixmap(const QFileInfo &fileInfo)
{
	QFile file(fileInfo.absoluteFilePath());
	if (!file.open(QIODevice::ReadOnly)) {
		return QByteArray();
	}

	return file.readAll();
}
