#include "dropacceptingtablewidget.h"
#include <iostream>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QHeaderView>
#include <QDrag>
#include <QMessageBox>
DropAcceptingTableWidget::DropAcceptingTableWidget(QWidget* parent)
    :QTableWidget(parent)
    ,db("GameObjects")
{
    if(!db.isOpen())
    {
        QMessageBox::critical(this,"Error","Can not open database GameObjects");
        return;
    }
    mEmptyItem = db.loadItem("Empty");
    mAppleItem = db.loadItem("Apple");
    horizontalHeader()->hide();
    verticalHeader()->hide();
    //
    size_t inventorySize = 3;
    createSquareTable(inventorySize);
    mInventory = new Inventory(inventorySize);
}

void DropAcceptingTableWidget::startNewGame()
{
    int size = 3;
    mInventory = new Inventory(size);
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
            updateImageOn(x,y);
}


void DropAcceptingTableWidget::dragEnterEvent(QDragEnterEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
    event->acceptProposedAction();
    event->accept();
}

void DropAcceptingTableWidget::dropEvent(QDropEvent* event)
{
    auto item = itemAt(event->pos());
    if(item)
    {
        auto r = item->row();
        auto c = item->column();
        //
        int previousRow,previousColumn;
        auto coords = event->mimeData()->property("from").toStringList();
        if(coords.size() == 2) // проверим не кидаем ли в старую ячейку
        {
            previousRow = coords.at(0).toInt();
            previousColumn = coords.at(1).toInt();
            if(r == previousRow && c == previousColumn)
                return;
        }
        event->acceptProposedAction();
        //
        //std::cout << "Dropped in: " << r << " " << c << std::endl;
        auto toAdd = event->mimeData()->text().toInt();
        mInventory->counterAt(r,c) += toAdd;
        mInventory->typeAt(r,c) = "Apple";
        updateImageOn(item->row(), item->column());
        db.saveInventory(*mInventory);
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
                                mEmptyItem.getScaledPixmap(100));
            setItem(row,column,thumbnail);
            resizeColumnsToContents();
            resizeRowsToContents();
        }
    }
}

void DropAcceptingTableWidget::updateImageOn(int row, int column)
{
    auto newCounter = mInventory->counterAt(row,column);
    QPixmap resultedImage;//
    if(newCounter > 0)
    {
        resultedImage = mAppleItem.getScaledPixmap(100);
        QPainter painter(&resultedImage);
        painter.drawText(90, 90, QString::number(newCounter));
    }
    else
        resultedImage = mEmptyItem.getScaledPixmap(100);
    item(row,column)->setData(Qt::DecorationRole, resultedImage);
}

void DropAcceptingTableWidget::removeAppleOn(QTableWidgetItem* item)
{
    if(!item)
        return;
    auto r = item->row();
    auto c = item->column();
    if(mInventory->counterAt(r,c) == 0) // nothing to delete
        return;
    mInventory->counterAt(r,c)--;
    updateImageOn(r,c);
    player.setMedia(QUrl("qrc:/snd/crunch.mp3"));
    player.setPosition(700);
    player.setVolume(100);
    player.play();
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
    mTableOfTypes.resize(size);
    for(auto &row : mTableOfTypes)
    {
        row.resize(size);
        for(auto &value : row)
            value = "Empty";
    }
}

size_t& Inventory::counterAt(int row, int column)
{
    return mTableOfCounters[row][column];
}

QString& Inventory::typeAt(int row, int column)
{
    return mTableOfTypes[row][column];
}


void DropAcceptingTableWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            auto item = itemAt(event->pos());
            if(!item)
            {
                delete mimeData;
                return;
            }
            auto r = item->row();
            auto c = item->column();
            auto &dragValue = mInventory->counterAt(r, c);
            mimeData->setText(QString::number(dragValue));
            mimeData->setProperty("from",QStringList{
                                      QString::number(r),
                                      QString::number(c)
                                  });
            drag->setMimeData(mimeData);
            Qt::DropAction dropAction = drag->exec();
            if(dropAction)
            {
                dragValue = 0;
                updateImageOn(r, c);
            }
    }
    //delete apple
    else if(event->button() == Qt::RightButton)
    {
        auto clickedItem = itemAt(event->pos());
        if(clickedItem)
            removeAppleOn(clickedItem);
    }
}

Database::Database(QString dbName)
{
    QString driver = "QSQLITE";
    if(!QSqlDatabase::isDriverAvailable(driver))
        return;
      db = QSqlDatabase::addDatabase(driver,"SQLITE");
      db.setDatabaseName(dbName);
      if(!db.open())
      {
          std::cout << "Can't open " << dbName.toStdString() << " : " <<
                       db.lastError().text().toStdString() << std::endl;
          return;
      }
//      auto tables = db.tables().toStdList();
//      std::cout << "tables: " << std::endl;
//      for(const auto &t : tables)
//          std::cout << t.toStdString() << std::endl;
}

void Database::saveInventory(Inventory& toSave)
{
    auto size = toSave.size();
    if(size == 0)
        return;
    QSqlQuery query(db);
    query.prepare("DELETE FROM Inventory");
    if(!query.exec())
    {
        std::cout << Q_FUNC_INFO << std::endl ;
        std::cout << "ERROR: " << query.lastError().text().toStdString();
    }
    for(size_t x = 0; x < size; x++)
    {
        for(size_t y = 0; y < size; y++)
        {
            query.prepare("INSERT INTO Inventory VALUES(?,?,?,?)");
            query.addBindValue(int(x));
            query.addBindValue(int(y));
            query.addBindValue(int(toSave.counterAt(x,y)));
            query.addBindValue(toSave.typeAt(x,y));
            if(!query.exec())
                std::cout << "Can not exec query: " << query.lastError().text().toStdString() << std::endl;
        }
    }
}

void Database::saveItem(Item& toSave)
{
//
}

Inventory Database::loadInventory()
{
//?
}
//Qvariant?
Item Database::loadItem(QString type)
{
    QSqlQuery query(QString("SELECT image FROM Item WHERE itemType='%1'").arg(type),db);
    std::cout << query.lastQuery().toStdString() << std::endl;
    if(!query.exec())
    {
        std::cout << Q_FUNC_INFO << std::endl;
        std::cout << "Type: " << type.toStdString() << std::endl;
        std::cout << "ERROR: " << query.lastError().text().toStdString() << std::endl;

    }
    query.last();
    Item result(type, query.value(0).toString());
    return result;
}

QPixmap Item::getScaledPixmap(int size)
{
    return QPixmap(mIconPath).scaled(size,size,Qt::KeepAspectRatio);
}
