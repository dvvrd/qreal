#pragma once

#include "editor/commands/nodeElementCommand.h"

namespace qReal {
namespace commands {

class FoldCommand : public NodeElementCommand
{
public:
	FoldCommand(NodeElement const *element);
	virtual ~FoldCommand() {}

protected:
	bool execute();
	bool restoreState();

private:
	void changeFoldState();
};

}
}
