#pragma once

#include <qrutils/versioningUtils/externalClientPluginBase.h>
#include <qrgui/toolPluginInterface/customizer.h>
#include "viewInteraction.h"

namespace svn
{

class SubversionPlugin : public qReal::versioning::ExternalClientPluginBase
{
	Q_OBJECT
	Q_INTERFACES(qReal::ToolPluginInterface)
	Q_PLUGIN_METADATA(IID "qReal.versioning.svn")

public:
	SubversionPlugin();
	virtual ~SubversionPlugin();

	QString pathToSvn() const;

	// QReal plugin interface
	virtual qReal::Customizer* customizationInterface();
	virtual void updateSettings();
	virtual QList<qReal::ActionInfo> actions();
	virtual void init(qReal::PluginConfigurator const &configurator);
	virtual QPair<QString, PreferencesPage *> preferencesPage();

	// Working copy inspection
	virtual bool onFileAdded(QString const &filePath, QString const &workingDir);
	virtual bool onFileRemoved(QString const &filePath, QString const &workingDir);
	virtual bool onFileChanged(QString const &filePath, QString const &workingDir);

	// Brief VCS interface
	virtual void beginWorkingCopyDownloading(QString const &repoAddress
			, QString const &targetProject
			, QString revisionNumber = "-1"
			, bool quiet = false);

	virtual void beginWorkingCopyUpdating(QString const &targetProject = QString());
	virtual void beginChangesSubmitting(const QString &description, QString const &targetProject = QString()
											, bool const &quiet = false);
	virtual bool reinitWorkingCopy(QString const &targetProject = QString());
	virtual QString information(QString const &targetProject = QString());
	virtual int revisionNumber(QString const &targetProject = QString());
	virtual QString remoteRepositoryUrl(QString const &targetProject = QString());
	virtual bool isMyWorkingCopy(QString const &directory = QString(), bool const &quiet = false
								, bool const &prepareAndProcess = false);
	virtual QString friendlyName();
	virtual QString getLog(QString const &format = QString(), bool const &quiet = false);
	virtual void setVersion(QString hash, bool const &quiet = false){}
	bool clientExist();

	void editProxyConfiguration();

public slots:
	void startCheckout(QString const &from
			, QString const &targetProject = QString()
			, QString const &targetFolder = QString()
			, QString revision = "-1", bool quiet = false);
	void startUpdate(QString const &to = QString()
			, QString const &sourceProject = QString());
	void startCommit(QString const &message = QString(), QString const &from = QString()
			, QString const &sourceProject = QString());
	bool doCleanUp(QString const &what = QString()
			, QString const &sourceProject = QString());
	void startRevert(QString const &what = QString()
			, QString const &sourceProject = QString());
	bool doAdd(QString const &what, bool force = true);
	bool doRemove(QString const &what, bool force = true);
	QString info(QString const &target = QString(), bool const reportErrors = true
			, QString const &sourceProject = QString());
	QString repoUrl(QString const &target = QString(), bool const reportErrors = false
			, QString const &sourceProject = QString());
	int currentRevision(QString const &target = QString(), bool const reportErrors = false
			, QString const &sourceProject = QString());
	void doAfterOperationIsFinished(QVariant const &tag);
	void checkClientInstalling();

signals:
	void workingCopyDownloaded(const bool success, QString const &targetProject);
	void workingCopyUpdated(const bool success);
	void changesSubmitted(const bool success);
	void clientInstalled(QString client, bool exist);

	void checkoutComplete(bool const success, QString const &targetProject, bool quiet);
	void updateComplete(bool const success);
	void commitComplete(bool const success);
	void revertComplete(bool const success);
	void cleanUpComplete(bool const success);
	void addComplete(bool const success);
	void removeComplete(bool const success);
	void operationComplete(QString const &name, bool const success);

protected:
	// External client overloads
	virtual int timeout() const;
	virtual QString tempFolder() const;

private:
	QString infoToRepoUrl(QString &repoInfo);
	int infoToRevision(QString const &repoInfo);

	void onCheckoutComplete(bool const result
		, QString const &targetProject, const bool quiet);
	void onUpdateComplete(bool const result);
	void onCommitComplete(bool const result);
	void onRevertComplete(bool const result);

	QStringList authenticationArgs() const;

	details::ViewInteraction *mViewInteraction;
	QString mTempDir;
};
}

