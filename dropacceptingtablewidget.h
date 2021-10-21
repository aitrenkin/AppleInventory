#ifndef DROPACCEPTINGTABLEWIDGET_H
#define DROPACCEPTINGTABLEWIDGET_H
#include <QMediaPlayer>
#include <QTableWidget>
#include <QPointer>
//
//
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
//

class Item
{
public:
    Item() = default;
    Item(QString Type, QString IconPath)
        : mType(Type), mIconPath(IconPath){}
    QPixmap getScaledPixmap(int size);
private:
    QString mType;
    QString mIconPath;
};

class Inventory : public QObject // to use QPointer
{
    Q_OBJECT
public:
    Inventory() = default;
    Inventory(size_t size);
    size_t size(){return mTableOfCounters.size();}
    void clear();
    void clearCounters();
    size_t& counterAt(int row, int column);
    QString typeAt(int row, int column);
private:
    QVector<QVector<size_t>> mTableOfCounters;
    QVector<QVector<QString>> mTableOfTypes;
};

class Database
{
public:
    Database(QString dbName);
    void saveInventory(Inventory &toSave);
    void saveItem(Item &toSave);
    Inventory loadInventory();
    Item loadItem(QString type);
    bool isOpen(){return db.isOpen();}
private:
    QSqlDatabase db;
};

class DropAcceptingTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    DropAcceptingTableWidget(QWidget *parent = nullptr);


    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;


    // QWidget interface
protected:
    void dragMoveEvent(QDragMoveEvent* event) override;

private:
    void createSquareTable(int count);
    void updateImageOn(int row, int column);
    void removeAppleOn(QTableWidgetItem *item);
    QPointer<Inventory> mInventory;
    Item mEmptyItem;
    Item mAppleItem;
    Database db;
    QMediaPlayer player;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // DROPACCEPTINGTABLEWIDGET_H
