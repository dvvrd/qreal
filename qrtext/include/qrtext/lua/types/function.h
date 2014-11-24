#pragma once

#include <QtCore/QStringList>

#include "qrtext/core/types/typeExpression.h"

namespace qrtext {
namespace lua {
namespace types {

/// Reresents function type.
class Function : public core::types::TypeExpression
{
public:
	/// Constructor.
	/// @param returnType - type expression denoting return type of a function.
	/// @param formalParameters - a list of formal parameter types.
	Function(QSharedPointer<core::types::TypeExpression> const &returnType
			, QList<QSharedPointer<core::types::TypeExpression>> const &formalParameters)
		: mReturnType(returnType), mFormalParameters(formalParameters)
	{
	}

	/// Returns return type of a function.
	QSharedPointer<core::types::TypeExpression> const &returnType() const
	{
		return mReturnType;
	}

	/// Returns a list of types of formal parameters.
	QList<QSharedPointer<core::types::TypeExpression>> const &formalParameters() const
	{
		return mFormalParameters;
	}

	QString toString() const override
	{
		QStringList parameterTypes;
		for (QSharedPointer<core::types::TypeExpression> const &type : mFormalParameters) {
			parameterTypes << type->toString();
		}

		return QString("%1(%2)").arg(mReturnType->toString()).arg(parameterTypes.join(", ")) +  QObject::tr("");
	}


private:
	QSharedPointer<core::types::TypeExpression> mReturnType;
	QList<QSharedPointer<core::types::TypeExpression>> mFormalParameters;
};

}
}
}
