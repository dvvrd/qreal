#include "mouseMovementManager.h"

#include "view/gestures/pathCorrector.h"
#include "view/gestures/levenshteinDistance.h"
#include "view/gestures/geometricForms.h"
#include "view/gestures/mixedgesturesmanager.h"

QString const comma = ", ";
QString const pointDelimeter = " : ";
QString const pathDelimeter = " | ";

QString const deletionGestureKey = "<deletionMetaGesture>";
/// @todo: specify it in metamodel?
QString const deletionGesture = "0, 200 : 200, 0 : ";

using namespace qReal::gestures;

MouseMovementManager::MouseMovementManager(QList<qReal::Id> elements
		, qReal::EditorManagerInterface * editorManagerInterface
		, GesturesPainterInterface *gesturesPaintManager)
{
	mGesturesManager = new MixedGesturesManager();
	mKeyManager = &mKeyStringManager;
	mEditorManagerInterface = editorManagerInterface;
	mGesturesPaintMan = gesturesPaintManager;
	setElements(elements);
}

MouseMovementManager::~MouseMovementManager()
{
	delete mGesturesManager;
}

void MouseMovementManager::setGesturesPainter(GesturesPainterInterface *gesturesPainter)
{
	mGesturesPaintMan = gesturesPainter;
}

void MouseMovementManager::drawIdealPath()
{
	Id const currentElement = mGesturesPaintMan->currentElement();
	if (mElements.contains(currentElement)) {
		QString const paths = mEditorManagerInterface->mouseGesture(currentElement);
		mGesturesPaintMan->draw(stringToPath(paths));
	}
}

void MouseMovementManager::printElements()
{
	QList<QPair<QString, Id> > elements;
	foreach (Id const &element, mElements) {
		elements << qMakePair(mEditorManagerInterface->friendlyName(element), element);
	}
	mGesturesPaintMan->setElements(elements);
}

void MouseMovementManager::clear()
{
	mPath.clear();
}

QLineF MouseMovementManager::newLine()
{
	QLineF line;
	if (mPath.back().size() > 1) {
		line.setP1(mPath.back().at(mPath.back().size() - 2));
		line.setP2(mPath.back().back());
	}
	return line;
}

void MouseMovementManager::setElements(IdList const &elements)
{
	QMap<QString, PathVector> gestures;
	gestures.insert(deletionGestureKey, stringToPath(deletionGesture));
	for (Id const &element : elements) {
		QString const pathStr = mEditorManagerInterface->mouseGesture(element);
		if (!pathStr.isEmpty()) {
			gestures.insert(element.toString(), stringToPath(pathStr));
			mElements << element;
		}
	}

	mGesturesManager->initIdealGestures(gestures);
}

void MouseMovementManager::recountCentre()
{
	if (mPath.empty() || mPath.back().empty()) {
		return;
	}
	int count = 0;
	foreach (PointVector const &path, mPath) {
		count += path.size();
	}
	mCentre = ((count - 1) * mCentre + mPath.back().back()) / count;
}

void MouseMovementManager::mousePress(QPointF const & pnt)
{
	QList<QPointF> path;
	path.push_back(pnt);
	mPath.push_back(path);
	recountCentre();
}

void MouseMovementManager::mouseMove(QPointF const & pnt)
{
	PointVector path = mPath.back();
	mPath.pop_back();
	path.push_back(pnt);
	mPath.push_back(path);
	recountCentre();
}

QPointF MouseMovementManager::pos()
{
	return mCentre;
}

PathVector MouseMovementManager::stringToPath(QString const &valueStr)
{
	PathVector result;
	QStringList paths = valueStr.split(pathDelimeter, QString::SkipEmptyParts);
	foreach(QString pathStr, paths) {
		QStringList points = pathStr.split(pointDelimeter, QString::SkipEmptyParts);
		PointVector path;
		foreach (QString str, points) {
			QPointF point = parsePoint(str);
			path.push_back(point);
		}
		result.push_back(path);
	}
	return result;
}

QPoint MouseMovementManager::parsePoint(QString const &str)
{
	bool isInt = true;
	int x = str.section(comma, 0, 0).toInt(&isInt, 0);
	int y = str.section(comma, 1, 1).toInt(&isInt, 0);
	return QPoint(x, y);
}

MouseMovementManager::GestureResult MouseMovementManager::result()
{
	GestureResult result;
	mGesturesManager->setKey(mPath);
	mPath.clear();
	qreal minDist = INT_MAX;

	QMap<QString, Id> gestures;
	gestures[deletionGestureKey] = Id();
	for (Id const &element : mElements) {
		gestures[element.toString()] = element;
	}


	for (QString const &key: gestures.keys()) {
		minDist = qMin(minDist, mGesturesManager->getMaxDistance(key));
		qreal const dist = mGesturesManager->getDistance(key);
		if (dist < minDist) {
			minDist = dist;
			result.setType(key == deletionGestureKey ? deleteGesture : createElementGesture);
			result.setElementType(gestures[key]);
		}
	}

	return result;
}

QPointF MouseMovementManager::firstPoint()
{
	if (!mPath.isEmpty() && !mPath.at(0).empty()) {
		return QPointF(mPath.at(0).at(0));
	}
	return QPointF(0, 0);
}

QPointF MouseMovementManager::lastPoint()
{
	if (!mPath.isEmpty() && !mPath.back().empty()) {
		return QPointF(mPath.back().back());
	}
	return QPointF(0, 0);
}

bool MouseMovementManager::wasMoving()
{
	return (firstPoint() != lastPoint() || mPath.size() > 1 ||
			(!mPath.isEmpty() && mPath.at(0).size() > 2));
}

bool MouseMovementManager::isEdgeCandidate()
{
	return mPath.count() <= 1;
}

bool MouseMovementManager::pathIsEmpty()
{
	return mPath.isEmpty();
}

MouseMovementManager::GestureResult::GestureResult()
	: mType(invalidGesture)
{
}

MouseMovementManager::GestureResult::GestureResult(MouseMovementManager::GestureResultType type, qReal::Id const &id)
	: mType(type)
	, mId(id)
{
}

MouseMovementManager::GestureResultType MouseMovementManager::GestureResult::type() const
{
	return mType;
}

qReal::Id MouseMovementManager::GestureResult::elementType() const
{
	return mId;
}

void MouseMovementManager::GestureResult::setType(MouseMovementManager::GestureResultType type)
{
	mType = type;
}

void MouseMovementManager::GestureResult::setElementType(qReal::Id const &id)
{
	mId = id;
}
