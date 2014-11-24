#include "stringPropertyConverter.h"

#include "generatorBase/lua/luaProcessor.h"

using namespace generatorBase::converters;
using namespace qReal;

StringPropertyConverter::StringPropertyConverter(lua::LuaProcessor &luaTranslator
		, qReal::Id const &id
		, QString const &propertyName
		, simple::Binding::ConverterInterface *reservedVariablesConverter)
	: CodeConverterBase(luaTranslator, id, propertyName, reservedVariablesConverter)
{
}

QString StringPropertyConverter::convert(QString const &expression) const
{
	return mLuaTranslator.castToString(expression, mId, mPropertyName, mReservedVariablesConverter);
}
