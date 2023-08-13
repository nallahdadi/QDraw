#include "thumb.h"

CThumb::CThumb(QPointF Start, int Size)
{
    start = QPointF(Start.x()-Size/2,Start.y()-Size/2);
    size = QSizeF(Size,Size);
}

CThumb::CThumb(int x, int y, int Size)
{
    start = QPointF(x-Size/2,y-Size/2);
    size = QSizeF(Size,Size);
}

QRectF CThumb::boundingRect() const
{
    return QRectF(start, size);
}

void CThumb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->fillRect(rect,QBrush(Qt::cyan));
    painter->drawRect(rect);
    update(boundingRect());
}

void CThumb::setSize(int s)
{
    size = QSizeF(s,s);
}


bool CThumb::IsinThumb(QPointF point)
{
    if(this != NULL)
        if( (point.x()>boundingRect().x() && point.x()<boundingRect().right()) &&
                (point.y()>boundingRect().y() && point.y()<boundingRect().bottom()))
            return true;
    return false;
}
