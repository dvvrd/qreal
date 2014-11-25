#pragma once

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QSignalMapper>

#include <qrkernel/ids.h>
#include <qrgui/mainWindow/mainWindowInterpretersInterface.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/graphicalModelAssistInterface.h>

#include <interpreterBase/blocksBase/blockInterface.h>

#include "blocksTable.h"

namespace interpreterCore {
namespace interpreter {
namespace details {

/// Program execution thread. Has currently executed block, and its own stack.
class Thread : public QObject
{
	Q_OBJECT

public:
	/// Creates new instance of thread starting from specified block.
	/// @param graphicalModelApi - graphical model, contains diagram.
	/// @param interpretersInterface - reference to QReal main window.
	/// @param blocksTable - interpreter-wide table of blocks (map from ids to "code-behind" objects).
	/// @param initialNode - node that shall be executed first in this thread.
	Thread(qReal::GraphicalModelAssistInterface const *graphicalModelApi
			, qReal::gui::MainWindowInterpretersInterface &interpretersInterface
			, BlocksTable &blocksTable
			, qReal::Id const &initialNode);

	/// Creates new instance of thread starting from initial node of specified diagram.
	/// @param graphicalModelApi - graphical model, contains diagram.
	/// @param interpretersInterface - reference to QReal main window.
	/// @param diagramToInterpret - diagram, whose initial node shall be executed in a new thread.
	/// @param blocksTable - interpreter-wide table of blocks (map from ids to "code-behind" objects).
	Thread(qReal::GraphicalModelAssistInterface const *graphicalModelApi
			, qReal::gui::MainWindowInterpretersInterface &interpretersInterface
			, qReal::Id const &diagramToInterpret
			, BlocksTable &blocksTable);

	~Thread() override;

	/// Starts interpretation process starting from the block specified in one of the constructors.
	void interpret();

signals:
	/// Emitted when interpretation process was terminated (correctly or due to errors).
	void stopped();

	/// Emitted when one of the blocks interpreted by this thread requested new thread.
	void newThread(qReal::Id const &startBlockId);

private slots:
	void nextBlock(qReal::Id const &blockId);

	void stepInto(qReal::Id const &diagram);
	void finishedSteppingInto();

	void failure();

	void interpretAfterEventsProcessing(QObject *block);

private:
	void initTimer();

	qReal::Id findStartingElement(qReal::Id const &diagram) const;
	void error(QString const &message, qReal::Id const &source = qReal::Id());

	void turnOn(interpreterBase::blocksBase::BlockInterface * const block);
	void turnOff(interpreterBase::blocksBase::BlockInterface * const block);

	qReal::GraphicalModelAssistInterface const *mGraphicalModelApi;  // Doesn't have ownership
	qReal::gui::MainWindowInterpretersInterface &mInterpretersInterface;
	BlocksTable &mBlocksTable;
	interpreterBase::blocksBase::BlockInterface *mCurrentBlock;  // Doesn't have ownership
	QStack<interpreterBase::blocksBase::BlockInterface *> mStack;  // Doesn't have ownership
	qReal::Id const mInitialDiagram;
	int mBlocksSincePreviousEventsProcessing;
	QTimer *mProcessEventsTimer;  // Has ownership
	QSignalMapper *mProcessEventsMapper;  // Has ownership
};

}
}
}
