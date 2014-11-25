#include "interpreterBase/blocksBase/common/engineCommandBlock.h"

#include <interpreterBase/robotModel/robotModelUtils.h>

using namespace interpreterBase::blocksBase::common;
using namespace interpreterBase::robotModel;

EngineCommandBlock::EngineCommandBlock(RobotModelInterface &robotModel)
	: mRobotModel(robotModel)
{
}

QMap<PortInfo, DeviceInfo> EngineCommandBlock::usedDevices()
{
	QMap<PortInfo, DeviceInfo> result;
	for (robotParts::Motor * const motor : parsePorts<robotParts::Motor>(ReportErrors::doNotReport)) {
		result[motor->port()] = motor->deviceInfo();
	}

	return result;
}

void EngineCommandBlock::timeout()
{
	emit done(mNextBlockId);
}
