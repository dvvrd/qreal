#include "blocksTable.h"

#include <qrkernel/exception/exception.h>

using namespace qReal;
using namespace interpreterBase::blocksBase;
using namespace interpreterCore::interpreter::details;

BlocksTable::BlocksTable(BlocksFactoryManagerInterface &blocksFactoryManager
		, interpreterBase::robotModel::RobotModelManagerInterface const &robotModelManager)
	: mBlocksFactoryManager(blocksFactoryManager)
	, mRobotModelManager(robotModelManager)
{
}

BlocksTable::~BlocksTable()
{
	qDeleteAll(mBlocks);
}

BlockInterface *BlocksTable::block(Id const &element)
{
	if (mBlocks.contains(element)) {
		return mBlocks[element];
	}

	BlockInterface * const newBlock = mBlocksFactoryManager.block(element, mRobotModelManager.model());
	if (newBlock) {
		mBlocks.insert(element, newBlock);
	}

	return newBlock;
}

void BlocksTable::clear()
{
	qDeleteAll(mBlocks);
	mBlocks.clear();
}

void BlocksTable::setFailure()
{
	for (BlockInterface * const block : mBlocks.values()) {
		block->setFailedStatus();
	}
}
