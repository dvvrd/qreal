#pragma once

#include "waitForSensorBlock.h"

namespace interpreterBase {
namespace blocksBase {
namespace common {

/// An interpreter`s implementation for "wait for sonar sensor" block.
class ROBOTS_INTERPRETER_BASE_EXPORT WaitForSonarDistanceBlock : public WaitForSensorBlock
{
	Q_OBJECT

public:
	/// Constructor, takes current robot model as parameter.
	WaitForSonarDistanceBlock(robotModel::RobotModelInterface &robotModel, robotModel::DeviceInfo const &device);

protected slots:
	void responseSlot(int reading) override;

protected:
	interpreterBase::robotModel::DeviceInfo device() const override;

private:
	interpreterBase::robotModel::DeviceInfo const mDevice;
};

}
}
}
