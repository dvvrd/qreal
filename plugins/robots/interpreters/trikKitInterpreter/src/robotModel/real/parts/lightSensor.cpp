#include "lightSensor.h"
#include <utils/tracer.h>

using namespace trikKitInterpreter::robotModel::real::parts;
using namespace interpreterBase::robotModel;

int const maxLightValue = 1023;

LightSensor::LightSensor(DeviceInfo const &info, PortInfo const &port
		, utils::TcpRobotCommunicator &tcpRobotCommunicator)
	: interpreterBase::robotModel::robotParts::LightSensor(info, port)
	, mRobotCommunicator(tcpRobotCommunicator)
{
	connect(&mRobotCommunicator, &utils::TcpRobotCommunicator::newScalarSensorData
			, this, &LightSensor::onIncomingData);
}

void LightSensor::read()
{
	mRobotCommunicator.requestData(port().name());
}

void LightSensor::onIncomingData(QString const &portName, int value)
{
	if (portName == port().name()) {
		emit newData(value);
	}
}

