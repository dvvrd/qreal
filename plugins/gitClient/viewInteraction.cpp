#include "viewInteraction.h"
#include "../../qrkernel/settingsManager.h"
#include "../../qrutils/versioningUtils/versionSelector.h"
#include "gitPlugin.h"
#include <QGridLayout>

using namespace git::details;
using namespace git::ui;

ViewInteraction::ViewInteraction(GitPlugin *pluginInstance)
	: mPlugin(pluginInstance)
	, mPreferencesPage(new PreferencesVersioningPage())
	, mDiffWidgets(QList<QWidget *>())
{
	initActions();
	connect(mPlugin, SIGNAL(initComplete(bool)), this, SLOT(onInitComplete(bool)));
	connect(mPlugin, SIGNAL(cloneComplete(bool)), this, SLOT(onCloneComplete(bool)));
	connect(mPlugin, SIGNAL(remoteComplete(bool)), this, SLOT(onRemoteComplete(bool)));
	connect(mPlugin, SIGNAL(commitComplete(bool)), this, SLOT(onCommitComplete(bool)));
	connect(mPlugin, SIGNAL(pushComplete(bool)), this, SLOT(onPushComplete(bool)));
	connect(mPlugin, SIGNAL(pullComplete(bool)), this, SLOT(onPullComplete(bool)));
	connect(mPlugin, SIGNAL(resetComplete(bool)), this, SLOT(onResetComplete(bool)));
	connect(mPlugin, SIGNAL(statusComplete(QString,bool)), this, SLOT(onStatusComplete(QString,bool)));
	connect(mPlugin, SIGNAL(logComplete(QString,bool)), this, SLOT(onLogComplete(QString,bool)));
	connect(mPlugin, SIGNAL(remoteListComplete(QString,bool)), this, SLOT(onRemoteListComplete(QString,bool)));

	connect(mPreferencesPage, SIGNAL(compactMode(bool)), SLOT(modeChanged(bool)));
}

void ViewInteraction::initActions()
{
	// TODO: Add menu enabling/disabling when current project changed

	QMenu *gitMenu = new QMenu(tr("Git"));

	QAction *initAction = gitMenu->addAction(tr("Init"));
	connect(initAction, SIGNAL(triggered()), this, SLOT(initClicked()));

	QAction *cloneAction = gitMenu->addAction(tr("Clone..."));
	connect(cloneAction, SIGNAL(triggered()), this, SLOT(cloneClicked()));

	QAction *remoteAction = gitMenu->addAction(tr("Remote add..."));
	connect(remoteAction, SIGNAL(triggered()), this, SLOT(remoteClicked()));

	QAction *commitAction = gitMenu->addAction(tr("Commit..."));
	connect(commitAction, SIGNAL(triggered()), this, SLOT(commitClicked()));

	QAction *pushAction = gitMenu->addAction(tr("Push..."));
	connect(pushAction, SIGNAL(triggered()), this, SLOT(pushClicked()));

	QAction *pullAction = gitMenu->addAction(tr("Pull..."));
	connect(pullAction, SIGNAL(triggered()), this, SLOT(pullClicked()));

	QAction *resetAction = gitMenu->addAction(tr("Reset..."));
	connect(resetAction, SIGNAL(triggered()), this, SLOT(resetClicked()));

	QAction *cleanAction = gitMenu->addAction(tr("Clean"));
	connect(cleanAction, SIGNAL(triggered()), this, SLOT(cleanClicked()));

	QAction *statusAction = gitMenu->addAction(tr("Status"));
	connect(statusAction, SIGNAL(triggered()), this, SLOT(statusClicked()));

	QAction *logAction = gitMenu->addAction(tr("Log"));
	connect(logAction, SIGNAL(triggered()), this, SLOT(logClicked()));

	QAction *remoteListAction = gitMenu->addAction(tr("Remote -v"));
	connect(remoteListAction, SIGNAL(triggered()), this, SLOT(remoteListClicked()));

	QAction *versionsAction = new QAction(tr("Versions"), this);
	versionsAction->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_T, Qt::SHIFT + Qt::Key_V));
	connect(versionsAction, SIGNAL(triggered()), this, SLOT(versionsClicked()));

	QMenu *diffMenu = new QMenu(tr("Visual diff"));
	gitMenu->addMenu(diffMenu);

	QAction *diffAction = diffMenu->addAction(tr("Diff"));
	connect(diffAction, SIGNAL(triggered()), this, SLOT(diffClicked()));

	QAction *diffBetweenAction = diffMenu->addAction(tr("Diff between..."));
	connect(diffBetweenAction, SIGNAL(triggered()), this, SLOT(diffBetweenClicked()));

	mMenu << qReal::ActionInfo(gitMenu, "tools") << qReal::ActionInfo(versionsAction, "tools", "tools");
}

QList<qReal::ActionInfo> ViewInteraction::actions() const
{
	return mMenu;
}

QPair<QString, PreferencesPage *> ViewInteraction::preferencesPage() const
{
	return QPair<QString, PreferencesPage *>("Git", mPreferencesPage);
}

void ViewInteraction::init(const qReal::PluginConfigurator &configurator)
{
	mMainWindowIface = &(configurator.mainWindowInterpretersInterface());
	mProjectManager = &(configurator.projectManager());
	mRepoApi = &(configurator.repoControlInterface());
	mSystemEvents = &(configurator.systemEvents());
	mCompactMode = new TransparentMode(mPlugin, mProjectManager, mMainWindowIface, mSystemEvents);
	modeChanged(qReal::SettingsManager::value("versioningCompactMode").toBool());
}

void ViewInteraction::initClicked()
{
	mPlugin->doInit();
}

void ViewInteraction::cloneClicked()
{
	ui::CloneDialog *dialog = new ui::CloneDialog(mMainWindowIface->windowWidget());
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}

	QString url = dialog->url();
	qReal::SettingsManager::setValue("cloneUrl",url);
	mProjectManager->saveOrSuggestToSaveAs();
	mPlugin->startClone(url, mRepoApi->workingFile());
}

void ViewInteraction::remoteClicked()
{
	ui::RemoteDialog *dialog = new ui::RemoteDialog(mMainWindowIface->windowWidget());
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}

	QString name = dialog->remoteName();
	QString url = dialog->remoteUrl();
	qReal::SettingsManager::setValue("gitRemoteName", name);
	qReal::SettingsManager::setValue("gitRemoteUrl", url);
	mPlugin->doRemote(name, url);
}

void ViewInteraction::commitClicked()
{
	ui::CommitDialog *dialog = new ui::CommitDialog(mMainWindowIface->windowWidget());
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}
	QString message = dialog->message();
	if (message.isEmpty()) {
		message = "<no message>";
	}
	mProjectManager->saveOrSuggestToSaveAs();
	mPlugin->startCommit(message);
}

void ViewInteraction::pushClicked()
{
	ui::PushDialog *dialog = new ui::PushDialog(mMainWindowIface->windowWidget());
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}
	QString const remote = dialog->url();
	qReal::SettingsManager::setValue("gitRemoteName", remote);
	mPlugin->startPush(remote);
}

void ViewInteraction::pullClicked()
{
	ui::PullDialog *dialog = new ui::PullDialog(mMainWindowIface->windowWidget());
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}

	QString const remote = dialog->url();
	qReal::SettingsManager::setValue("pullUrl", remote);
	mPlugin->startPull(remote);
}

void ViewInteraction::resetClicked()
{
	ui::ResetDialog *dialog = new ResetDialog(mMainWindowIface->windowWidget());
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}

	mPlugin->startReset(dialog->hashCommit());
}

void ViewInteraction::cleanClicked()
{
	if (mPlugin->doClean()) {
		reopenWithoutSavings();
		showMessage(tr("Clean successfully."));
	}
}

void ViewInteraction::statusClicked()
{
	mPlugin->doStatus();
}

void ViewInteraction::logClicked()
{
	mPlugin->doLog(QString(), true, true);
}

void ViewInteraction::remoteListClicked()
{
	mPlugin->doRemoteList();
}

void ViewInteraction::showMessage(const QString &message)
{
	mMainWindowIface->errorReporter()->addInformation(message);
}

void ViewInteraction::onInitComplete(const bool success)
{
	if (success){
		showMessage(tr("Init successfully."));
	}
}

void ViewInteraction::onCloneComplete(const bool success)
{
	if (success){
		showMessage(tr("Clone successfully"));
		reopenWithoutSavings();
	}
}

void ViewInteraction::onCommitComplete(const bool success)
{
	if (success) {
		showMessage(tr("Commited successfully."));
		reopenWithoutSavings();
	}
}

void ViewInteraction::onRemoteComplete(const bool success)
{
	if (success){
		showMessage(tr("Remote successfully."));
		reopenWithoutSavings();
	}
}

void ViewInteraction::onPushComplete(const bool success)
{
	if (success) {
		showMessage(tr("Pushed successfully."));
		reopenWithoutSavings();
	}
}

void ViewInteraction::onPullComplete(const bool success)
{
	if (success) {
		showMessage(tr("Pulled successfully."));
		reopenWithoutSavings();
	}
}

void ViewInteraction::onResetComplete(const bool success)
{
	if (success) {
		showMessage(tr("Reseted successfully."));
	}
}

void ViewInteraction::onStatusComplete(QString answer, const bool success)
{
	if (!success)
		return;

	ui::StatusDialog *dialog = new ui::StatusDialog(mMainWindowIface->windowWidget());
	dialog->message(answer);
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}
}

void ViewInteraction::onLogComplete(QString answer, const bool success)
{
	Q_UNUSED(success)
	ui::LogDialog *dialog = new ui::LogDialog(mMainWindowIface->windowWidget());

	if (answer.isEmpty()) {
		dialog->message("You have no commits.");
	} else {
		dialog->message(answer);
	}
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}
}

void ViewInteraction::onRemoteListComplete(QString answer, const bool success)
{
	if (!success){
		return;
	}

	ui::RemoteListDialog *dialog = new ui::RemoteListDialog(mMainWindowIface->windowWidget());
	dialog->message(answer);
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}
}

void ViewInteraction::versionsClicked()
{
	mCompactMode->openChangeVersionTab();
}

void ViewInteraction::diffClicked()
{
	QWidget *widget = makeDiffTab();
	mPlugin->showDiff(mProjectManager->saveFilePath(), widget, false);
}

void ViewInteraction::diffBetweenClicked()
{
	ui::DiffBetweenDialog *dialog = new ui::DiffBetweenDialog(mMainWindowIface->windowWidget());
	if (QDialog::Accepted != dialog->exec()) {
		return;
	}
	QString const newHash = dialog->firstHash();
	QString const oldHash = dialog->secondHash();
	QWidget *widget = makeDiffTab();
	if (oldHash.isEmpty()){
		mPlugin->showDiff(newHash, mProjectManager->saveFilePath(), widget, false);
	} else{
		mPlugin->showDiff(oldHash, newHash, mProjectManager->saveFilePath(), widget, false);
	}
}

void ViewInteraction::modeChanged(bool compactMode)
{
	mMenu.first().menu()->menuAction()->setVisible(!compactMode);
	mMenu.last().action()->setVisible(compactMode);
	if (compactMode){
		connect(mSystemEvents, SIGNAL(startSave()), mCompactMode, SLOT(saveVersion()));
	} else {
		disconnect(mSystemEvents, SIGNAL(startSave()), mCompactMode, SLOT(saveVersion()));
	}
}

void ViewInteraction::removeClosedTab(QWidget *widget)
{
	if (mDiffWidgets.contains(widget)){
		mDiffWidgets.removeOne(widget);
		if (mDiffWidgets.isEmpty()){
			mMainWindowIface->makeFullScreen(isFullScreen);
		}
	}
}

void ViewInteraction::reopenWithoutSavings()
{
	mProjectManager->reload();
}

QWidget *ViewInteraction::makeDiffTab()
{
	isFullScreen = mMainWindowIface->isFullScreen();
	if (!isFullScreen){
		mMainWindowIface->makeFullScreen(true);
	}
	mMainWindowIface->makeFullScreen();
	QWidget *widget = new QWidget();
	QGridLayout *mLayout = new QGridLayout(widget);
	mLayout->setMargin(0);
	widget->setLayout(mLayout);
	mMainWindowIface->openTab(widget, "diff");
	mDiffWidgets << widget;
	connect(mSystemEvents, SIGNAL(indefiniteTabClosed(QWidget*)), this, SLOT(removeClosedTab(QWidget*)));
	return widget;
}
