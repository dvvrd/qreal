#include <QtWidgets/QTabWidget>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtCore>


#include "startDialog.h"
#include "suggestToCreateDiagramWidget.h"
#include "recentProjectsListWidget.h"
#include "../../mainwindow/mainWindow.h"

using namespace qReal;

const QSize StartDialog::mMinimumSize = QSize(350, 200);

StartDialog::StartDialog(MainWindow *mainWindow, ProjectManager *projectManager)
		: ManagedClosableDialog(mainWindow, false)
		, mMainWindow(mainWindow)
		, mProjectManager(projectManager)
{
	setMinimumSize(mMinimumSize);

	RecentProjectsListWidget *recentProjects = new RecentProjectsListWidget();
	SuggestToCreateDiagramWidget *diagrams = new SuggestToCreateDiagramWidget(mMainWindow);

	//QString userData=diagrams->itemAt(0);

	QString openLinkText = QString("<a href=\"Open project...\">%1</a>").arg(tr("<font color='black'>Open project...</font>"));
	QLabel* openLink = new QLabel(openLinkText, this);

	QString creatLinkText = QString("<a href=\'Create project\'>%1</a>").arg(tr("<font color='black'>Create new project</font>"));
	QLabel* createLink = new QLabel(creatLinkText, this);

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(recentProjects, 0, 0);
	mainLayout->addWidget(openLink, 1, 0);
	mainLayout->addWidget(createLink, 1, 1);

	setLayout(mainLayout);
	setWindowTitle(tr("Start page"));

	//connect(createLink, SIGNAL(linkActivated(const QString)), diagrams, SLOT(createProjectWithDiagram(QString)));
	connect(openLink, SIGNAL(linkActivated(const QString)), this, SLOT(openExistingProject()));
	connect(recentProjects, SIGNAL(userDataSelected(QString)), this, SLOT(openRecentProject(QString)));
	connect(diagrams, SIGNAL(userDataSelected(QString)), this, SLOT(createProjectWithDiagram(QString)));

	if (mainWindow)
	{
		move(mainWindow->geometry().center() - rect().center());
	}
}

void StartDialog::openRecentProject(QString const &fileName)
{
	if (mProjectManager->open(fileName)) {
		forceClose();
	}
}

void StartDialog::openExistingProject()
{
	if (mProjectManager->suggestToOpenExisting()) {
		forceClose();
	}
}

void StartDialog::createProjectWithDiagram(QString const &idString)
{
	mProjectManager->clearAutosaveFile();
	mProjectManager->openEmptyWithSuggestToSaveChanges();
	mMainWindow->createDiagram(idString);
	forceClose();
}

void StartDialog::exitApp()
{
	forceClose();
}
