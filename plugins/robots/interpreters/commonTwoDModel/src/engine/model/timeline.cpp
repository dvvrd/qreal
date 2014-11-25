#include <QtCore/QDateTime>

#include "timeline.h"
#include "modelTimer.h"

using namespace twoDModel::model;

Timeline::Timeline(QObject *parent)
	: QObject(parent)
	, mSpeedFactor(normalSpeedFactor)
	, mCyclesCount(0)
	, mIsStarted(false)
{
	connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
	mTimer.setInterval(realTimeInterval);
}

void Timeline::start()
{
	if (!mIsStarted) {
		mIsStarted = true;
		emit started();
		gotoNextFrame();
	}
}

void Timeline::stop()
{
	mIsStarted = false;
	emit stopped();
}

void Timeline::onTimer()
{
	if (!mIsStarted) {
		mTimer.stop();
		return;
	}

	for (int i = 0; i < ticksPerCycle; ++i) {
		mTimestamp += timeInterval;
		emit tick();
		++mCyclesCount;
		if (mCyclesCount >= mSpeedFactor) {
			mTimer.stop();
			mCyclesCount = 0;
			int const msFromFrameStart = static_cast<int>(QDateTime::currentMSecsSinceEpoch()
					- mFrameStartTimestamp);
			int const pauseBeforeFrameEnd = frameLength - msFromFrameStart;
			if (pauseBeforeFrameEnd > 0) {
				QTimer::singleShot(pauseBeforeFrameEnd - 1, this, SLOT(gotoNextFrame()));
			} else {
				gotoNextFrame();
			}
			return;
		}
	}
}

void Timeline::gotoNextFrame()
{
	emit nextFrame();
	mFrameStartTimestamp = QDateTime::currentMSecsSinceEpoch();
	if (!mTimer.isActive()) {
		mTimer.start();
	}
}

int Timeline::speedFactor() const
{
	return mSpeedFactor;
}

quint64 Timeline::timestamp() const
{
	return mTimestamp;
}

utils::AbstractTimer *Timeline::produceTimer()
{
	return new ModelTimer(this);
}

void Timeline::setSpeedFactor(int factor)
{
	mSpeedFactor = factor;
}
