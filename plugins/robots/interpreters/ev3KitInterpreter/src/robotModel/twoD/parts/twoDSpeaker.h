#pragma once

#include "robotModel/parts/nxtSpeaker.h"

#include <commonTwoDModel/engine/twoDModelEngineInterface.h>

namespace nxtKitInterpreter {
namespace robotModel {
namespace twoD {
namespace parts {

class TwoDSpeaker : public robotModel::parts::NxtSpeaker
{
	Q_OBJECT

public:
	TwoDSpeaker(interpreterBase::robotModel::DeviceInfo const &info
			, interpreterBase::robotModel::PortInfo const &port
			, twoDModel::engine::TwoDModelEngineInterface &engine);

	void playTone(unsigned freq, unsigned time) override;

private:
	twoDModel::engine::TwoDModelEngineInterface &mEngine;
};

}
}
}
}
