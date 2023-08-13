#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QUndoCommand>
#include <QUndoView>
#include "constants.h"
#include "border.h"
#include "arcdialog.h"
#include "textdialog.h"
#include "itemeditdialog.h"
#include "ui_itemeditdialog.h"

namespace Ui {
    class view;
}

class view : public QMainWindow
{
    Q_OBJECT

public:
    explicit view(QWidget *parent = 0);
    void createUndoView();
    void createItem(int type);
    void createAreaGroup(CBorder* bd);
    void createLineGroup(CBorder* bd);
    ~view();
    QPointF Start;
    QPointF End;
    bool press;
    QBrush dlgBrush;
    QPen   dlgPen;

public slots:
    void itemMoved(CBorder* bd, QPointF moveStartPosition);
    void itemResized(CBorder *bd, QRectF ResizeFirstRect);
    void MouseDoubleClicked(CBorder* bd,QGraphicsSceneMouseEvent *event);
    void customBtClick(QColor eColor);


private slots:
    void newAct();
    void addRectAct();
    void addCircleAct();
    void addPolyAct();
    void addBezierAct();
    void addLineAct();
    void addArcAct();
    void addTextAct();
    void RotateAct();
    void Rotate2Act();
    void setColorAct();
    void undoAct();
    void redoAct();

private:
    Ui::view *ui;
    QGraphicsScene *scene;
    QGraphicsItem  *currItem;
    CBorder    *border;
    QList<QGraphicsItem* > itemList;

    arcDialog* arcDlg;
    TextDialog* txtDlg;

    QUndoStack *undoStack;
    QUndoView *undoView;
    QUndoCommand *addCommand, *moveCommand, *deleteCommand, *reziseCommand, *rotateCommand, *brushCommand;
    ItemEditDialog* editDlg;

      void mousePressEvent(QMouseEvent *event);
      void keyPressEvent(QKeyEvent * event);
//    void mouseMoveEvent(QMouseEvent *evet);
//    void mouseReleaseEvent(QMouseEvent *evet);

};

#endif // VIEW_H
