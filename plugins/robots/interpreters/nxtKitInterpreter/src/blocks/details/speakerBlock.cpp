#include "speakerBlock.h"

#include <utils/tracer.h>
#include <utils/timelineInterface.h>
#include <utils/abstractTimer.h>
#include <interpreterBase/robotModel/robotModelUtils.h>

using namespace nxtKitInterpreter::blocks::details;
using namespace interpreterBase::robotModel;

SpeakerBlock::SpeakerBlock(RobotModelInterface &robotModel)
	: interpreterBase::blocksBase::common::DeviceBlock<robotModel::parts::NxtSpeaker>(robotModel)
	, mTimer(robotModel.timeline().produceTimer())
{
	mTimer->setParent(this);
	connect(mTimer, &utils::AbstractTimer::timeout, this, &SpeakerBlock::timeout);
}

void SpeakerBlock::run()
{
	DeviceBlock::run();
	if (errorsOccured()) {
		return;
	}

	if (!boolProperty("WaitForCompletion"))
		emit done(mNextBlockId);
	else {
		mTimer->start(duration());
	}
}

void SpeakerBlock::timeout()
{
	utils::Tracer::debug(utils::Tracer::blocks, "TimerBlock::timeout", "emit done(mNextBlock)");
	emit done(mNextBlockId);
}
