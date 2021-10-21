#include "gameboard.h"
#include "ui_gameboard.h"

GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameBoard)
{
    ui->setupUi(this);
    connect(ui->menuButton, &QPushButton::clicked,
            this, &GameBoard::goToMenu);
}

GameBoard::~GameBoard()
{
    delete ui;
}

void GameBoard::startNewGame()
{
    //
}
