#include "powerMotor.h"

#include <qrutils/inFile.h>

using namespace trikKitInterpreter::robotModel::real::parts;
using namespace interpreterBase::robotModel;

PowerMotor::PowerMotor(DeviceInfo const &info, PortInfo const &port
		, utils::TcpRobotCommunicator &tcpRobotCommunicator)
	: robotModel::parts::TrikPowerMotor(info, port)
	, mRobotCommunicator(tcpRobotCommunicator)
{
}

void PowerMotor::on(int speed)
{
	QString const pathToCommand = ":/trikQts/templates/engines/forward.t";
	QString const directCommand = utils::InFile::readAll(pathToCommand)
			.replace("@@PORT@@", "\"" + port().name() + "\"")
			.replace("@@POWER@@", QString::number(speed)) + "brick.run();";

	mRobotCommunicator.runDirectCommand(directCommand);
}

void PowerMotor::stop()
{
	on(0);
}

void PowerMotor::off()
{
	/// @todo It shall be a separate command, to power off motor, not to leave it in blocked state.
	on(0);
}
