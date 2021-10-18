#include "dropacceptingtablewidget.h"
#include <iostream>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QHeaderView>
#include <QDrag>
DropAcceptingTableWidget::DropAcceptingTableWidget(QWidget* parent)
    :QTableWidget(parent)
{
    std::cout << Q_FUNC_INFO << std::endl;
    //setIconSize(QSize(100,100));
    createSquareTable(3);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    //

    //todo read from DB
    mInventory = new Inventory(3);

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
        auto r = item->row();
        auto c = item->column();
        std::cout << "Dropped in: " << r << " " << c << std::endl;
        auto toAdd = event->mimeData()->text().toInt();
        mInventory->at(r,c) += toAdd;
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
                                mItem->getScaledApplePixmap(100));
            setItem(row,column,thumbnail);
            resizeColumnsToContents();
            resizeRowsToContents();
        }
    }
}

QPixmap Item::getScaledApplePixmap(int size)
{
    return QPixmap(":/images/red_apple.jpg").scaled(size,size,Qt::KeepAspectRatio); // todo db
}

void DropAcceptingTableWidget::updateImageOn(int row, int column)
{
    auto newCounter = mInventory->at(row,column);
    auto resultedImage = mItem->getScaledApplePixmap(100);
    QPainter painter(&resultedImage);
    painter.drawText(90, 90, QString::number(newCounter));
    item(row,column)->setData(Qt::DecorationRole, resultedImage);
}

Inventory::Inventory(size_t size)
{
    mTableOfCounters.resize(size);
    for(auto &row: mTableOfCounters)
    {
        row.resize(size);
        for(auto &value : row)
            value = 0;
    }
}

size_t& Inventory::at(int row, int column)
{
    return mTableOfCounters[row][column];
}


void DropAcceptingTableWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            auto item = itemAt(event->pos());
            if(!item)
                return;
            auto r = item->row();
            auto c = item->column();
            auto &dragValue = mInventory->at(r, c);
            mimeData->setText(QString::number(dragValue));
            drag->setMimeData(mimeData);
            Qt::DropAction dropAction = drag->exec();
            if(dropAction)
            {
                dragValue = 0;
                updateImageOn(r, c);
            }
    }
    else if(event->button() == Qt::RightButton)
    {
        auto clickedItem = itemAt(event->pos());
        if(clickedItem)
        {
            auto r = clickedItem->row();
            auto c = clickedItem->column();
            mInventory->at(r,c)--; //todo more checks
            updateImageOn(r,c);
        }
    }
}
