#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>

class DraggableLabel : public QLabel
{
    Q_OBJECT
public:
    DraggableLabel(QWidget *parent = nullptr);


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    // QWidget interface
protected:
    void dragMoveEvent(QDragMoveEvent* event) override;
};

#endif // DRAGGABLELABEL_H
