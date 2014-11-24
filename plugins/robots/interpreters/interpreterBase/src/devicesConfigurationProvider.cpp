#include "interpreterBase/devicesConfigurationProvider.h"

using namespace interpreterBase;
using namespace robotModel;

DevicesConfigurationProvider::DevicesConfigurationProvider(QString const &name)
	: mName(name)
{
}

DevicesConfigurationProvider::~DevicesConfigurationProvider()
{
}

void DevicesConfigurationProvider::connectDevicesConfigurationProvider(
		DevicesConfigurationProvider * const otherProvider)
{
	if (!otherProvider) {
		return;
	}

	if (!mConnectedProviders.contains(otherProvider)) {
		mConnectedProviders << otherProvider;
		otherProvider->connectDevicesConfigurationProvider(this);
	}
}

void DevicesConfigurationProvider::disconnectDevicesConfigurationProvider(
		DevicesConfigurationProvider * const provider)
{
	if (!provider) {
		return;
	}

	mConnectedProviders.removeOne(provider);
}

void DevicesConfigurationProvider::disconnectDevicesConfigurationProvider()
{
	for (DevicesConfigurationProvider *provider : mConnectedProviders) {
		provider->disconnectDevicesConfigurationProvider(this);
	}
}

void DevicesConfigurationProvider::deviceConfigurationChanged(QString const &robotModel
		, PortInfo const &port, DeviceInfo const &device, Reason reason)
{
	if (mCurrentConfiguration[robotModel][port] != device) {
		mCurrentConfiguration[robotModel][port] = device;

		for (DevicesConfigurationProvider * const provider : mConnectedProviders) {
			// Broadcast change.
			provider->deviceConfigurationChanged(robotModel, port, device, reason);

			// Allow connected providers to react on configuration change.
			provider->onDeviceConfigurationChanged(robotModel, port, device, reason);
		}
	}
}

void DevicesConfigurationProvider::onDeviceConfigurationChanged(QString const &robotModel
		, PortInfo const &port, DeviceInfo const &sensor, Reason reason)
{
	Q_UNUSED(robotModel)
	Q_UNUSED(port);
	Q_UNUSED(sensor);
	Q_UNUSED(reason);
}

void DevicesConfigurationProvider::clearConfiguration(Reason reason)
{
	for (QString const &robotModel : mCurrentConfiguration.keys()) {
		for (PortInfo const &port : mCurrentConfiguration[robotModel].keys()) {
			deviceConfigurationChanged(robotModel, port, DeviceInfo(), reason);
		}
	}
}

QStringList DevicesConfigurationProvider::configuredModels() const
{
	return mCurrentConfiguration.keys();
}

QList<robotModel::PortInfo> DevicesConfigurationProvider::configuredPorts(QString const &modelName) const
{
	if (!mCurrentConfiguration.contains(modelName)) {
		return {};
	}

	return mCurrentConfiguration[modelName].keys();
}

robotModel::DeviceInfo DevicesConfigurationProvider::currentConfiguration(QString const &modelName
		, robotModel::PortInfo const &port) const
{
	if (!mCurrentConfiguration.contains(modelName) || !mCurrentConfiguration[modelName].contains(port)) {
		return robotModel::DeviceInfo();
	}

	return mCurrentConfiguration[modelName][port];
}
