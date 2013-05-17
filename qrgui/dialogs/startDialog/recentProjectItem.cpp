#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "recentProjectItem.h"

using namespace qReal;

RecentProjectItem::RecentProjectItem(QWidget *parent, QString const &projectName, QString const &projectFullName)
	: QWidget(parent)
	, mFullName()
{
	mFullName = projectFullName;
	QString nameText = QString("<a href=\"%1\">%2</a>").arg(projectFullName,projectName);
	QLabel *name = new QLabel(nameText);
	QLabel *fullName = new QLabel(projectFullName);
	QVBoxLayout *recentProject = new QVBoxLayout();

	recentProject->addWidget(name);
	recentProject->addWidget(fullName);

	connect(name, SIGNAL(linkActivated(const QString)), parent, SLOT(createProjectWithDiagram(QString)));
}

QString RecentProjectItem::getData()
{
	return mFullName;
}
