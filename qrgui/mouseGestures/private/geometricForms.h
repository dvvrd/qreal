#pragma once

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtCore/QPair>

namespace qReal {
namespace gestures {

static const qreal e = 10;

static const int gridSize = 81;//gridSize = 100 recognition = 833 gestures

typedef QList<QPointF> PointVector;

typedef QList<PointVector> PathVector;

typedef QPair<QString, PathVector> Entity;

typedef QList<Entity> EntityVector;

typedef QPair<qreal, qreal> SquarePos;

typedef QList<SquarePos> Key;

typedef QPair<QString, PointVector> PathObject;

typedef QPair<QString, Key> IdealGesture;

typedef QList<IdealGesture> IdealGestures;

typedef QPair<QString, QList<QPoint> > GestureObject;

typedef QPair<PathVector, QStringList> UsersGestures;

struct KeyObjectItem
{
public:
	KeyObjectItem(const QString &object, const QList<QPoint> &path, const QString &key)
	{
		this->object = object;
		this->correctPath = path;
		this->key = key;
	}
	KeyObjectItem(){}
	QString object;
	QList<QPoint> correctPath;
	QString key;
};

typedef QList<KeyObjectItem> KeyObjectItems;

struct Object
{
public:
	Object(QString const &name, QList<QList<QPoint> > const &path)
	{
		this->name = name;
		this->path = path;
	}

	QString name;
	QList<QList<QPoint> > path;
};

typedef QList<Object> Objects;

}
}
