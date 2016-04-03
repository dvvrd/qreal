/* Copyright 2012-2016 Dmitry Mordvinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/QFileInfo>
#include <QtXml/QDomDocument>

/// Loads xml document in the given file substituting contents instead of 'external' tags
/// and detecting cyclic dependencies.
class DocumentLoader
{
public:
	/// Loads the given xml file with the external tags expanding (substitutes the contents as child tag
	/// if the external file has xml format or like the inner text else).
	QDomDocument load(const QFileInfo &fileInfo);

private:
	void processElement(QDomElement &element, QDomElement &parent, const QString &currentDir);

	QList<QString> mUsedFiles;
};
