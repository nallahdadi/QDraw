#ifndef TEXT_H
#define TEXT_H

#include "constants.h"

class CText: public QGraphicsItem
    {
    public:
        CText();
        enum {Type = txt};
        int type() const;
        bool pressed;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF m_Rect;
        QPointF m_cursor;
        QString text;
        QTextOption textOption;

        protected:
            void mousePressEvent(QGraphicsSceneMouseEvent *event);
            void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
            void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TEXT_H
