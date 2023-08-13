#include "view.h"
#include "ui_view.h"


class CBorder;
#include "commands.h"

view::view(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view)
{
    dlgBrush = QBrush(Qt::lightGray);
    dlgPen.setColor(Qt::black);

    press = false;
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    createUndoView();
    editDlg = new ItemEditDialog(this);
    connect(editDlg,SIGNAL(customBtClick(QColor)),this,SLOT(customBtClick(QColor)));
    //rectItem = new CRectangle();
    // scene->addItem(rectItem);
}

view::~view()
{
    delete ui;
}

void view::newAct()
{
    undoStack->~QUndoStack();
    undoView->~QUndoView();
    createUndoView();
    scene->clear();
    scene->update();
}

void view::addRectAct()
{
    createItem(rectangle);
}

void view::addCircleAct()
{
    createItem(circle);
}

void view::addPolyAct()
{
    QToolTip::showText(this->pos(),"begin with click on the drawing space!");
    createItem(polygan);
}

void view::addBezierAct()
{
    QToolTip::showText(this->pos(),"begin with click on the drawing space! and then put 3 point");
    createItem(bezier);
}

void view::addLineAct()
{
    createItem(line);
}

void view::addArcAct()
{
    arcDlg = new arcDialog(this);
    arcDlg->show();
    if(arcDlg->exec() == QDialog::Accepted)
    {
        createItem(arc);
    }
}

void view::addTextAct()
{
    txtDlg = new TextDialog(this);
    txtDlg->show();
    if(txtDlg->exec() == QDialog::Accepted)
    {
        createItem(txt);
    }
}

void view::RotateAct()
{
    QGraphicsItem * item;
    foreach(item,itemList)
        if(item->isSelected())
        {
            CBorder* temp = static_cast<CBorder*>(item);
            undoStack->push(new RotateCommand(temp,30,QPointF(35,-35)));
            //setTransform(QTransform().translate(100, 100).rotate(30).translate(-100, -100));
            // item->setTransformOriginPoint(100,100);
            //item->setToolTip("Heloooooooo");
            //item->setTransform(QTransform().translate(100, 100).rotate(30).translate(-100, -100));
            //temp->translate( 35, -35 );
            //temp->rotate( 30 );
            //temp->translate( -35, 35 );
        }
    update();
}

void view::Rotate2Act()
{
    QGraphicsItem * item;
    foreach(item,itemList)
        if(item->isSelected())
        {
            CBorder* temp = static_cast<CBorder*>(item);
            undoStack->push(new RotateCommand(temp,-30,QPointF(35,-35)));
            // item->setTransformOriginPoint(100,100);
            //item->setToolTip("Heloooooooo");
            //item->setTransform(QTransform().translate(100, 100).rotate(-30).translate(-100, -100));
            //temp->translate( 35, -35 );
            //temp->rotate( -30 );
            //temp->translate( -35, 35 );
        }
    update();
}

void view::mousePressEvent(QMouseEvent *event)
{
    press = true;
    Start = event->pos();
    //    QGraphicsItem * item;
    //    foreach(item,itemList)
    //        if(item->isSelected())
    //            if(event->button() == Qt::RightButton)
    //            {
    //                QColorDialog colorDlg(this);
    //                colorDlg.show();
    //            }

    QMainWindow::mousePressEvent(event);
}

void view::keyPressEvent(QKeyEvent *event)
{
    if(event == QKeySequence::Delete)
        undoStack->push(new DeleteCommand(scene));
    else if(event ==  QKeySequence::Undo) {
        undoStack->undo();
        update();
    }
    else if(event ==  QKeySequence::Redo) {
        undoStack->redo();
        update();
    }
}

void view::setColorAct()
{
    QColorDialog colorDlg(this);
    colorDlg.show();
    if(colorDlg.exec() == QDialog::Accepted)
    {
        dlgBrush = colorDlg.selectedColor();
        QGraphicsItem * item;
        foreach(item,itemList)
            if(item->isSelected())
            {
                CBorder* temp =static_cast<CBorder*>(item);
                QBrush oldBrush = temp->abrush;
                temp->abrush= dlgBrush;
                undoStack->push( new BrushCommand(temp,oldBrush));
            }
    }
}

void view::undoAct()
{
    undoStack->undo();
    update();
}

void view::redoAct()
{
    undoStack->redo();
    update();
}

void view::itemMoved(CBorder *bd, QPointF moveStartPosition)
{
    undoStack->push(new MoveCommand(bd, moveStartPosition));
}

void view::itemResized(CBorder *bd, QRectF ResizeFirstRect)
{
    undoStack->push(new ResizeCommand(bd,ResizeFirstRect));
}

void view::MouseDoubleClicked(CBorder *bd, QGraphicsSceneMouseEvent *event)
{
    editDlg->show();

    editDlg->update();
    if(editDlg->exec() == QDialog::Accepted)
    {
        createAreaGroup(bd);
        createLineGroup(bd);
    }
}

void view::customBtClick(QColor eColor)
{
    QGraphicsItem * item;
    foreach(item,itemList)
        if(item->isSelected())
        {
            CBorder* temp = static_cast<CBorder*>(item);
            QBrush oldBrush = temp->abrush;
            temp->abrush=  eColor;
            undoStack->push( new BrushCommand(temp,oldBrush));
        }
}

void view::createUndoView()
{
    undoStack = new QUndoStack(this);
    undoView = new QUndoView(undoStack,ui->undoTab);
    undoView->setWindowTitle(tr("Command List"));
    undoView->setGeometry(8,80,180,440);
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

void view::createItem(int type)
{
    border = new CBorder(type);
    switch(type)
    {
    case rectangle:
        currItem = new CRectangle(dlgBrush,dlgPen); break;
    case circle:
        currItem = new CCircle(dlgBrush,dlgPen); break;
    case polygan:
        currItem = new CPolygan(dlgBrush,dlgPen);
        border->setSelected(true);
        static_cast<CBorder*>(border)->drawCHandle = false; break;

    case bezier:
        currItem = new CBezier(dlgBrush,dlgPen);
        static_cast<CBorder*>(border)->drawCHandle = false; break;

    case line:
        currItem = new CLine(dlgBrush,dlgPen); break;

    case arc:
        currItem = new CArc(dlgBrush,dlgPen);
        static_cast<CArc*>(currItem)->startAngle = arcDlg->getStartAngle();
        static_cast<CArc*>(currItem)->spanAngle =  arcDlg->getSpanAngle();
        static_cast<CArc*>(currItem)->m_Rect.setWidth(arcDlg->getWidth());
        static_cast<CArc*>(currItem)->m_Rect.setHeight(arcDlg->getHeight());
        static_cast<CArc*>(currItem)->setItemType(arcDlg->getType());
        static_cast<CBorder*>(border)->drawCHandle = false; break;

    case txt: currItem = new CText();
        static_cast<CText*>(currItem)->text = txtDlg->text; break;
    }
    border->setBorderFromItemSize(currItem);
    currItem->setParentItem(border);

    //scene->addItem(border);
    connect(border, SIGNAL( itemMoved(CBorder*,QPointF)),this, SLOT(itemMoved(CBorder*,QPointF)));
    connect(border, SIGNAL(itemResized(CBorder*,QRectF)),this, SLOT(itemResized(CBorder*,QRectF)));
    connect(border, SIGNAL(MouseDoubleClicked(CBorder*,QGraphicsSceneMouseEvent*)),
            this, SLOT(MouseDoubleClicked(CBorder*,QGraphicsSceneMouseEvent*)));
    undoStack->push(new AddCommand(border,type,scene));
    itemList << static_cast<CBorder*>(border);
}

void view::createAreaGroup(CBorder *bd)
{
    QBrush b;
    switch(editDlg->ui->brushComboBox->currentIndex())
    {
    case 0:  b.setStyle(Qt::NoBrush);       break;
    case 2:  b.setStyle(Qt::SolidPattern);  break;
    case 1:  b.setStyle(Qt::Dense1Pattern); break;
    case 3:  b.setStyle(Qt::Dense2Pattern); break;
    case 4:  b.setStyle(Qt::Dense3Pattern); break;
    case 5:  b.setStyle(Qt::Dense4Pattern); break;
    case 6:  b.setStyle(Qt::Dense5Pattern); break;
    case 7:  b.setStyle(Qt::Dense6Pattern); break;
    case 8:  b.setStyle(Qt::Dense7Pattern); break;
    case 9:  b.setStyle(Qt::HorPattern);    break;
    case 10: b.setStyle(Qt::VerPattern);    break;
    case 11: b.setStyle(Qt::CrossPattern);  break;
    case 12: b.setStyle(Qt::BDiagPattern);  break;
    case 13: b.setStyle(Qt::FDiagPattern);  break;
    case 14: b.setStyle(Qt::DiagCrossPattern);      break;
    case 15: b.setStyle(Qt::LinearGradientPattern); break;
    case 16: b.setStyle(Qt::RadialGradientPattern); break;
    case 17: b.setStyle(Qt::ConicalGradientPattern);break;
    }

    if(editDlg->ui->bColorcomboBox->currentIndex() != 8)
    {
        editDlg->ui->customButton->setText("");
        editDlg->ui->customButton->setStyleSheet(QObject::tr("background-color: %1").arg(editDlg->ui->bColorcomboBox->currentText()));
        QBrush oldBrush = bd->abrush;
        b.setColor(QColor(editDlg->ui->bColorcomboBox->currentText()));
        bd->abrush= b;
        undoStack->push( new BrushCommand(bd,oldBrush));
    }
}

void view::createLineGroup(CBorder *bd)
{

    QPen p;
    QPen oldPen;
    switch(editDlg->ui->lineComboBox->currentIndex())
    {
    case 0: p.setStyle(Qt::SolidLine);  break;
    case 1: p.setStyle(Qt::DashLine);  break;
    case 2: p.setStyle(Qt::DotLine);   break;
    case 3: p.setStyle(Qt::DashDotLine);     break;
    case 4: p.setStyle(Qt::DashDotDotLine);  break;
    }
    p.setColor(editDlg->ui->pColorcomboBox->currentText());
    p.setWidth(editDlg->ui->doubleSpinBox->value());
    oldPen = bd->apen;
    bd->apen = p;
    undoStack->push( new PenCommand(bd,oldPen));
}
