#pragma once

#include <QtCore/QMap>
#include <QtWidgets/QAbstractItemView>
#include <QtGui/QResizeEvent>

#include <qrgui/models/propertyEditorModel.h>
#include <qrgui/models/logicalModelAssistApi.h>

#include <qrgui/controller/controller.h>

#include <qrgui/thirdparty/qtpropertybrowser/src/qttreepropertybrowser.h>

#include "qrgui/editor/editorDeclSpec.h"
#include "qrgui/editor/private/pushButtonProperty.h"

/** @brief This widget imitates QtCreator's property editor */
class QRGUI_EDITOR_EXPORT PropertyEditorView : public QWidget
{
	Q_OBJECT

public:
	explicit PropertyEditorView(QWidget *parent = 0);
	~PropertyEditorView();

	// QAbstractItemView's methods
	void setModel(PropertyEditorModel *model);
	/** @brief editor initialization */
	void init(qReal::models::LogicalModelAssistApi &logicalModelAssistApi, qReal::Controller &controller);
	/** @brief unimplemented */
	void scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible);

	PropertyEditorModel* model() {
		return mModel;
	}
	
	void installEventFilter(QObject *obj);

signals:
	/// Emitted when user wants to edits 'Shape' property.
	void shapeEditorRequested(QPersistentModelIndex const &index, int role
		, QString const &propertyValue, bool useTypedPorts);

	/// Emitted when user wants to enter a code into a property.
	void textEditorRequested(QPersistentModelIndex const &index, int const role, QString const &propertyValue);

	/// Emitted when user wants to edit some reference property.
	void referenceListRequested(QPersistentModelIndex const &index, QString const &referenceType
			, QString const &propertyValue, int role);

public slots:

	// QAbstractItemView's methods
	void update(const QModelIndex &index);
	void setRootIndex(const QModelIndex &index);
	void reset();

protected:
	virtual void resizeEvent(QResizeEvent *event);

protected slots:
	// QAbstractItemView's methods
	void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
	void editorValueChanged(QtProperty *, QVariant);

	void buttonClicked(QtProperty *);

private:
	/** @brief returns index of value in list of possible values for index  */
	int enumPropertyIndexOf(QModelIndex const &, QString const &);
	void setPropertyValue(QtVariantProperty *property, QVariant const &value);

	bool mChangingPropertyValue;
	PropertyEditorModel *mModel;
	QtTreePropertyBrowser *mPropertyEditor;
	qReal::models::LogicalModelAssistApi *mLogicalModelAssistApi;
	QtVariantPropertyManager *mVariantManager;
	QtVariantEditorFactory *mVariantFactory;
	PushButtonPropertyManager *mButtonManager;
	PushButtonFactory *mButtonFactory;
	qReal::Controller *mController;
};
