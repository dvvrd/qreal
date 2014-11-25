#include "debuggerPage.h"
#include "ui_debuggerPage.h"

#include <qrkernel/settingsManager.h>

using namespace qReal;

PreferencesDebuggerPage::PreferencesDebuggerPage(QWidget *parent)
		: PreferencesPage(parent)
		, mUi(new Ui::PreferencesDebuggerPage)

{
	mUi->setupUi(this);
	setObjectName("preferencesDebuggerPage");
	setWindowIcon(QIcon(":/preferencesDialog/images/bug.png"));

	restoreSettings();
}

PreferencesDebuggerPage::~PreferencesDebuggerPage()
{
	delete mUi;
}

void PreferencesDebuggerPage::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		mUi->retranslateUi(this);
		break;
	default:
		break;
	}
}

void PreferencesDebuggerPage::save()
{
	SettingsManager::setValue("debuggerTimeout", mUi->timeoutLineEdit->text());
	SettingsManager::setValue("debugColor", mUi->colorComboBox->currentText());
}

void PreferencesDebuggerPage::restoreSettings()
{
	mUi->timeoutLineEdit->setText(SettingsManager::value("debuggerTimeout").toString());
	mUi->colorComboBox->addItems(QColor::colorNames());
	QString curColor = SettingsManager::value("debugColor").toString();
	int curColorIndex = mUi->colorComboBox->findText(curColor);
	mUi->colorComboBox->setCurrentIndex(curColorIndex);
}
