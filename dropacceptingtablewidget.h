#ifndef DROPACCEPTINGTABLEWIDGET_H
#define DROPACCEPTINGTABLEWIDGET_H

#include <QTableWidget>

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
    QPixmap getScaledApplePixmap(int size);
    void updateImageOn(int row, int column);
};

#endif // DROPACCEPTINGTABLEWIDGET_H
