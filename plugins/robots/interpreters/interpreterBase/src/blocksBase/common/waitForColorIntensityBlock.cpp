#include "interpreterBase/blocksBase/common/waitForColorIntensityBlock.h"

using namespace interpreterBase;
using namespace blocksBase::common;

WaitForColorIntensityBlock::WaitForColorIntensityBlock(interpreterBase::robotModel::RobotModelInterface &robotModel)
	: WaitForColorSensorBlockBase(robotModel)
{
}

void WaitForColorIntensityBlock::responseSlot(int reading)
{
	int const result = eval<int>("Intensity");
	if (!errorsOccured()) {
		processResponce(reading, result);
	}
}
