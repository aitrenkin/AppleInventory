#ifndef STARTGAMEMENU_H
#define STARTGAMEMENU_H

#include <QWidget>

namespace Ui {
    class StartGameMenu;
}

class StartGameMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartGameMenu(QWidget *parent = nullptr);
    ~StartGameMenu();
signals:
    void startNewGame();
private:
    Ui::StartGameMenu *ui;
};

#endif // STARTGAMEMENU_H
