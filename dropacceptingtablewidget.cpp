#include "dropacceptingtablewidget.h"
#include <iostream>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QHeaderView>
DropAcceptingTableWidget::DropAcceptingTableWidget(QWidget* parent)
    :QTableWidget(parent)
{
    std::cout << Q_FUNC_INFO << std::endl;
    //setIconSize(QSize(100,100));
    createSquareTable(3);
    horizontalHeader()->hide();
    verticalHeader()->hide();
}


void DropAcceptingTableWidget::dragEnterEvent(QDragEnterEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
    event->acceptProposedAction();
    event->accept();
}

void DropAcceptingTableWidget::dropEvent(QDropEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
    event->acceptProposedAction();
    auto item = itemAt(event->pos());
    if(item)
    {
        std::cout << "Dropped in: " << item->row() << " " <<
                     item->column() << std::endl;
        updateImageOn(item->row(), item->column());
    }
}


void DropAcceptingTableWidget::dragMoveEvent(QDragMoveEvent* event)
{
    //
}

void DropAcceptingTableWidget::createSquareTable(int count)
{
    clear();
    setColumnCount(count);

    for(int row = 0; row < count; row++)
    {
        insertRow(row);
        for(int column = 0; column < count; column++)
        {
            auto thumbnail = new QTableWidgetItem();
            thumbnail->setFlags(thumbnail->flags() ^ Qt::ItemIsEditable);
            thumbnail->setData(Qt::DecorationRole,
                                getScaledApplePixmap(100));
            setItem(row,column,thumbnail);
            resizeColumnsToContents();
            resizeRowsToContents();
        }
    }
}

QPixmap DropAcceptingTableWidget::getScaledApplePixmap(int size)
{
    return QPixmap(":/images/red_apple.jpg").scaled(size,size,Qt::KeepAspectRatio);
}

void DropAcceptingTableWidget::updateImageOn(int row, int column)
{
    ;//
}
