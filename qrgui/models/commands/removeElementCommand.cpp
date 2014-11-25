#include "removeElementCommand.h"

using namespace qReal::commands;

RemoveElementCommand::RemoveElementCommand(
		models::LogicalModelAssistApi &logicalApi
		, models::GraphicalModelAssistApi &graphicalApi
		, models::Exploser const &exploser
		, Id const &logicalParent
		, Id const &graphicalParent
		, Id const &id
		, bool isFromLogicalModel
		, QString const &name
		, QPointF const &position)
	: mImpl(logicalApi, graphicalApi, exploser, logicalParent, graphicalParent
			, id, isFromLogicalModel, name, position)
{
}

bool RemoveElementCommand::execute()
{
	mImpl.remove();
	return true;
}

bool RemoveElementCommand::restoreState()
{
	mImpl.create();
	return true;
}

qReal::Id RemoveElementCommand::elementId() const
{
	return mImpl.id();
}

bool RemoveElementCommand::equals(AbstractCommand const &other) const
{
	RemoveElementCommand const *removeCommand = dynamic_cast<RemoveElementCommand const *>(&other);
	if (removeCommand) {
		return mImpl == removeCommand->mImpl;
	}

	return false;
}
