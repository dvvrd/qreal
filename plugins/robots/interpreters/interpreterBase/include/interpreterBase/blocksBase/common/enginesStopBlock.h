#pragma once

#include <interpreterBase/blocksBase/common/engineCommandBlock.h>

namespace interpreterBase {
namespace blocksBase {
namespace common {

/// An interpreter`s implementation for the motors stop block.
class ROBOTS_INTERPRETER_BASE_EXPORT EnginesStopBlock : public EngineCommandBlock
{
	Q_OBJECT

public:
	/// Constructor, takes current robot model as parameter.
	explicit EnginesStopBlock(robotModel::RobotModelInterface &robotModel);

	void run() override;
};

}
}
}
