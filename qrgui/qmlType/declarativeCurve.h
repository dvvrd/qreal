#pragma once

#include <QtDeclarative/QDeclarativeItem>

#include "declarativePen.h"

namespace qmlTypes {

class DeclarativeCurve : public DeclarativePen
{
    Q_OBJECT

    Q_PROPERTY(int startx READ startx WRITE setStartx NOTIFY startxChanged)
    Q_PROPERTY(int starty READ starty WRITE setStarty NOTIFY startyChanged)
    Q_PROPERTY(int endx READ endx WRITE setEndx NOTIFY endxChanged)
    Q_PROPERTY(int endy READ endy WRITE setEndy NOTIFY endyChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int sizex READ sizex WRITE setSizex NOTIFY sizexChanged)
    Q_PROPERTY(int sizey READ sizey WRITE setSizey NOTIFY sizeyChanged)
    Q_PROPERTY(QColor fill READ fill WRITE setFill NOTIFY fillChanged)

public:
    DeclarativeCurve(QDeclarativeItem *parent = 0);
    int startx() const;
    int starty() const;
    int endx() const;
    int endy() const;
    int x() const;
    int y() const;
    int sizex() const;
    int sizey() const;
    QColor fill() const;

signals:
    void startxChanged();
    void startyChanged();
    void endxChanged();
    void endyChanged();
    void xChanged();
    void yChanged();
    void sizexChanged();
    void sizeyChanged();
    void fillChanged();

protected:
    void updateSize();
    void setStartx(int startx);
    void setStarty(int starty);
    void setEndx(int endx);
    void setEndy(int endy);
    void setX(int x);
    void setY(int y);
    void setSizex(int sizex);
    void setSizey(int sizey);
    void setFill(QColor color);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    int mStartx;
    int mStarty;
    int mEndx;
    int mEndy;
    int mX;
    int mY;
    int mSizex;
    int mSizey;
    int mFirstSizex;
    int mFirstSizey;
    QColor mFill;
};

}
QML_DECLARE_TYPE(qmlTypes::DeclarativeCurve)
