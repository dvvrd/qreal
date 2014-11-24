#include "nxtMotor.h"

using namespace nxtKitInterpreter::robotModel::parts;
using namespace interpreterBase::robotModel;

NxtMotor::NxtMotor(DeviceInfo const &info, interpreterBase::robotModel::PortInfo const &port)
	: interpreterBase::robotModel::robotParts::Motor(info, port)
{
}

void NxtMotor::on(int speed)
{
	on(speed, true);
}

void NxtMotor::stop()
{
	stop(true);
}

void NxtMotor::off()
{
	stop(false);
}

void NxtMotor::on(int speed, bool breakMode)
{
	on(speed, 0, breakMode);
}

void NxtMotor::on(int speed, long unsigned int degrees, bool breakMode)
{
	Q_UNUSED(speed);
	Q_UNUSED(degrees);
	Q_UNUSED(breakMode);
}

void NxtMotor::stop(bool breakMode)
{
	Q_UNUSED(breakMode);
}
