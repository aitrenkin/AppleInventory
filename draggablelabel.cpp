#include "draggablelabel.h"
#include <iostream>
#include <QDrag>
#include <QDragMoveEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QPixmap>
DraggableLabel::DraggableLabel(QWidget* parent)
    :QLabel(parent)
{
    setPixmap(QPixmap(":/images/red_apple.jpg"));
    setScaledContents(true);
}

void DraggableLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            mimeData->setText("1");
            drag->setMimeData(mimeData);
            Qt::DropAction dropAction = drag->exec();
            Q_UNUSED(dropAction);
    }
}

void DraggableLabel::mouseReleaseEvent(QMouseEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
}

void DraggableLabel::mouseMoveEvent(QMouseEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
}


void DraggableLabel::dragMoveEvent(QDragMoveEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
}
