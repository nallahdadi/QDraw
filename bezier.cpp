#include "border.h"

CBezier::CBezier(QBrush b, QPen p):abrush(b), apen(p)
{
    pressed = false;
    addbez  = false;
    pressResize  =false;
    pressMove = false;
    m_Rect.setRect(0,0,400,300);
}

QRectF CBezier::boundingRect() const
{
    return m_Rect;
}

void CBezier::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();
    myPath.~QPainterPath();
    painter->setPen(apen);
    //painter->setBrush(abrush);
    //painter->eraseRect(m_Rect);
    //painter->setRenderHint(QPainter::Antialiasing);
    if(pressed)
    {
        //abrush.setColor(Qt::red);

        if(IsCtrlPoint(m_cursor))
        {
            redrawWithCtrl();
        }
        else
        {
            static_cast<CBorder*>(parentItem())->setFlag(ItemIsMovable ,true);
        }
        if(c.count() < 3)
        {
            c << m_cursor;
            if(c.count()-1 == 2)
            {
                painter->eraseRect(static_cast<CBorder*>(parentItem())->boundingRect());
                sThumb[2].setRect(m_cursor.x()-2*borderMargin,m_cursor.y()-2*borderMargin,borderMargin,borderMargin);
            }
            else
                sThumb[c.count()-1].setRect(m_cursor.x(),m_cursor.y(),borderMargin,borderMargin);
            pressed =false;
        }

        else
        {
            //abrush.setColor(Qt::green);
        }
    }

    if(c.count() >= 3)
    {
        static_cast<CBorder*>(parentItem())->drawCHandle = true;
        QPolygonF points;
        myPath.moveTo(m_Rect.topLeft());
        myPath.cubicTo(c[0],c[1],c[2]);
        //static_cast<CBorder*>(parentItem())->
        painter->setPen(abrush.color());
        painter->drawPath(myPath);
        points << c[0] << c[1] << c[2] << myPath.boundingRect().bottomLeft() << myPath.boundingRect().topRight();
        m_Rect = points.boundingRect();
        static_cast<CBorder*>(parentItem())->m_Rect = boundingRect();
        //static_cast<CBorder*>(parentItem())->setSelected(false);
        static_cast<CBorder*>(parentItem())->DoneDrawing =true;
    }
    if(static_cast<CBorder*>(parentItem())->isSelected())
        for(int i=0; i <c.count(); i++)
        {
            painter->fillRect(sThumb[i],QBrush(Qt::red));
            painter->drawRect(sThumb[i]);
        }


    QRectF start(boundingRect().x(),boundingRect().y(),borderMargin,borderMargin);
    painter->drawRect(start);
    painter->fillRect(start,QBrush(Qt::red));

    //
}

void CBezier::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    pressed = true;
    m_cursor = event->pos();
    QGraphicsItem::mousePressEvent(event);
}

void CBezier::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    pressed = false;
    pressResize = false;
    pressMove = false;
    m_cursor = event->pos();
    //QGraphicsItem::mousePressEvent(event);
}

void CBezier::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    m_cursor = event->pos();
    if(pressResize)
        redrawWithCtrl();
    else
    {
        pressMove = true;
       // QGraphicsItem::mouseMoveEvent(event);
    }
}

int CBezier::type() const
{
    return Type;
}

int CBezier::IsCtrlPoint(QPointF point)
{
    for(int i=0 ; i<3 ; i++)
    {
        int xdiffer = static_cast<int>(point.x() - sThumb[i].x());
        int ydiffer = static_cast<int>(point.y() - sThumb[i].y());

        if ( (xdiffer > 0  &&  xdiffer < borderMargin ) && ( ydiffer > 0  &&  ydiffer < borderMargin ) )
        {
            pressResize =true;
            static_cast<CBorder*>(parentItem())->setFlag(ItemIsMovable,false);
            ctrlcorner = i+1;
            return ctrlcorner;
        }
    }

    return 0;
}

void CBezier::redrawWithCtrl()
{
    m_cursor = static_cast<CBorder*>(parentItem())->m_cursor;
    switch(ctrlcorner)
    {
    case 1:
        c[0] = m_cursor;
        sThumb[0].setRect(m_cursor.x()-borderMargin/2,m_cursor.y()-borderMargin/2,borderMargin,borderMargin);
        break;

    case 2:
        c[1] = m_cursor;
        sThumb[1].setRect(m_cursor.x()-borderMargin/2,m_cursor.y()-borderMargin/2,borderMargin,borderMargin);
        break;

    case 3:
        c[2] = m_cursor;
        sThumb[2].setRect(m_cursor.x()-borderMargin/2,m_cursor.y()-borderMargin/2,borderMargin,borderMargin);
        break;
    }
}

void CBezier::normalize(QRectF rect)
{
    m_Rect.setRect(rect.left()+borderMargin,rect.top()+borderMargin,
                   rect.width()-2*borderMargin,rect.height()-2*borderMargin);
}

void CBezier::updateItem()
{
}
