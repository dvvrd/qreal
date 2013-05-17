#include <QtWidgets/QTabWidget>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtCore>

#include "../../mainwindow/mainWindow.h"
#include "../../../qrkernel/settingsManager.h"
#include "startDialog.h"
#include "suggestToCreateDiagramWidget.h"
#include "recentProjectsListWidget.h"
#include "recentProjectItem.h"

using namespace qReal;

const QSize StartDialog::mMinimumSize = QSize(350, 200);

StartDialog::StartDialog(MainWindow *mainWindow, ProjectManager *projectManager)
	: QWidget()
	, mMainWindow(mainWindow)
	, mProjectManager(projectManager)
	, mProjectListSize(5)
	, mProjectsLayout(new QVBoxLayout())
{
	setMinimumSize(mMinimumSize);

	//RecentProjectsListWidget *recentProjects = new RecentProjectsListWidget();
	SuggestToCreateDiagramWidget *diagrams = new SuggestToCreateDiagramWidget(mMainWindow);

	//QString userData=diagrams->itemAt(0);

	QString openLinkText = QString("<a href=\"Open project...\">%1</a>").arg(tr("<font color='black'>Open project...</font>"));
	QLabel *openLink = new QLabel(openLinkText, this);

	QString creatLinkText = QString("<a href=\'Create project\'>%1</a>").arg(tr("<font color='black'>Create new project</font>"));
	QLabel *createLink = new QLabel(creatLinkText, this);

	QLabel *mSessions = new QLabel(tr("<font size = 14>Sessions</font>"));
	QLabel *mRecentProjects = new QLabel(tr("<font size = 14>Recent projects</font>"));

	initRecentProjects();

	QVBoxLayout *sessionsLayout = new QVBoxLayout();

	QVBoxLayout *recentProjectsLayout = new QVBoxLayout();

	QHBoxLayout *mainLayout = new QHBoxLayout();

	sessionsLayout->addWidget(mSessions);
	sessionsLayout->addWidget(openLink);
	sessionsLayout->addWidget(createLink);

	recentProjectsLayout->addWidget(mRecentProjects);
	recentProjectsLayout->addLayout(mProjectsLayout);

	mainLayout->addLayout(sessionsLayout);
	mainLayout->addLayout(recentProjectsLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Start page"));

	connect(createLink, SIGNAL(linkActivated(const QString)), diagrams, SLOT(createProjectWithDiagram(QString)));
	connect(openLink, SIGNAL(linkActivated(const QString)), this, SLOT(openExistingProject()));
	//connect(recentProjects, SIGNAL(userDataSelected(QString)), this, SLOT(openRecentProject(QString)));
	//connect(diagrams, SIGNAL(userDataSelected(QString)), this, SLOT(createProjectWithDiagram(QString)));

	if (mainWindow)
	{
		move(mainWindow->geometry().center() - rect().center());
	}
}

void StartDialog::openRecentProject(QString const &fileName)
{
	if (mProjectManager->open(fileName)) {
		this->close();
	}
}

void StartDialog::openExistingProject()
{
	if (mProjectManager->suggestToOpenExisting()) {
		this->close();
	}
}

void StartDialog::createProjectWithDiagram(QString const &idString)
{
	mProjectManager->clearAutosaveFile();
	mProjectManager->openEmptyWithSuggestToSaveChanges();
	mMainWindow->createDiagram(idString);
	this->close();
}

void StartDialog::exitApp()
{
	this->close();
}

void StartDialog::initRecentProjects()
{
	int i=0;
	QString recentProjects = SettingsManager::value("recentProjects").toString();
	foreach (QString const &project, recentProjects.split(";", QString::SkipEmptyParts)) {
		RecentProjectItem *projectWidget = new RecentProjectItem(this, project.split("/").last().split("\\").last(), project);
		mProjectsLayout->addWidget(projectWidget);
		i++;
		if (i == mProjectListSize)
			break;
	}
}
