/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "commands.h"
#include "border.h"


MoveCommand::MoveCommand(CBorder *RectItem, const QPointF &oldPos,
                 QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myRectItem = RectItem;
    newPos = RectItem->pos();
    myOldPos = oldPos;
}

bool MoveCommand::mergeWith(const QUndoCommand *command)
{
    const MoveCommand *moveCommand = static_cast<const MoveCommand *>(command);
    CBorder *item = moveCommand->myRectItem;

    if (myRectItem != item)
    return false;

    newPos = item->pos();
    setText(QObject::tr("Move %1")
        .arg(createCommandString(myRectItem, newPos)));

    return true;
}

void MoveCommand::undo()
{
    myRectItem->setPos(myOldPos);
    myRectItem->scene()->update();
    setText(QObject::tr("Move %1")
        .arg(createCommandString(myRectItem, newPos)));
}

void MoveCommand::redo()
{
    myRectItem->setPos(newPos);
    setText(QObject::tr("Move %1")
        .arg(createCommandString(myRectItem, newPos)));
}

DeleteCommand::DeleteCommand(QGraphicsScene *scene, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = scene;
    QList<QGraphicsItem *> list = myGraphicsScene->selectedItems();
    list.first()->setSelected(false);
    myRectItem = static_cast<CBorder *>(list.first());
    setText(QObject::tr("Delete %1")
        .arg(createCommandString(myRectItem, myRectItem->pos())));
}

void DeleteCommand::undo()
{
    myGraphicsScene->addItem(myRectItem);
    myGraphicsScene->update();
}

void DeleteCommand::redo()
{
    myGraphicsScene->removeItem(myRectItem);
}

AddCommand::AddCommand(CBorder *border, int addType, QGraphicsScene *graphicsScene, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = graphicsScene;
    myRectItem = border;
    initialPosition = myRectItem->pos();
    graphicsScene->update();
    ++itemCount;
    setText(QObject::tr("Add %1")
        .arg(createCommandString(myRectItem, initialPosition)));
}
//! [7]

AddCommand::~AddCommand()
{
    if (!myRectItem->scene())
        delete myRectItem;
}

//! [8]
void AddCommand::undo()
{
    myGraphicsScene->removeItem(myRectItem);
    myGraphicsScene->update();
}
//! [8]

//! [9]
void AddCommand::redo()
{
    myGraphicsScene->addItem(myRectItem);
    myRectItem->setPos(initialPosition);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}
//! [9]

QString createCommandString(CBorder *item, const QPointF &pos)
{
    return QObject::tr("%1 at (%2, %3)")
        .arg(item->type())
            .arg(pos.x()).arg(pos.y());
}

ResizeCommand::ResizeCommand(CBorder *RectItem,QRectF oldRect, QUndoCommand *parent)
{
    myRectItem = RectItem;
    myNewRect= RectItem->boundingRect();
    myOldRect = oldRect;
}

void ResizeCommand::undo()
{
    myRectItem->m_Rect = myOldRect;
    myRectItem->updateItem();
    myRectItem->scene()->update();
    setText(QObject::tr("Resize %1")
            .arg(createCommandString(myRectItem, myNewRect.topLeft())));
}

void ResizeCommand::redo()
{
    myRectItem->m_Rect = myNewRect;
    myRectItem->updateItem();
    myRectItem->scene()->update();
    setText(QObject::tr("Resize %1")
            .arg(createCommandString(myRectItem,  myNewRect.topLeft())));
}

RotateCommand::RotateCommand(CBorder *RectItem, int angle,QPointF aroundPoint, QUndoCommand *parent)
{
    myRectItem = RectItem;
    myAngle = angle;
    myPoint = aroundPoint;
}

void RotateCommand::undo()
{
    myRectItem->translate(myPoint.x(), -myPoint.y());
    myRectItem->rotate(-myAngle);
    myRectItem->translate(-myPoint.x(), myPoint.y());
    myRectItem->scene()->update();
    setText(QObject::tr("Rotate %1 with %2 deg")
            .arg(myRectItem->type()).arg(myAngle));
}

void RotateCommand::redo()
{
    myRectItem->translate(myPoint.x(), -myPoint.y());
    myRectItem->rotate(myAngle);
    myRectItem->translate(-myPoint.x(), myPoint.y());
    myRectItem->scene()->update();
    setText(QObject::tr("Rotate %1 with %2")
            .arg(myRectItem->type()).arg(myAngle));
}

BrushCommand::BrushCommand(CBorder *RectItem, QBrush oldBrush, QUndoCommand *parent)
{
    myRectItem = RectItem;
    myNewBrush= myRectItem->abrush;
    myOldBrush = oldBrush;
}

void BrushCommand::undo()
{
    myRectItem->abrush = myOldBrush;
    myRectItem->updateItem();
    myRectItem->scene()->update();
    setText(QObject::tr("Brush:%1, %2")
            .arg(myRectItem->type()).arg(myRectItem->abrush.color().name()));
}

void BrushCommand::redo()
{
    myRectItem->abrush = myNewBrush;
    myRectItem->updateItem();
    myRectItem->scene()->update();
    setText(QObject::tr("Brush:%1, %2")
            .arg(myRectItem->type()).arg(myRectItem->abrush.color().name()));
}

PenCommand::PenCommand(CBorder *RectItem, QPen oldPen, QUndoCommand *parent)
{
    myRectItem = RectItem;
    myNewPen= myRectItem->apen;
    myOldPen = oldPen;
}

void PenCommand::undo()
{
    myRectItem->apen = myOldPen;
    myRectItem->updateItem();
    myRectItem->scene()->update();
    setText(QObject::tr("Pen:%1 color: %2, %3")
            .arg(myRectItem->type()).arg(myRectItem->apen.color().name()).arg(myRectItem->apen.width()));
}

void PenCommand::redo()
{
    myRectItem->apen = myNewPen;
    myRectItem->updateItem();
    myRectItem->scene()->update();
    setText(QObject::tr("Pen:%1 color: %2, %3")
            .arg(myRectItem->type()).arg(myRectItem->apen.color().name()).arg(myRectItem->apen.width()));
}
