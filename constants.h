#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QPainter>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <qmath.h>
#include <QMessageBox>
#include <QToolTip>
#include "thumb.h"

/// margin from original shape and it`s Border
unsigned const int borderMargin = 7;

/// Item typs are declared with unsigned constant inteeger
const int border    = QGraphicsItem::UserType + 1;
const int rectangle = QGraphicsItem::UserType + 2;
const int circle    = QGraphicsItem::UserType + 3;
const int polygan   = QGraphicsItem::UserType + 4;
const int bezier    = QGraphicsItem::UserType + 5;
const int line      = QGraphicsItem::UserType + 6;
const int arc       = QGraphicsItem::UserType + 7;
const int txt      = QGraphicsItem::UserType + 8;

#endif // CONSTANTS_H
