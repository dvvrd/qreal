#include "qrtext/core/connection.h"

using namespace qrtext::core;

Connection::Connection(int absolutePosition, int line, int column, const qReal::Id &id, const QString &propertyName)
	: mAbsolutePosition(absolutePosition)
	, mLine(line)
	, mColumn(column)
	, mId(id)
	, mPropertyName(propertyName)
{
}

Connection::Connection()
{
}

int Connection::absolutePosition() const
{
	return mAbsolutePosition;
}

int Connection::line() const
{
	return mLine;
}

int Connection::column() const
{
	return mColumn;
}

qReal::Id const &Connection::id() const
{
	return mId;
}

QString const &Connection::propertyName() const
{
	return mPropertyName;
}
