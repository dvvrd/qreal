#include <QtWidgets/QTabWidget>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtCore>

#include "../../mainwindow/mainWindow.h"
#include "../../../qrkernel/settingsManager.h"
#include "startDialog.h"
#include "suggestToCreateDiagramWidget.h"
#include "recentProjectsListWidget.h"
#include "recentProjectItem.h"

using namespace qReal;

StartWidget::StartWidget(MainWindow *mainWindow, ProjectManager *projectManager)
	: QWidget()
	, mMainWindow(mainWindow)
	, mProjectManager(projectManager)
	, mProjectListSize(5)
	, mProjectsLayout(new QVBoxLayout())
	, mSessionsLayout(new QHBoxLayout())
{
	//RecentProjectsListWidget *recentProjects = new RecentProjectsListWidget();
	SuggestToCreateDiagramWidget *diagrams = new SuggestToCreateDiagramWidget(mMainWindow);

	//QString userData=diagrams->itemAt(0);

	QString openLinkText = QString("<a href=\"Open project...\">%1</a>").arg(tr("<font color='black'>Open project...</font>"));
	QLabel *openLink = new QLabel(openLinkText, this);

	QString creatLinkText = QString("<a href=\'Create project\'>%1</a>").arg(tr("<font color='black' >Create new project</font>"));
	QLabel *createLink = new QLabel(creatLinkText, this);

	QLabel *sessions = new QLabel(tr("<font size = 14>Sessions</font>"));
	QLabel *recentProjects = new QLabel(tr("<font size = 14>Recent projects</font>"));

	initRecentProjects();

	QVBoxLayout *sessionsLayout = new QVBoxLayout();

	QVBoxLayout *recentProjectsLayout = new QVBoxLayout();

	QHBoxLayout *mainLayout = new QHBoxLayout();

	sessionsLayout->addWidget(sessions);
	sessionsLayout->addLayout(mSessionsLayout);
	sessionsLayout->addWidget(openLink);
	sessionsLayout->addWidget(createLink);
	sessionsLayout->addStretch(0);

	recentProjectsLayout->addWidget(recentProjects);
	recentProjectsLayout->addLayout(mProjectsLayout);
	//recentProjectsLayout->addItem(new QSpacerItem(1, 400));
	recentProjectsLayout->addStretch(0);

	mainLayout->addLayout(sessionsLayout);
	QWidget *horizontalLineWidget = new QWidget;
	horizontalLineWidget->setFixedWidth(1);
	horizontalLineWidget->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Expanding);
	horizontalLineWidget->setStyleSheet(QString("background-color: #c0c0c0;"));
	mainLayout->addWidget(horizontalLineWidget);
	mainLayout->addLayout(recentProjectsLayout);

	setLayout(mainLayout);
	QPalette Pal(palette());
	QColor color = QColor::fromHsl (180, 50, 240, 255);
	Pal.setColor(QPalette::Background, color);
	this->setAutoFillBackground(true);
	this->setPalette(Pal);
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

void StartWidget::openRecentProject(QString const &fileName)
{
	if (mProjectManager->open(fileName)) {
		this->close();
	}
}

void StartWidget::openExistingProject()
{
	if (mProjectManager->suggestToOpenExisting()) {
		this->close();
	}
}

void StartWidget::createProjectWithDiagram(QString const &idString)
{
	mProjectManager->clearAutosaveFile();
	mProjectManager->openEmptyWithSuggestToSaveChanges();
	mMainWindow->createDiagram(idString);
	this->close();
}

void StartWidget::exitApp()
{
	this->close();
}

void StartWidget::initRecentProjects()
{
	int i=0;
	QString recentProjects = SettingsManager::value("recentProjects").toString();
	foreach (QString const &project, recentProjects.split(";", QString::SkipEmptyParts)) {
		QString const name = project.split("/").last().split("\\").last();
		if("autosave.qrs"== name){
			QString currentProject = QString("<a href='%2'>%1</a>").arg(tr("<font color='black'>•  default (current session)</font>"), project);
			QLabel *currentProjectLabel = new QLabel(currentProject, this);
			mSessionsLayout->addSpacing(25);
			mSessionsLayout->addWidget(currentProjectLabel);
		} else {
			RecentProjectItem *projectWidget = new RecentProjectItem(this, name, project);
			mProjectsLayout->addWidget(projectWidget);
			i++;
			if (i == mProjectListSize)
				break;
		}
	}
}
