#include "ev3AdditionalPreferences.h"
#include "ui_ev3AdditionalPreferences.h"

#include <qrkernel/settingsManager.h>
#include <plugins/robots/thirdparty/qextserialport/src/qextserialenumerator.h>

using namespace ev3KitInterpreter;
using namespace qReal;

Ev3AdditionalPreferences::Ev3AdditionalPreferences(QString const &realRobotName, QWidget *parent)
		: AdditionalPreferences(parent)
		, mUi(new Ui::Ev3AdditionalPreferences)
		, mRealRobotName(realRobotName)
{
	mUi->setupUi(this);
	connect(mUi->bluetoothRadioButton, &QRadioButton::toggled
			, mUi->bluetoothSettingsGroupBox, &QWidget::setVisible);
	connect(mUi->manualComPortCheckbox, &QCheckBox::toggled
			, this, &Ev3AdditionalPreferences::manualComPortCheckboxChecked);
}

Ev3AdditionalPreferences::~Ev3AdditionalPreferences()
{
	delete mUi;
}

void Ev3AdditionalPreferences::save()
{
	SettingsManager::setValue("Ev3BluetoothPortName", selectedPortName());
	SettingsManager::setValue("Ev3ValueOfCommunication", selectedCommunication());
	SettingsManager::setValue("Ev3ManualComPortCheckboxChecked", mUi->manualComPortCheckbox->isChecked());
	emit settingsChanged();
}

void Ev3AdditionalPreferences::restoreSettings()
{
	QList<QextPortInfo> const ports = QextSerialEnumerator::getPorts();
	QString const defaultPortName = SettingsManager::value("Ev3BluetoothPortName").toString();
	mUi->comPortComboBox->clear();

	for (QextPortInfo const &info : ports) {
		QRegExp const portNameRegexp("COM\\d+", Qt::CaseInsensitive);
		if (portNameRegexp.indexIn(info.portName) != -1) {
			QString const portName = portNameRegexp.cap();
			mUi->comPortComboBox->addItem(portName);
		}
	}

	int const defaultIndex = mUi->comPortComboBox->findText(defaultPortName);
	if (defaultIndex != -1) {
		mUi->comPortComboBox->setCurrentIndex(defaultIndex);
	}

	if (mUi->comPortComboBox->count() == 0) {
		mUi->comPortComboBox->hide();
		mUi->comPortLabel->hide();
		mUi->manualComPortCheckbox->hide();
		mUi->noComPortsFoundLabel->show();
		mUi->directInputComPortLabel->show();
		mUi->directInputComPortLineEdit->show();
		mUi->directInputComPortLineEdit->setText(defaultPortName);
	} else {
		mUi->comPortComboBox->show();
		mUi->comPortLabel->show();
		mUi->manualComPortCheckbox->show();
		mUi->directInputComPortLabel->hide();
		mUi->directInputComPortLineEdit->hide();
		mUi->noComPortsFoundLabel->hide();
		mUi->manualComPortCheckbox->setChecked(false);
		mUi->manualComPortCheckbox->setChecked(SettingsManager::value("Ev3ManualComPortCheckboxChecked").toBool());
	}

	QString const typeOfCommunication = SettingsManager::value("Ev3ValueOfCommunication").toString();
	if (typeOfCommunication == "bluetooth") {
		mUi->bluetoothRadioButton->setChecked(true);
	} else if (typeOfCommunication == "usb") {
		mUi->usbRadioButton->setChecked(true);
	} else {
		mUi->bluetoothRadioButton->setChecked(false);
		mUi->usbRadioButton->setChecked(false);
	}
}

void Ev3AdditionalPreferences::onRobotModelChanged(interpreterBase::robotModel::RobotModelInterface * const robotModel)
{
	bool const isReal = robotModel->name() == mRealRobotName;
	mUi->communicationTypeGroupBox->setVisible(isReal);
	mUi->bluetoothSettingsGroupBox->setVisible(mUi->bluetoothRadioButton->isChecked() && isReal);
}

void Ev3AdditionalPreferences::manualComPortCheckboxChecked(bool state)
{
	QString const defaultPortName = SettingsManager::value("Ev3BluetoothPortName").toString();

	if (state) {
		mUi->comPortComboBox->hide();
		mUi->comPortLabel->hide();
		mUi->directInputComPortLabel->show();
		mUi->directInputComPortLineEdit->show();
		mUi->directInputComPortLineEdit->setText(defaultPortName);
	} else {
		mUi->comPortComboBox->show();
		mUi->comPortLabel->show();
		mUi->directInputComPortLabel->hide();
		mUi->directInputComPortLineEdit->hide();
		mUi->noComPortsFoundLabel->hide();
	}
}

QString Ev3AdditionalPreferences::selectedCommunication() const
{
	return mUi->bluetoothRadioButton->isChecked() ? "bluetooth"
			: mUi->usbRadioButton->isChecked() ? "usb" : "";
}

QString Ev3AdditionalPreferences::selectedPortName() const
{
	return mUi->comPortComboBox->isVisible()
			? mUi->comPortComboBox->currentText()
			: mUi->directInputComPortLineEdit->text();
}
