#include "twoDSpeaker.h"

using namespace nxtKitInterpreter::robotModel::twoD::parts;

TwoDSpeaker::TwoDSpeaker(interpreterBase::robotModel::DeviceInfo const &info
		, interpreterBase::robotModel::PortInfo const &port
		, twoDModel::engine::TwoDModelEngineInterface &engine)
	: robotModel::parts::NxtSpeaker(info, port)
	, mEngine(engine)
{
}

void TwoDSpeaker::playTone(unsigned freq, unsigned time)
{
	Q_UNUSED(freq)
	mEngine.playSound(time);
}
