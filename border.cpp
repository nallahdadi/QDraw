#include "border.h"

CBorder::CBorder(int itemType)
    : pressed(false),
      pressResize(false),
      pressMove(false),
      drawCHandle(true),
      DoneDrawing(false),
      corner(0),
      startPos(QPointF(0,0)),
      endPos(QPointF(0,0))
{
    type1 = itemType;
    setFlags(ItemIsSelectable|ItemIsMovable|ItemIsFocusable);
    QGraphicsItem* item;
    foreach(item,childItems())
        childList << item;
    for(int i=0 ; i<9 ; i++)
        m_cornerHandle[i] = NULL;
    abrush = QBrush(Qt::lightGray);
    apen   = QPen(Qt::black);
}

QRectF CBorder::boundingRect() const
{
    return QRectF(m_Rect.x()-borderMargin,m_Rect.y()-borderMargin,m_Rect.width()+2*borderMargin,m_Rect.height()+2*borderMargin);
}

void CBorder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    borderRect.setRect(boundingRect().x()+borderMargin,boundingRect().y()+borderMargin,
                       boundingRect().width()-2*borderMargin,boundingRect().height()-2*borderMargin);

    QBrush handleBrush;
    handleBrush = QBrush(Qt::cyan);
    if(pressed)
        if (IsCornerPos(m_cursor))
            handleBrush.setColor(Qt::red);
        else
            handleBrush.setColor(Qt::black);

    if(pressResize) handleBrush.setColor(Qt::red);
    //painter->fillRect(rect,abrush);

    setcornnerhandles();
    if(isSelected() && (!pressMove && !pressResize))
    {
        if(drawCHandle)
            for(int i=0; i<9; i++)
            {
                QRectF rect2 = m_cornerHandle[i]->boundingRect();
                painter->fillRect(rect2,handleBrush);
                painter->drawRect(rect2);
            }
        //updateItem();
        painter->setPen(QPen(Qt::lightGray,1.5,Qt::DashLine,Qt::FlatCap,Qt::MiterJoin));
        painter->drawRect(borderRect);
        //update(m_Rect);
    }

}

void CBorder::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    pressed = true;
    m_cursor = event->pos() ;
    startPos = m_cursor;
    oldPos = pos();
    if(IsCornerPos(m_cursor)) oldRect = boundingRect();

    QGraphicsItem::mousePressEvent(event);
}

void CBorder::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    if(pressResize)      emit itemResized(this,oldRect);
    else if(DoneDrawing && pressMove) emit itemMoved(this,oldPos);
    pressed = false;
    pressResize = false;
    pressMove = false;
    m_cursor = event->pos();


    QGraphicsItem::mouseReleaseEvent(event);
}

void CBorder::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    prepareGeometryChange();
    update((m_Rect.left()-15),(m_Rect.top()-15),
           (m_Rect.width()+15),(m_Rect.height()+15));

    endPos = event->pos();
    m_cursor = endPos;
    if((pressResize))
        resizeWithHandles();
    else
    {
        pressMove = true;
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void CBorder::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit MouseDoubleClicked(this,event);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void CBorder::setcornnerhandles()
{
    int Sx = borderRect.width()/2;
    int Sy = borderRect.height()/2;



    m_cornerHandle[0] = new CThumb(borderRect.topLeft());
    m_cornerHandle[1] = new CThumb(borderRect.x()+Sx,borderRect.y());
    m_cornerHandle[2] = new CThumb(borderRect.topRight());

    m_cornerHandle[3] = new CThumb(borderRect.x(),borderRect.y()+Sy);
    m_cornerHandle[4] = new CThumb(borderRect.x(),borderRect.y());
    m_cornerHandle[5] = new CThumb(borderRect.right(),borderRect.y()+Sy);

    m_cornerHandle[6] = new CThumb(borderRect.bottomLeft());
    m_cornerHandle[7] = new CThumb(borderRect.x()+Sx,borderRect.bottom());
    m_cornerHandle[8] = new CThumb(borderRect.bottomRight());
}

int CBorder::IsCornerPos(QPointF point)
{
    for(int i=0 ; i<9 ; i++)
    {

        if( m_cornerHandle[i]->IsinThumb(point) )
        {
            pressResize =true;
            corner = i+1;
            return corner;
        }
    }

    return 0;
}

bool CBorder::IsinBounding(QPointF point)
{
    if( (point.x()>boundingRect().x() && point.x()<boundingRect().right()) &&
            (point.y()>boundingRect().y() && point.y()<boundingRect().bottom()))
        return true;
    return false;
}

void CBorder::resizeWithHandles()
{
    QGraphicsItem* item;

    if(normalize(corner))
        foreach(item, childItems())
        {
            switch (item->type())
            {
            case rectangle:
                //static_cast<CRectangle*>(item)->m_Rect.setTopLeft(QPointF(m_cursor.x(),m_cursor.y()));
                static_cast<CRectangle*>(item) ->m_cursor = m_cursor;
                static_cast<CRectangle*>(item)->normalize(m_Rect);
                //m_Rect = static_cast<CCircle*>(item)->m_Rect;
                break;

            case circle:
                //static_cast<CCircle*>(item)->m_Rect.setTopLeft(QPointF(m_cursor.x(),m_cursor.y()));
                static_cast<CCircle*>(item)->m_cursor = m_cursor;
                static_cast<CCircle*>(item)->normalize(m_Rect);
                //m_Rect = static_cast<CCircle*>(item)->m_Rect;
                break;

            case polygan:
                //static_cast<CPolygan*>(item)->m_Rect.setTopLeft(QPointF(m_cursor.x(),m_cursor.y()));
                static_cast<CPolygan*>(item) ->m_cursor = m_cursor;
                static_cast<CPolygan*>(item)->normalize(m_Rect);
                m_Rect = static_cast<CPolygan*>(item)->m_Rect;
                break;

            case bezier:
                //static_cast<CPolygan*>(item)->m_Rect.setTopLeft(QPointF(m_cursor.x(),m_cursor.y()));
                static_cast<CBezier*>(item) ->m_cursor = m_cursor;
                static_cast<CBezier*>(item)->normalize(m_Rect);
                m_Rect = static_cast<CBezier*>(item)->m_Rect;
                break;

            case line:
                //static_cast<CPolygan*>(item)->m_Rect.setTopLeft(QPointF(m_cursor.x(),m_cursor.y()));
                static_cast<CLine*>(item) ->m_cursor = m_cursor;
                static_cast<CLine*>(item)->normalize(m_Rect);
                m_Rect = static_cast<CLine*>(item)->m_Rect;
                break;

            case arc:
                //static_cast<CPolygan*>(item)->m_Rect.setTopLeft(QPointF(m_cursor.x(),m_cursor.y()));
                static_cast<CArc*>(item) ->m_cursor = m_cursor;
                //static_cast<CArc*>(item)->normalize(m_Rect);
                m_Rect = static_cast<CArc*>(item)->m_Rect;
                break;
            }

        }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("cornner handle out of range and your item will be delete automaticlly \n because you try to resize item smaller than will appear!");
        //msgBox.exec();
        //delete this;
    }
}


int CBorder::type() const
{
    return type1;
}

QString CBorder::type()
{
    switch (type1)
    {
    case arc: return "Arc";
    case bezier: return "Bezier";
    case circle: return "Circle";
    case line: return "Line";
    case polygan: return "Poly";
    case rectangle: return "Rec";
    case txt: return "Text";
    }
}

bool CBorder::normalize(int corner)
{

    switch (corner)
    {
    case 1:
        if(m_Rect.right() - m_cursor.x() < 0 || m_Rect.bottom() - m_cursor.y() < 0)
            return false;
        m_Rect.setTopLeft(QPointF(m_cursor.x()-borderMargin,m_cursor.y()-borderMargin));
        break;
    case 2:
        if(m_Rect.bottom() - m_cursor.y() < 0)
            return false;
        m_Rect.setTop(m_cursor.y()-borderMargin+1);
        break;
    case 3:
        if( m_cursor.x() - m_Rect.left() < 0 || m_Rect.bottom() - m_cursor.y() < 0)
            return false;
        m_Rect.setTopRight(QPointF(m_cursor.x()+borderMargin+1,m_cursor.y()-borderMargin-1));
        break;
    case 4:
        if(m_Rect.right() - m_cursor.x() < 0)
            return false;
        m_Rect.setLeft(m_cursor.x()-borderMargin);
        break;
    case 5:
        break;
    case 6:
        if(m_cursor.x() - m_Rect.left() < 0)
            return false;
        m_Rect.setRight(m_cursor.x()+borderMargin+1);
        break;
    case 7:
        if(m_Rect.right() - m_cursor.x() < 0 || m_cursor.y() - m_Rect.top() < 0)
            return false;
        m_Rect.setBottomLeft(QPointF(m_cursor.x()-borderMargin-1,m_cursor.y()+borderMargin+1));
        break;
    case 8:
        if(m_cursor.y() - m_Rect.top() < 0)
            return false;
        m_Rect.setBottom(m_cursor.y()+borderMargin+1);
        break;
    case 9:
        if(m_cursor.x() - m_Rect.left() < 0 || m_cursor.y() - m_Rect.top() < 0)
            return false;
        m_Rect.setBottomRight(QPointF(m_cursor.x()+borderMargin+1,m_cursor.y()+borderMargin+1));
        break;
    default:
        QMessageBox msgBox;
        msgBox.setText("cornner handle out of range");
        msgBox.exec();
    }
    return true;

}

QGraphicsItem *CBorder::selectedItem()
{
    QGraphicsItem* item;
    foreach(item, childItems())
        return item;
}

void CBorder::updateItem()
{
    QGraphicsItem* item;

    foreach(item, childItems())
    {
        switch (item->type())
        {
        case rectangle:
            static_cast<CRectangle*>(item)->abrush = abrush;
            static_cast<CRectangle*>(item)->apen = apen;
            static_cast<CRectangle*>(item)->normalize(m_Rect);
            break;

        case circle:
            static_cast<CCircle*>(item)->abrush = abrush;
            static_cast<CCircle*>(item)->apen = apen;
            static_cast<CCircle*>(item)->normalize(m_Rect);
            break;

        case polygan:
            static_cast<CPolygan*>(item)->abrush = abrush;
            static_cast<CPolygan*>(item)->apen = apen;
            static_cast<CPolygan*>(item)->normalize(m_Rect);
            break;

        case line:
            static_cast<CLine*>(item)->apen.setColor(abrush.color());
            static_cast<CLine*>(item)->apen = apen;
            static_cast<CLine*>(item)->normalize(m_Rect);
            break;

        case arc:
            static_cast<CArc*>(item)->abrush = abrush;
            static_cast<CArc*>(item)->apen = apen;
            static_cast<CArc*>(item)->normalize(m_Rect);
            break;

        case bezier:
            static_cast<CBezier*>(item)->abrush = abrush;
            static_cast<CBezier*>(item)->apen = apen;
            static_cast<CBezier*>(item)->normalize(m_Rect);
            break;

defualt:
            QMessageBox msgBox;
            msgBox.setText("no Item selected or cannot get brush color");
        }
    }
}

void CBorder::setBorderFromItemSize(QGraphicsItem* item)
{
    m_Rect.setRect(item->boundingRect().x()-borderMargin,
                   item->boundingRect().y()-borderMargin,
                   item->boundingRect().width()+2*borderMargin,
                   item->boundingRect().height()+2*borderMargin);
}
