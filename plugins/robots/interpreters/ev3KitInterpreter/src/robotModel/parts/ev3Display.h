#pragma once

#include <interpreterBase/robotModel/robotParts/display.h>

namespace ev3KitInterpreter {
namespace robotModel {
namespace parts {

class Ev3Display : public interpreterBase::robotModel::robotParts::Display
{
	Q_OBJECT

public:
	Ev3Display(interpreterBase::robotModel::DeviceInfo const &info, interpreterBase::robotModel::PortInfo const &port);

	virtual void drawCircle(int x, int y, int radius, bool filled) = 0;
	virtual void drawRect(int x, int y, int width, int height, bool filled) = 0;
};

}
}
}
