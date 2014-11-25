#pragma once

#include <qrgui/plugins/toolPluginInterface/projectConverter.h>

namespace interpreterCore {

/// Provides a number of converters that transform some incompatible features in old save versions.
class SaveConvertionManager
{
public:
	/// Returns a list of converters for robots editor.
	static QList<qReal::ProjectConverter> converters();

private:
	/// Returns a converter that restricts all saves made by editors till 3.0.0 alpha1.
	static qReal::ProjectConverter before300Alpha1Converter();

	/// Returns a converter that transforms JA1-form ports to the A1-form ones and
	/// sensor1- and digitSensor1-form variables into sensorA1- and sensorD1-form ones.
	static qReal::ProjectConverter from300Alpha4to300Alpha5Converter();

	static bool isRobotsDiagram(qReal::Id const &diagram);
	static qReal::IdList elementsOfRobotsDiagrams(qReal::LogicalModelAssistInterface const &logicalApi);
	static QString editor();
};

}
