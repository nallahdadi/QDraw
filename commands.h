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

#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>

#include "border.h"

class MoveCommand : public QUndoCommand
{
public:

    enum {Id = 1234};
    MoveCommand(CBorder *RectItem, const QPointF &oldPos,
                QUndoCommand *parent = 0);
    bool mergeWith(const QUndoCommand *command);
    int id() const { return Id; }
    void undo();
    void redo();

private:
    CBorder *myRectItem;
    QPointF myOldPos;
    QPointF newPos;
};

class DeleteCommand : public QUndoCommand
{
public:
    DeleteCommand(QGraphicsScene *graphicsScene, QUndoCommand *parent = 0);

    void undo();
    void redo();

private:
    CBorder *myRectItem;
    QGraphicsScene *myGraphicsScene;
};

class AddCommand : public QUndoCommand
{
public:
    AddCommand(CBorder* border, int addType, QGraphicsScene *graphicsScene,
               QUndoCommand *parent = 0);
    ~AddCommand();

    void undo();
    void redo();

private:
    CBorder *myRectItem;
    QGraphicsScene *myGraphicsScene;
    QPointF initialPosition;
};

class ResizeCommand : public QUndoCommand
{
public:
    ResizeCommand(CBorder *RectItem, QRectF oldRect,
               QUndoCommand *parent = 0);

    void undo();
    void redo();

private:
    CBorder *myRectItem;
    QRectF  myOldRect;
    QRectF  myNewRect;
    int myCorner;
};

class RotateCommand : public QUndoCommand
{
public:
    RotateCommand(CBorder *RectItem, int angle, QPointF aroundPoint, QUndoCommand *parent=0);

    void undo();
    void redo();

private:
    CBorder *myRectItem;
    QPointF myPoint;
    int myAngle;
};

class BrushCommand : public QUndoCommand
{
public:
    BrushCommand(CBorder *RectItem,QBrush oldBrush, QUndoCommand *parent =0 );

    void undo();
    void redo();

private:
    CBorder *myRectItem;
    QBrush myNewBrush;
    QBrush myOldBrush;
};

class PenCommand : public QUndoCommand
{
public:
    PenCommand(CBorder *RectItem,QPen oldPen, QUndoCommand *parent =0 );

    void undo();
    void redo();

private:
    CBorder *myRectItem;
    QPen myNewPen;
    QPen myOldPen;
};

QString createCommandString(CBorder *item, const QPointF &point);

#endif
