#pragma once

#include "waitForSensorBlock.h"

namespace interpreterBase {
namespace blocksBase {
namespace common {

/// A base for all color sensor`s wait blocks.
class ROBOTS_INTERPRETER_BASE_EXPORT WaitForColorSensorBlockBase : public WaitForSensorBlock
{
	Q_OBJECT

public:
	/// Constructor, takes current robot model as parameter.
	explicit WaitForColorSensorBlockBase(robotModel::RobotModelInterface &robotModel);

protected:
	robotModel::DeviceInfo device() const override;
};

}
}
}
