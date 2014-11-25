#include "model.h"

#include <qrkernel/settingsManager.h>

#include "include/commonTwoDModel/robotModel/nullTwoDRobotModel.h"

using namespace twoDModel::model;

Model::Model(QObject *parent)
	: QObject(parent)
{
}

WorldModel &Model::worldModel()
{
	return mWorldModel;
}

Timeline &Model::timeline()
{
	return mTimeline;
}

QList<RobotModel *> Model::robotModels()
{
	return mRobotModels;
}

Settings &Model::settings()
{
	return mSettings;
}

QDomDocument Model::serialize() const
{
	QDomDocument save;
	QDomElement root = save.createElement("root");
	save.appendChild(root);
	root.appendChild(mWorldModel.serialize(save, QPoint(0, 0)));

	QDomElement robots = save.createElement("robots");
	for (RobotModel *robotModel : mRobotModels) {
		QDomElement robot = robotModel->serialize(save);
		robots.appendChild(robot);
	}

	root.appendChild(robots);

	return save;
}

void Model::deserialize(QDomDocument const &xml)
{
	QDomNodeList const worldList = xml.elementsByTagName("world");
	QDomNodeList const robotsList = xml.elementsByTagName("robots");

	if (worldList.count() != 1) {
		/// @todo Report error
		return;
	}

	mWorldModel.deserialize(worldList.at(0).toElement());

	if (robotsList.count() != 1) {
		// need for backward compatibility with old format
		QDomNodeList const robotList = xml.elementsByTagName("robot");

		if (robotList.count() != 1) {
			/// @todo Report error
			return;
		}

		mRobotModels.at(0)->deserialize(robotList.at(0).toElement());
		mRobotModels.at(0)->configuration().deserialize(robotList.at(0).toElement());

		return;
	}

	QMutableListIterator<RobotModel *> iterator(mRobotModels);

	bool const oneRobot = robotsList.at(0).toElement().elementsByTagName("robot").size() == 1
			&& mRobotModels.size() == 1;

	while(iterator.hasNext()) {
		bool exist = false;
		RobotModel *robotModel = iterator.next();

		for (QDomElement element = robotsList.at(0).firstChildElement("robot"); !element.isNull();
				element = element.nextSiblingElement("robot")) {
			if (robotModel->info().robotId() == element.toElement().attribute("id")) {
				robotModel->deserialize(element);
				robotModel->configuration().deserialize(element);
				exist = true;
				robotsList.at(0).removeChild(static_cast<QDomNode>(element));
				break;
			}
		}

		if (!exist && !oneRobot) {
			iterator.remove();
			emit robotRemoved(robotModel);
			delete robotModel;
		}
	}

	if (oneRobot && !robotsList.at(0).firstChildElement("robot").isNull()) {
		QDomElement element = robotsList.at(0).firstChildElement("robot");
		mRobotModels.at(0)->deserialize(element);
	} else {
		for (QDomElement element = robotsList.at(0).firstChildElement("robot"); !element.isNull();
				element = element.nextSiblingElement("robot")) {
			twoDModel::robotModel::NullTwoDRobotModel *robotModel = new twoDModel::robotModel::NullTwoDRobotModel(
					element.attribute("id"));
			addRobotModel(*robotModel);
			mRobotModels.last()->deserialize(element);
		}
	}
}

void Model::addRobotModel(robotModel::TwoDRobotModel &robotModel, QPointF const &pos)
{
	RobotModel *robot = new RobotModel(robotModel, mSettings, this);
	robot->setPosition(pos);

	connect(&mTimeline, &Timeline::started, robot, &RobotModel::reinit);
	connect(&mTimeline, &Timeline::stopped, robot, &RobotModel::stopRobot);

	connect(&mTimeline, &Timeline::tick, robot, &RobotModel::recalculateParams);
	connect(&mTimeline, &Timeline::nextFrame, robot, &RobotModel::nextFragment);

	auto resetPhysics = [this, robot]() { robot->resetPhysics(mWorldModel, mTimeline); };
	connect(&mSettings, &Settings::physicsChanged, resetPhysics);
	resetPhysics();

	mRobotModels.append(robot);

	emit robotAdded(robot);
}

void Model::removeRobotModel(twoDModel::robotModel::TwoDRobotModel const &robotModel)
{
	int const index = findModel(robotModel);

	if (index == -1) {
		return;
	}

	RobotModel *robot = mRobotModels.at(index);
	mRobotModels.removeOne(mRobotModels.at(index));
	emit robotRemoved(robot);
	delete robot;
}

void Model::replaceRobotModel(twoDModel::robotModel::TwoDRobotModel const &oldModel
		, twoDModel::robotModel::TwoDRobotModel &newModel)
{
	int const index = findModel(oldModel);

	if (index == -1) {
		return;
	}

	QPointF const pos = mRobotModels.at(index)->position();
	removeRobotModel(oldModel);
	addRobotModel(newModel, pos);
}

int Model::findModel(twoDModel::robotModel::TwoDRobotModel const &robotModel)
{
	for (int i = 0; i < mRobotModels.count(); i++) {
		if (mRobotModels.at(i)->info().robotId() == robotModel.robotId()) {
			return i;
		}
	}

	return -1;
}
