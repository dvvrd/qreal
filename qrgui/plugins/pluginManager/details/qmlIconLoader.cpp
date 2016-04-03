/* Copyright 2014-2016 Dmitry Mordvinov
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

#include "qmlIconLoader.h"

#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include <qrutils/graphicsUtils/itemRenderer.h>

using namespace qReal;

QmlIconLoader::QmlIconLoader()
{
}

QmlIconLoader::~QmlIconLoader()
{
}

void QmlIconLoader::setQmlEngine(QQmlEngine &engine)
{
	instance()->mQmlEngine = &engine;
}

QIcon QmlIconLoader::iconOf(const QString &qmlString)
{
	return loadPixmap(qmlString);
}

QSize QmlIconLoader::preferedSizeOf(const QString &qmlString)
{
	loadPixmap(qmlString);
	return instance()->mPreferedSizes[qmlString];
}

QmlIconLoader *QmlIconLoader::instance()
{
	static QmlIconLoader instance;
	return &instance;
}

QIcon QmlIconLoader::loadPixmap(const QString &qmlString)
{
	int FIX_IT_BACK_BITCH = 100500;
//	QQmlComponent component(instance()->mQmlEngine);
//	component.setData(qmlString.toLocal8Bit(), QUrl());
//	QQmlItem * const item = qobject_cast<QDeclarativeItem *>(component.create());
//	const QIcon icon = graphicsUtils::ItemRenderer::renderRecursively(item
//		, item->width(), item->height(), QColor(Qt::white));

//	instance()->mLoadedIcons[qmlString] = icon;
//	instance()->mPreferedSizes[qmlString] = QSize(item->width(), item->height());

	return instance()->mLoadedIcons[qmlString];
}
