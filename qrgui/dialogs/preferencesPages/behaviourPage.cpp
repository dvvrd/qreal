#include "behaviourPage.h"
#include "ui_behaviourPage.h"

#include <qrkernel/settingsManager.h>

using namespace qReal;

PreferencesBehaviourPage::PreferencesBehaviourPage(QWidget *parent)
		: PreferencesPage(parent)
		, mUi(new Ui::PreferencesBehaviourPage)
{
	mIcon = QIcon(":/icons/preferences/behaviour.png");
	mUi->setupUi(this);

	connect(mUi->autoSaveCheckBox, SIGNAL(clicked(bool)), this, SLOT(showAutoSaveBox(bool)));
	connect(mUi->collectErgonomicValuesCheckBox, SIGNAL(clicked(bool))
			, &mFilterObject, SLOT(setStatusCollectUsabilityStatistics(bool)));
	restoreSettings();
}

PreferencesBehaviourPage::~PreferencesBehaviourPage()
{
	delete mUi;
}

void PreferencesBehaviourPage::changeEvent(QEvent *e)
{
	switch (e->type()) {
	case QEvent::LanguageChange:
		mUi->retranslateUi(this);
		break;
	default:
		break;
	}
}

void PreferencesBehaviourPage::save()
{
	SettingsManager::setValue("PaletteTabSwitching", mUi->paletteTabCheckBox->isChecked());
	SettingsManager::setValue("Autosave", mUi->autoSaveCheckBox->isChecked());
	SettingsManager::setValue("AutosaveInterval", mUi->autoSaveSpinBox->value());
	SettingsManager::setValue("gestureDelay", mUi->gestureDelaySpinBox->value());
	bool const usabilityTestingMode = mUi->usabilityModeCheckBox->isChecked();
	SettingsManager::setValue("usabilityTestingMode", usabilityTestingMode);
	SettingsManager::setValue("collectErgonomicValues", mUi->collectErgonomicValuesCheckBox->isChecked()
			|| usabilityTestingMode);
	SettingsManager::setValue("touchMode", mUi->touchModeChackBox->isChecked());

	if (mUsabilityTestingMode != usabilityTestingMode) {
		if (usabilityTestingMode) {
			mUi->collectErgonomicValuesCheckBox->setChecked(true);
		}
		mUsabilityTestingMode = usabilityTestingMode;
		emit usabilityTestingModeChanged(mUsabilityTestingMode);
	}
}

void PreferencesBehaviourPage::restoreSettings()
{
	mUi->paletteTabCheckBox->setChecked(SettingsManager::value("PaletteTabSwitching").toBool());
	mUi->autoSaveCheckBox->setChecked(SettingsManager::value("Autosave").toBool());
	mUi->autoSaveSpinBox->setValue(SettingsManager::value("AutosaveInterval").toInt());
	mUi->gestureDelaySpinBox->setValue(SettingsManager::value("gestureDelay").toInt());
	mUi->collectErgonomicValuesCheckBox->setChecked(SettingsManager::value("collectErgonomicValues").toBool());

	mUi->usabilityModeCheckBox->setChecked(mUsabilityTestingMode);
	mUi->touchModeChackBox->setChecked(SettingsManager::value("touchMode").toBool());

	mUsabilityTestingMode = SettingsManager::value("usabilityTestingMode").toBool();

	showAutoSaveBox(mUi->autoSaveCheckBox->isChecked());
	int const editorsLoadedCount = SettingsManager::value("EditorsLoadedCount").toInt();
	mUi->paletteTabCheckBox->setVisible(editorsLoadedCount != 1);
	mFilterObject.setStatusCollectUsabilityStatistics(mUi->collectErgonomicValuesCheckBox->isChecked());
}

void PreferencesBehaviourPage::showAutoSaveBox(bool show)
{
	mUi->autoSaveSpinBox->setVisible(show);
	mUi->autoSaveLabel->setVisible(show);
}
