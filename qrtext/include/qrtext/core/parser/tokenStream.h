#pragma once

#include <QtCore/QString>

#include "qrtext/core/lexer/token.h"
#include "qrtext/core/error.h"

namespace qrtext {
namespace core {

/// Stream of tokens.
template<typename TokenType>
class TokenStream
{
public:
	/// Constructor. Takes list of tokens and names of tokens (for error reporting) from lexer and a reference to error
	/// stream where to put errors.
	TokenStream(QList<Token<TokenType>> const &tokenList, QHash<TokenType, QString> const &tokenUserFriendlyNames
			, QList<Error> &errorList)
		: mTokenList(tokenList), mErrorList(errorList), mTokenUserFriendlyNames(tokenUserFriendlyNames), mPosition(0)
	{
	}

	/// Returns next token, or last token if there is end of stream.
	Token<TokenType> next() const
	{
		if (mPosition >= mTokenList.size()) {
			return mTokenList.last();
		}

		return mTokenList.at(mPosition);
	}

	/// Advances stream.
	void consume()
	{
		++mPosition;
	}

	/// Advances stream if current token is the expected one, raises error otherwise.
	bool expect(TokenType token)
	{
		if (next().token() == token) {
			consume();
			return true;
		} else {
			mErrorList << Error(next().range().start()
					, QString(QObject::tr("Expected \"%1\", got \"%2\""))
							.arg(mTokenUserFriendlyNames[token])
							.arg(mTokenUserFriendlyNames[next().token()])
					, ErrorType::syntaxError
					, Severity::error);

			return false;
		}
	}

	/// Returns true, if end of token stream is reached.
	bool isEnd()
	{
		return mPosition == mTokenList.size();
	}

private:
	QList<Token<TokenType>> mTokenList;
	QList<Error> &mErrorList;
	QHash<TokenType, QString> mTokenUserFriendlyNames;
	int mPosition;
};

}
}
