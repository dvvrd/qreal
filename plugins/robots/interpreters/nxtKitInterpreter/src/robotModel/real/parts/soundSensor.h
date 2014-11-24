#pragma once

#include <interpreterBase/robotModel/robotParts/soundSensor.h>
#include "nxtInputDevice.h"

namespace nxtKitInterpreter {
namespace robotModel {
namespace real {
namespace parts {

class SoundSensor : public interpreterBase::robotModel::robotParts::SoundSensor
{
	Q_OBJECT

public:
	SoundSensor(interpreterBase::robotModel::DeviceInfo const &info
			, interpreterBase::robotModel::PortInfo const &port
			, utils::robotCommunication::RobotCommunicator &robotCommunicator);

	void read() override;
	void doConfiguration() override;

private slots:
	void sensorSpecificProcessResponse(QByteArray const &reading);

private:
	NxtInputDevice mImplementation;
};

}
}
}
}
