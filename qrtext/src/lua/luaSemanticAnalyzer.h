#pragma once

#include <QtCore/QScopedPointer>

#include "qrtext/core/semantics/semanticAnalyzer.h"
#include "qrtext/lua/types/function.h"

#include "qrtext/declSpec.h"

namespace qrtext {
namespace lua {
namespace details {

/// Semantic analyzer for Lua language.
class QRTEXT_EXPORT LuaSemanticAnalyzer : public core::SemanticAnalyzer
{
public:
	/// Constructor.
	/// @param errors - error stream to report errors to.
	explicit LuaSemanticAnalyzer(QList<core::Error> &errors);

	/// Registers external (intrinsic for a language) function in interpreter.
	/// @param name - name of a function.
	/// @param type - type of a function.
	void addIntrinsicFunction(QString const &name, QSharedPointer<types::Function> const &type);

	/// Override that excludes intrinsic function identifiers.
	QMap<QString, QSharedPointer<core::types::TypeExpression>> variableTypes() const;

private:
	void analyzeNode(QSharedPointer<core::ast::Node> const &node) override;
	void analyzeUnaryOperator(QSharedPointer<core::ast::Node> const &node);
	void analyzeBinaryOperator(QSharedPointer<core::ast::Node> const &node);

	void constrainAssignment(QSharedPointer<core::ast::Node> const &operation
			, QSharedPointer<core::ast::Node> const &lhs, QSharedPointer<core::ast::Node> const &rhs);

	void analyzeFunctionCall(QSharedPointer<core::ast::Node> const &node);

	QSharedPointer<core::types::TypeExpression> mBoolean;
	QSharedPointer<core::types::TypeExpression> mFloat;
	QSharedPointer<core::types::TypeExpression> mInteger;
	QSharedPointer<core::types::TypeExpression> mNil;
	QSharedPointer<core::types::TypeExpression> mString;

	QHash<QString, QSharedPointer<types::Function>> mIntrinsicFunctions;
};

}
}
}
