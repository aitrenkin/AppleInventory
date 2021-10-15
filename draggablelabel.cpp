#include "draggablelabel.h"
#include <iostream>
#include <QResource>
#include <QDir>
#include <QPixmap>
DraggableLabel::DraggableLabel(QWidget* parent)
    :QLabel(parent)
{
    setPixmap(QPixmap(":/images/red_apple.jpg"));
    setScaledContents(true);
}

void DraggableLabel::mousePressEvent(QMouseEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
}

void DraggableLabel::mouseReleaseEvent(QMouseEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
}

void DraggableLabel::mouseMoveEvent(QMouseEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
}
