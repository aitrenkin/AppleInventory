#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>

namespace Ui {
    class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();
public slots:
    void startNewGame();
signals:
    void goToMenu();
private:
    Ui::GameBoard *ui;
};

#endif // GAMEBOARD_H
