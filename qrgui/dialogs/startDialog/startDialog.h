#pragma once
#include <QtWidgets/QVBoxLayout>

#include "../managedClosableDialog.h"
#include "../../mainwindow/projectManager/projectManager.h"

namespace qReal {

class MainWindow;

/**
 * @brief Start page dialog
 *
 * Start page dialog that allows the user to either open an existing project (from list of recent
 * projects or not), or create a new one and did not appear in the main window of application,
 * where there is no single project.
 */
class StartWidget : public QWidget
{
	Q_OBJECT

public:
	explicit StartWidget(MainWindow *mainWindow, ProjectManager *projectManager);

private slots:
	void openRecentProject(QString const &fileName);
	void openExistingProject();
	void createProjectWithDiagram(QString const &idString);
	void exitApp();

private:
	void initRecentProjects();

	int mProjectListSize;

	MainWindow *mMainWindow;
	ProjectManager *mProjectManager;
	QVBoxLayout *mProjectsLayout;
	QHBoxLayout *mSessionsLayout;
};

}
