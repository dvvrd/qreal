#pragma once

#include "robotModel/parts/trikObjectSensor.h"
#include <utils/tcpRobotCommunicator.h>

namespace trikKitInterpreter {
namespace robotModel {
namespace real {
namespace parts {

/// Stub for TRIK color sensor for interpreter.
class ObjectSensor : public robotModel::parts::TrikObjectSensor
{
	Q_OBJECT

public:
	ObjectSensor(interpreterBase::robotModel::DeviceInfo const &info
			, interpreterBase::robotModel::PortInfo const &port
			, utils::TcpRobotCommunicator &robotCommunicator);

	void init() override;
	void detect() override;
	void read() override;

private:
	utils::TcpRobotCommunicator &mRobotCommunicator;
};

}
}
}
}
