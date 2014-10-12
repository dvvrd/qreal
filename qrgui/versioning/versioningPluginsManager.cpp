#include "versioningPluginsManager.h"
#include "diffPluginBase.h"
#include "../mainwindow/mainWindow.h"
#include "visualDiff/diffPluginWrapper.h"
#include "../../qrutils/fileSystemUtils.h"
#include <QDebug>

using namespace qReal;

QString const tempFolderName = "tempVCS";

VersioningPluginsManager::VersioningPluginsManager(/*ToolPluginManager const &pluginManager
		,*/ qrRepo::RepoControlInterface *repoApi
		, ErrorReporterInterface *errorReporter
		, ProjectManager *projectManager)
	: mRepoApi(repoApi), mErrorReporter(errorReporter)
	, mDiffPlugin(NULL)
	, mProjectManager(projectManager)
	, mTempDir(qApp->applicationDirPath() + "/" + tempFolderName)
{
	SettingsManager::setValue("versioningManagerTempDir", mTempDir);
	mRepoApi->setWorkingCopyInspector(this);
}

QString VersioningPluginsManager::tempFolder() const
{
	return SettingsManager::value("versioningManagerTempDir", mTempDir).toString();
}

void VersioningPluginsManager::prepareWorkingCopy()
{
	mRepoApi->prepareWorkingCopy(tempFolder());
}

void VersioningPluginsManager::initFromToolPlugins(
		QListIterator<ToolPluginInterface *> iterator
		, MainWindow *mainWindow)
{
	while (iterator.hasNext()) {
		ToolPluginInterface *toolPlugin = iterator.next();
		VersioningPluginInterface *versioningPlugin =
				dynamic_cast<VersioningPluginInterface *>(toolPlugin);
		if (versioningPlugin) {
			mPlugins.append(versioningPlugin);
			if (versioningPlugin->clientExist()){
				mPluginsWithExistClient.append(versioningPlugin);
			} else {
				foreach(ActionInfo const &actionInfo, versioningPlugin->actions()) {
					actionInfo.menu()->menuAction()->setVisible(false);
				}
			}
			versioningPlugin->setWorkingCopyManager(mRepoApi);
			connect(versioningPlugin, SIGNAL(workingCopyDownloaded(bool const, QString const &))
					, this, SLOT(onWorkingCopyDownloaded(bool const, QString const &)));
			connect(versioningPlugin, SIGNAL(workingCopyUpdated(bool const))
					, this, SLOT(onWorkingCopyUpdated(bool const)));
			connect(versioningPlugin, SIGNAL(changesSubmitted(bool const))
					, this, SLOT(onChangesSubmitted(bool const)));
		}
		DiffPluginBase *diffPlugin =
				dynamic_cast<DiffPluginBase *>(toolPlugin);
		// TODO: new diffPlugin for every versioning plugin
		if (diffPlugin) {
			mDiffPlugin = diffPlugin;
			mDiffPlugin->setHandler(new versioning::DiffPluginWrapper(mDiffPlugin, mRepoApi
					, this, mainWindow, &mainWindow->editorManager()));
		}
	}
	for (int i = 0; i < mPlugins.length(); i++){
		mPlugins[i]->setDiffViewerInterface(mDiffPlugin);
	}
}

VersioningPluginInterface *VersioningPluginsManager::activePlugin(bool needPreparation, const QString &workingDir)
{
	if (needPreparation) {
		prepareWorkingCopy();
	}
	VersioningPluginInterface *result = NULL;
	foreach (VersioningPluginInterface *plugin, mPlugins) {
		if (plugin->isMyWorkingCopy(workingDir)) {
			result = plugin;
		}
	}
	if (needPreparation) {
		qReal::FileSystemUtils::removeDir(tempFolder());
	}
	return result;
}

qrRepo::WorkingCopyInspectionInterface *VersioningPluginsManager::activeWorkingCopyInspector(QString const &workingDir)
{
	WorkingCopyInspectionInterface *activeInspector =
			dynamic_cast<WorkingCopyInspectionInterface *>(activeClient(workingDir));
	return activeInspector;
}

BriefVersioningInterface *VersioningPluginsManager::activeClient(QString const &workingDir)
{
	return activePlugin(false, workingDir);
}

bool VersioningPluginsManager::onFileAdded(const QString &filePath, const QString &workingDir)
{
	WorkingCopyInspectionInterface *activeInspector = activeWorkingCopyInspector(workingDir);
	if (!activeInspector) {
		return true;
	}
	return activeInspector->onFileAdded(filePath, workingDir);
}

bool VersioningPluginsManager::onFileRemoved(const QString &filePath, const QString &workingDir)
{
	WorkingCopyInspectionInterface *activeInspector = activeWorkingCopyInspector(workingDir);
	if (!activeInspector) {
		return true;
	}
	return activeInspector->onFileRemoved(filePath, workingDir);
}

bool VersioningPluginsManager::onFileChanged(const QString &filePath, const QString &workingDir)
{
	WorkingCopyInspectionInterface *activeInspector = activeWorkingCopyInspector(workingDir);
	if (!activeInspector) {
		return true;
	}
	return activeInspector->onFileChanged(filePath, workingDir);
}

void VersioningPluginsManager::beginWorkingCopyDownloading(
		  QString const &repoAddress
		, QString const &targetProject
		, QString commitId
		, bool quiet)
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return;
	}
	return activeVcs->beginWorkingCopyDownloading(repoAddress, targetProject, commitId, quiet);
}

void VersioningPluginsManager::beginWorkingCopyUpdating(QString const &targetProject)
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return;
	}
	return activeVcs->beginWorkingCopyUpdating(targetProject);
}

void VersioningPluginsManager::beginChangesSubmitting(QString const &description
														, QString const &targetProject, const bool &quiet)
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return;
	}
	return activeVcs->beginChangesSubmitting(description, targetProject, quiet);
}

bool VersioningPluginsManager::reinitWorkingCopy(QString const &targetProject)
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return true;
	}
	return activeVcs->reinitWorkingCopy(targetProject);
}

QString VersioningPluginsManager::information(QString const &targetProject)
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return QString();
	}
	return activeVcs->information(targetProject);
}

QString VersioningPluginsManager::commitId(QString const &targetProject)
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return "-1";
	}
	return activeVcs->commitId(targetProject);
}

QString VersioningPluginsManager::remoteRepositoryUrl(QString const &targetProject)
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return QString();
	}
	return activeVcs->remoteRepositoryUrl(targetProject);
}

bool VersioningPluginsManager::isMyWorkingCopy(QString const &directory, bool const &quiet
												, bool const &prepareAndProcess)
{
	return activePlugin(false, directory) != NULL;
}

QString VersioningPluginsManager::friendlyName()
{
	BriefVersioningInterface *activeVcs = activePlugin(true, tempFolder());
	if (!activeVcs) {
		return QString();
	}
	return activeVcs->friendlyName();
}

void VersioningPluginsManager::reportError(const QString &message)
{
	mErrorReporter->addError(message);
}

void VersioningPluginsManager::reportErrors(const QStringList &messages)
{
	foreach (QString const &message, messages) {
		reportError(message);
	}
}

void VersioningPluginsManager::reportWarning(const QString &message)
{
	mErrorReporter->addWarning(message);
}

void VersioningPluginsManager::reportWarnings(const QStringList &messages)
{
	foreach (QString const &message, messages) {
		reportWarning(message);
	}
}

void VersioningPluginsManager::onWorkingCopyDownloaded(const bool success
		, QString const &targetProject)
{
	emit workingCopyDownloaded(success, targetProject);
}

void VersioningPluginsManager::onWorkingCopyUpdated(const bool success)
{
	mProjectManager->reload();
	emit workingCopyUpdated(success);
}

void VersioningPluginsManager::onChangesSubmitted(const bool success)
{
	emit changesSubmitted(success);
}

bool VersioningPluginsManager::clientExist()
{
	activePlugin()->clientExist();
}
