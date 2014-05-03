#include "ChangeVersion.h"
#include "ui_ChangeVersion.h"
#include "../visualDiff/view/diffWindow.h"
#include <QtCore/QString>

using namespace qReal;

ChangeVersion::ChangeVersion(QWidget *parent) :
	QWidget(parent),
	mUi(new Ui::ChangeVersion)
{
	mUi->setupUi(this);
	mUi->pushButton->hide();
	mUi->label->hide();
	connect(mUi->pushButton, SIGNAL(clicked()), SLOT(obtainHash()));
	mUi->listWidgetForLog->setMinimumWidth(this->width() / 4);
	mUi->listWidgetForLog->setMinimumWidth(this->width() / 5);
	initDiffWidget();
}

ChangeVersion::~ChangeVersion()
{
	delete mUi;
}

void ChangeVersion::obtainHash()
{
	QString hash = mUi->listWidgetForLog->currentItem()->data(Qt::UserRole).toString();
	emit swapTab();
	mUi->listWidgetForLog->clear();
	mUi->listWidgetForLog->deleteLater();
	emit hashObtained(hash);
}

void ChangeVersion::showDiff(QListWidgetItem *item)
{
	if (mUi->listWidgetForLog->row(item) != 0){
		mUi->pushButton->show();
	}else{
		mUi->pushButton->hide();
	}
	QString firstHash = item->data(Qt::UserRole).toString();
	int row = mUi->listWidgetForLog->row(item);
	QListWidgetItem *item2 = mUi->listWidgetForLog->item(row + 1);
	foreach(QObject *object, mDiffWidget->children()){
		versioning::DiffWindow *dWindow = dynamic_cast<versioning::DiffWindow *>(object);
		if (dWindow){
			delete dWindow;
		}
	}

	if (item2 != NULL){
		emit showDiff(firstHash, item2->data(Qt::UserRole).toString(), mDiffWidget);
	} else {
		emit showDiff(firstHash, QString(), mDiffWidget);
	}
}

void ChangeVersion::initDiffWidget()
{
	mDiffWidget = new QWidget();
	QGridLayout *mLayout = new QGridLayout(mDiffWidget);
	mLayout->setMargin(0);
	mDiffWidget->setLayout(mLayout);
	mDiffWidget->setFixedWidth(0.9 * this->width());
	mUi->horizontalLayout->addWidget(mDiffWidget, 8, Qt::AlignLeft);
}

void ChangeVersion::updateLog(QList<QPair<QString , QString> > listLog) // hash & mainPart
{
	mUi->pushButton->hide();
	if (listLog.size() != 0){
		disconnect(mUi->listWidgetForLog, SIGNAL(itemClicked(QListWidgetItem*))
				, this, SLOT(showDiff(QListWidgetItem*)));
		connect(mUi->listWidgetForLog, SIGNAL(itemClicked(QListWidgetItem*))
				, this, SLOT(showDiff(QListWidgetItem*)),Qt::QueuedConnection);
		mUi->listWidgetForLog->clear();
		int number = 0;
		while (number < listLog.size()){
			QListWidgetItem *item = new QListWidgetItem;
			item->setData(Qt::UserRole,listLog.at(number).first);
			item->setText(listLog.at(number).second);
			mUi->listWidgetForLog->addItem(item);
			number++;
		}
		mUi->listWidgetForLog->item(0)->setSelected(true);
		showDiff(mUi->listWidgetForLog->item(0));
	} else {
		mUi->listWidgetForLog->clear();
		QString text = "There are not version of the project or project was not versioned. \n Or project isn't loaded";
		mUi->label->setText(text);
		mUi->label->showMaximized();
	}
}

void ChangeVersion::onViewForTransparentModeIsReady(QGraphicsView *mView)
{
	mUi->gridLayout->addWidget(mView);
}

