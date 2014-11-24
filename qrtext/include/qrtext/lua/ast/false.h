#pragma once

#include "qrtext/lua/ast/expression.h"

namespace qrtext {
namespace lua {
namespace ast {

/// Represents "false" logical constant.
class QRTEXT_EXPORT False : public Expression
{
private:
	void accept(core::AstVisitorInterface &visitor) const override
	{
		static_cast<LuaAstVisitorInterface *>(&visitor)->visit(*this);
	}
};

}
}
}
