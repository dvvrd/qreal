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

#include "documentLoader.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>

#include <qrutils/xmlUtils.h>
#include <qrutils/inFile.h>

QDomDocument DocumentLoader::load(const QFileInfo &fileInfo)
{
	QString errorMessage;
	int errorLine = 0;
	int errorColumn = 0;

	const QString path = fileInfo.absoluteFilePath();
	const QDomDocument document = utils::xmlUtils::loadDocument(path
			, &errorMessage, &errorLine, &errorColumn);
	if (!errorMessage.isEmpty()) {
		qCritical() << QString("(%1, %2):").arg(errorLine).arg(errorColumn)
				<< "Could not parse XML. Error:" << errorMessage;
		return QDomDocument();
	}

	if (mUsedFiles.contains(path)) {
		qCritical() << "ERROR: Cyclic external tags references; proceeding with empty document";
		return QDomDocument();
	}

	mUsedFiles.append(path);
	QDomElement root = document.documentElement();
	QDomElement dumbParent = root.parentNode().toElement();
	if (!root.isNull()) {
		processElement(root, dumbParent, fileInfo.absoluteDir().absolutePath());
	}

	mUsedFiles.removeOne(path);

	return document;
}

void DocumentLoader::processElement(QDomElement &element, QDomElement &parent, const QString &currentDir)
{
	if (element.tagName().toLower() == "external") {
		const QString externalFileName = element.attribute("file");
		parent.removeChild(element);
		if (externalFileName.isEmpty()) {
			return;
		}

		qInfo() << "Processing exernal link to " + externalFileName;
		QDir dir(currentDir);
		QFileInfo info(dir, externalFileName);
		const QDomDocument externalDoc = load(info);
		if (externalDoc.isNull()) {
			const QString fileContents = utils::InFile::readAll(info.absoluteFilePath());
			const QDomText textElement = parent.ownerDocument().createTextNode(fileContents);
			parent.appendChild(textElement);
		}

		const QDomElement newElement = externalDoc.documentElement().cloneNode().toElement();
		parent.appendChild(newElement);
		element = newElement;
	}

	QDomElement child = element.firstChildElement();
	while (!child.isNull()) {
		processElement(child, element, currentDir);
		child = child.nextSiblingElement();
	}
}
