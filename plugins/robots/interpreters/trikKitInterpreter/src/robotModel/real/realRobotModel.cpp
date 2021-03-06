/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "realRobotModel.h"

#include <qrkernel/settingsManager.h>
#include <qrkernel/exception/exception.h>

#include "parts/display.h"
#include "parts/speaker.h"
#include "parts/button.h"

#include "parts/powerMotor.h"
#include "parts/servoMotor.h"
#include "parts/encoderSensor.h"

#include "parts/lightSensor.h"
#include "parts/infraredSensor.h"
#include "parts/sonarSensor.h"
#include "parts/motionSensor.h"
#include "parts/gyroscope.h"
#include "parts/accelerometer.h"
#include "parts/colorSensor.h"
#include "parts/led.h"
#include "parts/lineSensor.h"
#include "parts/objectSensor.h"
#include "parts/shell.h"
#include "parts/gamepadButton.h"
#include "parts/gamepadConnectionIndicator.h"
#include "parts/gamepadPad.h"
#include "parts/gamepadPadPressSensor.h"
#include "parts/gamepadWheel.h"

using namespace trik::robotModel::real;
using namespace kitBase::robotModel;

RealRobotModel::RealRobotModel(const QString &kitId, const QString &robotId)
	: TrikRobotModelBase(kitId, robotId)
	, mRobotCommunicator(new utils::TcpRobotCommunicator("TrikTcpServer"))
{
	connect(mRobotCommunicator.data(), &utils::TcpRobotCommunicator::connected
			, this, &RealRobotModel::connected);
	connect(mRobotCommunicator.data(), &utils::TcpRobotCommunicator::disconnected
			, this, &RealRobotModel::disconnected);
}

QString RealRobotModel::name() const
{
	return "TrikRealRobotModel";
}

QString RealRobotModel::friendlyName() const
{
	return tr("Interpretation (Wi-Fi)");
}

int RealRobotModel::priority() const
{
	return 8;  // Right after qts generator
}

bool RealRobotModel::needsConnection() const
{
	return true;
}

void RealRobotModel::connectToRobot()
{
	mRobotCommunicator->connect();
}

void RealRobotModel::stopRobot()
{
	mRobotCommunicator->stopRobot();
}

void RealRobotModel::disconnectFromRobot()
{
	mRobotCommunicator->disconnect();
}

void RealRobotModel::setErrorReporter(qReal::ErrorReporterInterface *errorReporter)
{
	mRobotCommunicator->setErrorReporter(errorReporter);
}

robotParts::Device *RealRobotModel::createDevice(const PortInfo &port, const DeviceInfo &deviceInfo)
{
	if (deviceInfo.isA(displayInfo())) {
		return new parts::Display(displayInfo(), port, *mRobotCommunicator);
	}  else if (deviceInfo.isA(speakerInfo())) {
		return new parts::Speaker(speakerInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(gamepadButtonInfo())) {
		return new parts::GamepadButton(gamepadButtonInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(gamepadPadPressSensorInfo())) {
		return new parts::GamepadPadPressSensor(gamepadPadPressSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(buttonInfo())) {
		return new parts::Button(buttonInfo(), port, buttonCodes()[port.name() + "Button"], *mRobotCommunicator);
	} else if (deviceInfo.isA(powerMotorInfo())) {
		return new parts::PowerMotor(powerMotorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(servoMotorInfo())) {
		return new parts::ServoMotor(servoMotorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(encoderInfo())) {
		return new parts::EncoderSensor(encoderInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(lightSensorInfo())) {
		return new parts::LightSensor(lightSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(infraredSensorInfo())) {
		return new parts::InfraredSensor(infraredSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(sonarSensorInfo())) {
		return new parts::SonarSensor(sonarSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(motionSensorInfo())) {
		return new parts::MotionSensor(motionSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(gyroscopeInfo())) {
		return new parts::Gyroscope(motionSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(accelerometerInfo())) {
		return new parts::Accelerometer(motionSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(lineSensorInfo())) {
		return new parts::LineSensor(lineSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(colorSensorInfo())) {
		return new parts::ColorSensor(colorSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(objectSensorInfo())) {
		return new parts::ObjectSensor(objectSensorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(ledInfo())) {
		return new parts::Led(ledInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(shellInfo())) {
		return new parts::Shell(shellInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(gamepadConnectionIndicatorInfo())) {
		return new parts::GamepadConnectionIndicator(gamepadConnectionIndicatorInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(gamepadPadInfo())) {
		return new parts::GamepadPad(gamepadPadInfo(), port, *mRobotCommunicator);
	} else if (deviceInfo.isA(gamepadWheelInfo())) {
		return new parts::GamepadWheel(gamepadWheelInfo(), port, *mRobotCommunicator);
	}

	throw qReal::Exception("Unknown device " + deviceInfo.toString() + " requested on port " + port.name());
}
