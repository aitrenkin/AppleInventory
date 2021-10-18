#ifndef DROPACCEPTINGTABLEWIDGET_H
#define DROPACCEPTINGTABLEWIDGET_H

#include <QTableWidget>
#include <QPointer>
class Item : public QObject
{
    Q_OBJECT
public:
    Item() = default;
    Item(QString Type, QString IconPath)
        : mType(Type), mIconPath(IconPath){}
    QPixmap getScaledApplePixmap(int size);
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
    void clear();
    void clearCounters();
    size_t& at(int row, int column);
private:
    QVector<QVector<size_t>> mTableOfCounters;
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
    QPointer<Inventory> mInventory;
    QPointer<Item> mItem;
};

#endif // DROPACCEPTINGTABLEWIDGET_H
