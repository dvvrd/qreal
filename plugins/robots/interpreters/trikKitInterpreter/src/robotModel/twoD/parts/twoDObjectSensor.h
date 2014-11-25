#pragma once

#include "robotModel/parts/trikObjectSensor.h"

namespace trikKitInterpreter {
namespace robotModel {
namespace twoD {
namespace parts {

/// Stub for TRIK color sensor for interpreter.
/// Does nothing until object sensor emulation will be requested for 2D model.
class ObjectSensor : public robotModel::parts::TrikObjectSensor
{
	Q_OBJECT

public:
	ObjectSensor(interpreterBase::robotModel::DeviceInfo const &info
			, interpreterBase::robotModel::PortInfo const &port);

	void init() override;
	void detect() override;
	void read() override;
};

}
}
}
}
