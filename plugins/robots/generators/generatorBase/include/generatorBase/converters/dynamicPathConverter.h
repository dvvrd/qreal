#pragma once

#include "generatorBase/converters/templateParametrizedConverter.h"
#include "generatorBase/robotsGeneratorDeclSpec.h"

namespace generatorBase {
namespace converters {

/// A base class for converters that generate template path from their conversion data.
/// Must provide path with @@DATA@@ label that will be replaced by data.
/// May be useful for some enums.
class ROBOTS_GENERATOR_EXPORT DynamicPathConverter : public TemplateParametrizedConverter
{
public:
	/// @param pathFromRoot A path from templates root containing placeholder for data
	/// (for example colors/@@PATH@@.t)
	DynamicPathConverter(QString const &pathToTemplates, QString const &pathFromRoot);

	QString convert(QString const &data) const override;

private:
	QString const mPathFromRoot;
};

}
}
