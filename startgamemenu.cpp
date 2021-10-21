#include "startgamemenu.h"
#include "ui_startgamemenu.h"

StartGameMenu::StartGameMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartGameMenu)
{
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked,
            QApplication::instance(),&QApplication::exit);
    connect(ui->newGameButton, &QPushButton::clicked,
            this, &StartGameMenu::startNewGame);
}

StartGameMenu::~StartGameMenu()
{
    delete ui;
}
