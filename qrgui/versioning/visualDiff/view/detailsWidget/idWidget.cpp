#include "idWidget.h"

using namespace versioning;
using namespace versioning::details;

IdWidget::IdWidget(QString const &defaultText, QWidget *parent)
	: QWidget(parent), mDefaultText(defaultText), mIdSetted(false)
{
	this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

	mLayout = new QGridLayout(this);
	mLabelLogical = new QLabel(QString(), this);
	mLabelGraphical = new QLabel(QString(), this);

	QFont labelFont = mLabelLogical->font();
	labelFont.setBold(true);
	mLabelLogical->setFont(labelFont);
	mLabelGraphical->setFont(labelFont);

	mMetrics = new QFontMetrics(mLabelLogical->font());

	mLabelWidth = 4 * parentWidget()->contentsRect().width();

	QString elidedText = mMetrics->elidedText(mDefaultText, Qt::ElideRight, mLabelWidth);
	mLabelLogical->setText(elidedText);
	mLabelLogical->setToolTip(mDefaultText);
	mLabelLogical->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
	mLabelGraphical->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	mLayout->addWidget(mLabelLogical);
	mLayout->addWidget(mLabelGraphical);
	setLayout(mLayout);
}

void IdWidget::setId(const qReal::Id &graphicalId, const qReal::Id &logicalId)
{
	mIdSetted = true;
	mGraphicalId = graphicalId;
	mLogicalId = logicalId;
	mLabelLogical->setText(labelLogicalText());
	mLabelGraphical->setText(labelGraphicalText());
}

void IdWidget::reset()
{
	mIdSetted = false;
	mLabelLogical->setText(mDefaultText);
}

void IdWidget::enterEvent(QEvent *event)
{
	QWidget::enterEvent(event);
	event->accept();
	if (mIdSetted) {
		emit mouseEntered(mGraphicalId);
	}
}

void IdWidget::leaveEvent(QEvent *event)
{
	QWidget::leaveEvent(event);
	event->accept();
	if (mIdSetted) {
		emit mouseLeaved(mGraphicalId);
	}
}

QString IdWidget::labelLogicalText() const
{
	QString result = "";
	if (mLogicalId != qReal::Id()) {
		result += tr("Logical Id: ") + mLogicalId.toString();
	}
	QString elidedText = mMetrics->elidedText(result, Qt::ElideRight, mLabelWidth);
	mLabelLogical->setToolTip(result);
	return elidedText;
}

QString IdWidget::labelGraphicalText() const
{
	QString result = "";
	if (mGraphicalId != qReal::Id()) {
		result += tr("Graphical Id: ") + mGraphicalId.toString();
	}
	QString elidedText = mMetrics->elidedText(result, Qt::ElideRight, mLabelWidth);
	mLabelGraphical->setToolTip(result);
	return elidedText;
}
