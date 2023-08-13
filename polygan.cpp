#include "border.h"

CPolygan::CPolygan(QBrush b, QPen p):abrush(b), apen(p)
{

    //    polyPoints << QPoint(Start.x(),Start.y())
    //               << QPoint(End.x(),End.y());
    //    setFlags(ItemIsSelectable|ItemIsMovable);
    pressed = false;
    moving  = false;
    rightPress = false;
    addpoly = true;
    gon = false;

    m_Rect.setRect(0,0,400,300);
}

QRectF CPolygan::boundingRect() const
{
    return m_Rect;
}

void CPolygan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    prepareGeometryChange();
    painter->setPen(apen);
    painter->setBrush(abrush);
    if(pressed && addpoly)
    {
        polyPoints << startPos;
        //abrush.setColor(Qt::red);
        if(rightPress)
        {
            addpoly =false;
            m_Rect = polyPoints.boundingRect();
            static_cast<CBorder*>(parentItem())->drawCHandle = true;
            static_cast<CBorder*>(parentItem())->m_Rect = boundingRect();
        }
        else
        {
            sThumb.setRect(polyPoints.first().x(),polyPoints.first().y(),borderMargin,borderMargin);
            painter->fillRect(sThumb,QBrush(Qt::red));
            painter->drawRect(sThumb);
            QToolTip::showText(QPoint(polyPoints.last().x(),polyPoints.last().y())
                               ,"Now you can click on the start thumb and your shape will be polygon \n and if you right click, the polyline will be compeleted!");
        }

        if(IsinBounding(polyPoints.last(),sThumb))
        {
            polyPoints.pop_back();
            polyPoints.push_back(polyPoints.first());
            gon = true;
            addpoly =false;
        }
        else
            gon =false;

    }
    if(gon) {
        static_cast<CBorder*>(parentItem())->drawCHandle = true;
        painter->setBrush(abrush);
        painter->drawPolygon(polyPoints,Qt::OddEvenFill);
        m_Rect = polyPoints.boundingRect();
        static_cast<CBorder*>(parentItem())->m_Rect = boundingRect();
        static_cast<CBorder*>(parentItem())->DoneDrawing =true;
    }
    else
    {
        painter->setPen(abrush.color());
        painter->drawPolyline(polyPoints); 
        static_cast<CBorder*>(parentItem())->m_Rect = boundingRect();
        static_cast<CBorder*>(parentItem())->DoneDrawing =true;
    }
}

void CPolygan::normalize(QRectF rect)
{
    m_Rect.setRect(rect.left()+borderMargin,rect.top()+borderMargin,
                   rect.width()-2*borderMargin,rect.height()-2*borderMargin);
}

int CPolygan::type() const
{
    return Type;
}

void CPolygan::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;

    if(event->button() == Qt::RightButton) rightPress=true;
    else rightPress=false;
    m_cursor = event->pos();
    startPos = event->pos();

    //update();
    QGraphicsItem::mousePressEvent(event);
}

void CPolygan::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    moving = false;
    m_cursor = event->pos();
    endPos = event->pos();
    //update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void CPolygan::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    moving = true;
    m_cursor = event->pos();
    //update();
    QGraphicsItem::mouseMoveEvent(event);
}


bool CPolygan::IsinBounding(QPointF point, QRectF rect)
{
    if( (point.x()>rect.x() && point.x()<rect.right()) &&
            (point.y()>rect.y() && point.y()<rect.bottom()))
        return true;
    return false;
}

void CPolygan::updateItem()
{
    abrush = static_cast<CBorder*>(parentItem())->abrush;
}
