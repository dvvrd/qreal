#pragma once

#include <qrkernel/ids.h>

#include "view/gestures/keyManagerInterface.h"
#include "view/gestures/keyManager.h"
#include "pluginManager/editorManagerInterface.h"
#include "mainwindow/gesturesPainterInterface.h"
#include "view/gestures/abstractRecognizer.h"
#include <QtCore/QPointF>
#include <QtCore/QPoint>
#include <QtCore/QLineF>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QMap>

namespace qReal {
namespace gestures {

class MouseMovementManager
{
public:
	/// Specifies the type of the result of the gesture made by user: regular element creation or some metagesture
	/// (e.g. element deletion).
	enum GestureResultType
	{
		invalidGesture
		, createElementGesture
		, deleteGesture
	};

	/// Specifies the result of the gesture made.
	struct GestureResult
	{
	public:
		GestureResult();
		explicit GestureResult(GestureResultType type, Id const &id = Id());

		/// Returns the resulting type of the gesture.
		GestureResultType type() const;

		/// Returns the type of the element requested by the gesture.
		Id elementType() const;

		/// Returns the resulting type of the gesture.
		void setType(GestureResultType type);

		/// Sets the type of the element requested by the gesture.
		void setElementType(Id const &id);

	private:
		GestureResultType mType;
		Id mId;
	};

	MouseMovementManager(QList<Id> elements, EditorManagerInterface *editorManagerInterface
			, GesturesPainterInterface *gesturesPaintManager);

	~MouseMovementManager();

	void setElements(IdList const &elements);
	void mousePress(QPointF const &point);
	void mouseMove(QPointF const &point);
	void clear();
	void setGesturesPainter(GesturesPainterInterface *gesturesPainter);
	GestureResult result();
	static PathVector stringToPath(QString const &str);
	QPointF pos();
	QPointF firstPoint();
	QPointF lastPoint();
	QLineF newLine();
	void printElements();
	void drawIdealPath();
	bool wasMoving();
	bool isEdgeCandidate();
	bool pathIsEmpty();

private:
	static QPoint parsePoint(QString const &str);
	void recountCentre();
	PathVector mPath;
	IKeyManager *mKeyManager;
	KeyManager mKeyStringManager;
	EditorManagerInterface * mEditorManagerInterface;
	QList<Id> mElements;
	QPointF mCentre;
	GesturesPainterInterface *mGesturesPaintMan;
	GesturesManager *mGesturesManager;
};

}
}
