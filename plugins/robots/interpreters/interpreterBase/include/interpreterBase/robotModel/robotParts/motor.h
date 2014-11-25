#pragma once

#include "device.h"
#include "interpreterBase/interpreterBaseDeclSpec.h"

namespace interpreterBase {
namespace robotModel {
namespace robotParts {

/// Abstract motor which can be turned on with given speed or turned off.
class ROBOTS_INTERPRETER_BASE_EXPORT Motor : public Device
{
	Q_OBJECT
	Q_CLASSINFO("name", "motor")
	Q_CLASSINFO("friendlyName", tr("Motor"))
	Q_CLASSINFO("direction", "output")

public:
	/// Constructor, takes device type info and port on which this motor is configured.
	Motor(DeviceInfo const &info, PortInfo const &port);

	/// Turn on a motor with given speed (commonly in range -100..100, but it may depend on concrete motor).
	virtual void on(int speed);

	/// Stops motor actively, with breaking. For NXT and TRIK it is equivalent to on(0), but may depend on motor
	/// construction. Note that motor still be on and in most real motors it even will consume maximal amount of power
	/// in this mode (somewhat counter-intuitive).
	virtual void stop();

	/// Turns off electrical supply, which stops motor without breaking. Note that on real motors it is completely
	/// different from "stop()", but in 2D model "stop()" and "off()" behave basically the same way (some differences
	/// may be noted in advanced physics mode, related to breaking).
	virtual void off();
};

}
}
}
