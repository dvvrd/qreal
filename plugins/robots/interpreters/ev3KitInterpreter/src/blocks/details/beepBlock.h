#pragma once

#include "speakerBlock.h"

namespace ev3KitInterpreter {
namespace blocks {
namespace details {

class BeepBlock : public SpeakerBlock
{
	Q_OBJECT

public:
	explicit BeepBlock(interpreterBase::robotModel::RobotModelInterface &robotModel);
	~BeepBlock() override;

protected:
	int duration() override;
	void doJob(robotModel::parts::Ev3Speaker &speaker) override;
};

}
}
}
