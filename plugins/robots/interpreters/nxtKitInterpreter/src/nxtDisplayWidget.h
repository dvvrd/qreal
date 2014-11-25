#pragma once

#include <QtWidgets/QWidget>

#include <qrutils/graphicsUtils/painterInterface.h>
#include <qrutils/graphicsUtils/paintWidget.h>

#include "commonTwoDModel/engine/twoDModelDisplayWidget.h"

namespace Ui
{
class NxtDisplayWidget;
}

namespace nxtKitInterpreter {

class NxtDisplayWidget : public twoDModel::engine::TwoDModelDisplayWidget
{
	Q_OBJECT

public:
	explicit NxtDisplayWidget(QWidget *parent = 0);
	~NxtDisplayWidget();

	void setPainter(graphicsUtils::PainterInterface *painter) override;

	bool buttonIsDown(QString const &buttonId) const override;

	void repaintDisplay();
	int displayWidth() const;
	int displayHeight() const;

protected:
	void paintEvent(QPaintEvent *);

private:
	Ui::NxtDisplayWidget *mUi;
	QImage mBackground;
};

}
