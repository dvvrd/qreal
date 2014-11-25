#include "luaPrinter.h"

#include <qrkernel/logging.h>

#include <qrtext/lua/ast/number.h>
#include <qrtext/lua/ast/unaryMinus.h>
#include <qrtext/lua/ast/not.h>
#include <qrtext/lua/ast/bitwiseNegation.h>
#include <qrtext/lua/ast/length.h>
#include <qrtext/lua/ast/logicalAnd.h>
#include <qrtext/lua/ast/logicalOr.h>
#include <qrtext/lua/ast/addition.h>
#include <qrtext/lua/ast/subtraction.h>
#include <qrtext/lua/ast/multiplication.h>
#include <qrtext/lua/ast/division.h>
#include <qrtext/lua/ast/integerDivision.h>
#include <qrtext/lua/ast/modulo.h>
#include <qrtext/lua/ast/exponentiation.h>
#include <qrtext/lua/ast/bitwiseAnd.h>
#include <qrtext/lua/ast/bitwiseOr.h>
#include <qrtext/lua/ast/bitwiseXor.h>
#include <qrtext/lua/ast/bitwiseLeftShift.h>
#include <qrtext/lua/ast/bitwiseRightShift.h>
#include <qrtext/lua/ast/concatenation.h>
#include <qrtext/lua/ast/equality.h>
#include <qrtext/lua/ast/lessThan.h>
#include <qrtext/lua/ast/lessOrEqual.h>
#include <qrtext/lua/ast/inequality.h>
#include <qrtext/lua/ast/greaterThan.h>
#include <qrtext/lua/ast/greaterOrEqual.h>
#include <qrtext/lua/ast/integerNumber.h>
#include <qrtext/lua/ast/floatNumber.h>
#include <qrtext/lua/ast/fieldInitialization.h>
#include <qrtext/lua/ast/tableConstructor.h>
#include <qrtext/lua/ast/string.h>
#include <qrtext/lua/ast/true.h>
#include <qrtext/lua/ast/false.h>
#include <qrtext/lua/ast/nil.h>
#include <qrtext/lua/ast/identifier.h>
#include <qrtext/lua/ast/functionCall.h>
#include <qrtext/lua/ast/methodCall.h>
#include <qrtext/lua/ast/assignment.h>
#include <qrtext/lua/ast/block.h>
#include <qrtext/lua/ast/indexingExpression.h>
#include <qrtext/languageToolboxInterface.h>
#include <qrtext/lua/types/integer.h>
#include <qrtext/lua/types/float.h>
#include <qrtext/lua/types/boolean.h>
#include <qrtext/lua/types/string.h>

#include "reservedFunctionsConverter.h"

using namespace generatorBase::lua;

LuaPrinter::LuaPrinter(QString const &pathToTemplates
		, qrtext::LanguageToolboxInterface const &textLanguage
		, PrecedenceConverterInterface &precedeceTable
		, simple::Binding::ConverterInterface const *reservedVariablesConverter)
	: TemplateParametrizedEntity(pathToTemplates + "/luaPrinting")
	, mTextLanguage(textLanguage)
	, mPrecedenceTable(precedeceTable)
	, mReservedVariablesConverter(reservedVariablesConverter)
	, mReservedFunctionsConverter(pathToTemplates)
{
}

LuaPrinter::~LuaPrinter()
{
	delete mReservedVariablesConverter;
}

QString LuaPrinter::print(QSharedPointer<qrtext::lua::ast::Node> const &node)
{
	return printWithoutPop(node) ? popResult(*node) : QString();
}

QString LuaPrinter::castToString(QSharedPointer<qrtext::lua::ast::Node> const &node)
{
	return printWithoutPop(node) ? toString(node) : QString();
}

void LuaPrinter::pushResult(qrtext::lua::ast::Node const &node, QString const &generatedCode)
{
	mGeneratedCode[&node] = generatedCode;
}

QString LuaPrinter::popResult(qrtext::lua::ast::Node const &node, bool wrapIntoBrackets)
{
	QString const code = mGeneratedCode.take(&node);
	return wrapIntoBrackets ? "(" + code + ")" : code;
}

QStringList LuaPrinter::popResults(QList<QSharedPointer<qrtext::lua::ast::Node>> const &nodes)
{
	QStringList result;
	for (QSharedPointer<qrtext::lua::ast::Node> const &node : nodes) {
		result << popResult(*node);
	}

	return result;
}

bool LuaPrinter::printWithoutPop(QSharedPointer<qrtext::lua::ast::Node> const &node)
{
	if (!node) {
		return false;
	}

	node->acceptRecursively(*this);
	if (mGeneratedCode.keys().count() != 1 || mGeneratedCode.keys().first() != node.data()) {
		QLOG_WARN() << "Lua printer got into the inconsistent state during printing."
				<< mGeneratedCode.keys().count() << "pieces of code:";
		for (QString const &code : mGeneratedCode.values()) {
			QLOG_INFO() << code;
		}

		mGeneratedCode.clear();
		return false;
	}

	return true;
}

void LuaPrinter::processTemplate(qrtext::lua::ast::Node const &node
		, QString const &templateFileName
		, QMap<QString, QSharedPointer<qrtext::lua::ast::Node>> const &bindings)
{
	QString result = readTemplate(templateFileName);
	for (QString const &toReplace : bindings.keys()) {
		result.replace(toReplace, popResult(*bindings[toReplace]));
	}

	pushResult(node, result);
}

void LuaPrinter::processUnary(qrtext::core::ast::UnaryOperator const &node, QString const &templateFileName)
{
	pushResult(node, readTemplate(templateFileName)
			.replace("@@OPERAND@@", popResult(*node.operand(), needBrackets(node, *node.operand()))));
}

void LuaPrinter::processBinary(qrtext::core::ast::BinaryOperator const &node, QString const &templateFileName)
{
	pushResult(node, readTemplate(templateFileName)
			.replace("@@LEFT@@", popResult(*node.leftOperand(), needBrackets(node
					, *node.leftOperand(), qrtext::core::Associativity::left)))
			.replace("@@RIGHT@@", popResult(*node.rightOperand(), needBrackets(node
					, *node.rightOperand(), qrtext::core::Associativity::right))));
}

bool LuaPrinter::needBrackets(qrtext::lua::ast::Node const &parent
		, qrtext::lua::ast::Node const &child
		, qrtext::core::Associativity childAssociativity) const
{
	int const parentPrecedence = mPrecedenceTable.precedence(parent);
	int const childPrecedence = mPrecedenceTable.precedence(child);
	return parentPrecedence > childPrecedence || (parentPrecedence == childPrecedence
			&& mPrecedenceTable.associativity(parent) != childAssociativity);
}

void LuaPrinter::visit(qrtext::lua::ast::Number const &node)
{
	pushResult(node, node.stringRepresentation());
}

void LuaPrinter::visit(qrtext::lua::ast::UnaryMinus const &node)
{
	processUnary(node, "unaryMinus.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Not const &node)
{
	processUnary(node, "not.t");
}

void LuaPrinter::visit(qrtext::lua::ast::BitwiseNegation const &node)
{
	processUnary(node, "bitwiseNegation.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Length const &node)
{
	processUnary(node, "length.t");
}

void LuaPrinter::visit(qrtext::lua::ast::LogicalAnd const &node)
{
	processBinary(node, "logicalAnd.t");
}

void LuaPrinter::visit(qrtext::lua::ast::LogicalOr const &node)
{
	processBinary(node, "logicalOr.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Addition const &node)
{
	processBinary(node, "addition.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Subtraction const &node)
{
	processBinary(node, "subtraction.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Multiplication const &node)
{
	processBinary(node, "multiplication.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Division const &node)
{
	processBinary(node, "division.t");
}

void LuaPrinter::visit(qrtext::lua::ast::IntegerDivision const &node)
{
	processBinary(node, "integerDivision.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Modulo const &node)
{
	processBinary(node, "modulo.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Exponentiation const &node)
{
	processBinary(node, "exponentiation.t");
}

void LuaPrinter::visit(qrtext::lua::ast::BitwiseAnd const &node)
{
	processBinary(node, "bitwiseAnd.t");
}

void LuaPrinter::visit(qrtext::lua::ast::BitwiseOr const &node)
{
	processBinary(node, "bitwiseOr.t");
}

void LuaPrinter::visit(qrtext::lua::ast::BitwiseXor const &node)
{
	processBinary(node, "bitwiseXor.t");
}

void LuaPrinter::visit(qrtext::lua::ast::BitwiseLeftShift const &node)
{
	processBinary(node, "bitwiseLeftShift.t");
}

void LuaPrinter::visit(qrtext::lua::ast::BitwiseRightShift const &node)
{
	processBinary(node, "bitwiseRightShift.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Concatenation const &node)
{
	pushResult(node, readTemplate("concatenation.t")
			.replace("@@LEFT@@", toString(node.leftOperand()))
			.replace("@@RIGHT@@", toString(node.rightOperand())));
}

void LuaPrinter::visit(qrtext::lua::ast::Equality const &node)
{
	processBinary(node, "equality.t");
}

void LuaPrinter::visit(qrtext::lua::ast::LessThan const &node)
{
	processBinary(node, "lessThan.t");
}

void LuaPrinter::visit(qrtext::lua::ast::LessOrEqual const &node)
{
	processBinary(node, "lessOrEqual.t");
}

void LuaPrinter::visit(qrtext::lua::ast::Inequality const &node)
{
	processBinary(node, "inequality.t");
}

void LuaPrinter::visit(qrtext::lua::ast::GreaterThan const &node)
{
	processBinary(node, "greaterThan.t");
}

void LuaPrinter::visit(qrtext::lua::ast::GreaterOrEqual const &node)
{
	processBinary(node, "greaterOrEqual.t");
}

void LuaPrinter::visit(qrtext::lua::ast::IntegerNumber const &node)
{
	pushResult(node, node.stringRepresentation());
}

void LuaPrinter::visit(qrtext::lua::ast::FloatNumber const &node)
{
	pushResult(node, node.stringRepresentation());
}

void LuaPrinter::visit(qrtext::lua::ast::FieldInitialization const &node)
{
	QString const templatePath = node.key().data()
			? "explicitKeyFieldInitialization.t"
			: "implicitKeyFieldInitialization.t";
	processTemplate(node, templatePath, { {"@@KEY@@", node.key()}, {"@@VALUE@@", node.value()} });
}

void LuaPrinter::visit(qrtext::lua::ast::TableConstructor const &node)
{
	QStringList const initializers = popResults(qrtext::as<qrtext::lua::ast::Node>(node.initializers()));
	pushResult(node, readTemplate("tableConstructor.t")
			.replace("@@COUNT@@", QString::number(initializers.count()))
			.replace("@@INITIALIZERS@@", initializers.join(readTemplate("fieldInitializersSeparator.t"))));
}

void LuaPrinter::visit(qrtext::lua::ast::String const &node)
{
	pushResult(node, readTemplate("string.t").replace("@@VALUE@@", node.string()));
}

void LuaPrinter::visit(qrtext::lua::ast::True const &node)
{
	pushResult(node, readTemplate("true.t"));
}

void LuaPrinter::visit(qrtext::lua::ast::False const &node)
{
	pushResult(node, readTemplate("false.t"));
}

void LuaPrinter::visit(qrtext::lua::ast::Nil const &node)
{
	pushResult(node, readTemplate("nil.t"));
}

void LuaPrinter::visit(qrtext::lua::ast::Identifier const &node)
{
	/// @todo: if some function or method will have same id as some reserved variable it will be replaced too...
	pushResult(node, mReservedVariablesConverter->convert(node.name()));
}

void LuaPrinter::visit(qrtext::lua::ast::FunctionCall const &node)
{
	QString const expression = popResult(*node.function());
	QStringList const arguments = popResults(qrtext::as<qrtext::lua::ast::Node>(node.arguments()));

	qrtext::lua::ast::Identifier const *idNode = dynamic_cast<qrtext::lua::ast::Identifier *>(node.function().data());
	QString const reservedFunctionCall = idNode
			? mReservedFunctionsConverter.convert(idNode->name(), arguments)
			: QString();

	if (reservedFunctionCall.isEmpty()) {
		pushResult(node, readTemplate("functionCall.t")
				.replace("@@FUNCTION@@", expression)
				.replace("@@ARGUMENTS@@", arguments.join(readTemplate("argumentsSeparator.t"))));
	} else {
		pushResult(node, reservedFunctionCall);
	}
}

void LuaPrinter::visit(qrtext::lua::ast::MethodCall const &node)
{
	QString const object = popResult(*node.object());
	QString const method = popResult(*node.methodName());
	QStringList const arguments = popResults(qrtext::as<qrtext::lua::ast::Node>(node.arguments()));
	pushResult(node, readTemplate("methodCall.t")
			.replace("@@OBJECT@@", object)
			.replace("@@METHOD@@", method)
			.replace("@@ARGUMENTS@@", arguments.join(readTemplate("argumentsSeparator.t"))));
}

void LuaPrinter::visit(qrtext::lua::ast::Assignment const &node)
{
	processTemplate(node, "assignment.t", { {"@@VARIABLE@@", node.variable()}, {"@@VALUE@@", node.value()} });
}

void LuaPrinter::visit(qrtext::lua::ast::Block const &node)
{
	QStringList const expressions = popResults(node.children());
	pushResult(node, expressions.join(readTemplate("statementsSeparator.t")));
}

void LuaPrinter::visit(qrtext::lua::ast::IndexingExpression const &node)
{
	processTemplate(node, "indexingExpression.t", { {"@@TABLE@@", node.table()}, {"@@INDEXER@@", node.indexer()} });
}

QString LuaPrinter::toString(QSharedPointer<qrtext::lua::ast::Node> const &node)
{
	QSharedPointer<qrtext::core::types::TypeExpression> const type = mTextLanguage.type(node);
	QString const value = popResult(*node);
	if (type->is<qrtext::lua::types::String>()) {
		return value;
	}

	if (type->is<qrtext::lua::types::Integer>()) {
		return readTemplate("intToString.t").replace("@@VALUE@@", value);
	}

	if (type->is<qrtext::lua::types::Float>()) {
		return readTemplate("floatToString.t").replace("@@VALUE@@", value);
	}

	if (type->is<qrtext::lua::types::Integer>()) {
		return readTemplate("boolToString.t").replace("@@VALUE@@", value);
	}

	return readTemplate("otherToString.t").replace("@@VALUE@@", value);
}
