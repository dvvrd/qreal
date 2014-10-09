#include "qmlIconLoader.h"

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeItem>

#include <qrutils/graphicsUtils/itemRenderer.h>

using namespace qReal;

QmlIconLoader::QmlIconLoader()
{
}

QmlIconLoader::~QmlIconLoader()
{
}

void QmlIconLoader::setQmlEngine(QDeclarativeEngine * const engine)
{
	instance()->mQmlEngine = engine;
}

QIcon QmlIconLoader::iconOf(QString const &qmlString)
{
	return loadPixmap(qmlString);
}

QSize QmlIconLoader::preferedSizeOf(QString const &qmlString)
{
	loadPixmap(qmlString);
	return instance()->mPreferedSizes[qmlString];
}

QmlIconLoader *QmlIconLoader::instance()
{
	static QmlIconLoader instance;
	return &instance;
}

QIcon QmlIconLoader::loadPixmap(QString const &qmlString)
{
	QDeclarativeComponent component(instance()->mQmlEngine);
	component.setData(qmlString.toLocal8Bit(), QUrl());
	QDeclarativeItem * const item = qobject_cast<QDeclarativeItem *>(component.create());
	QIcon const icon = graphicsUtils::ItemRenderer::renderRecursively(item
		, item->width(), item->height(), QColor(Qt::white));

	instance()->mLoadedIcons[qmlString] = icon;
	instance()->mPreferedSizes[qmlString] = QSize(item->width(), item->height());

	return instance()->mLoadedIcons[qmlString];
}
