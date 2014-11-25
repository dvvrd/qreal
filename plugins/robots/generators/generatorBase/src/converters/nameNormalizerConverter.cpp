#include "nameNormalizerConverter.h"

#include <qrutils/nameNormalizer.h>

using namespace generatorBase::converters;
using namespace qReal;

QString NameNormalizerConverter::convert(QString const &data) const
{
	return utils::NameNormalizer::normalizeStrongly(data, false);
}
