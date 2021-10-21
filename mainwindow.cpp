#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDropEvent>
#include <QDragEnterEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pageMEnu, &StartGameMenu::startNewGame,
            [this]()
    {
        //ui->pageGame->startNewGame()
        ui->stackedWidget->setCurrentWidget(ui->pageGame);
    });
    connect(ui->pageGame, &GameBoard::goToMenu,
            [this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->pageMEnu);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
//    event->acceptProposedAction();
    event->accept();//
}

void MainWindow::dropEvent(QDropEvent* event)
{
    std::cout << Q_FUNC_INFO << std::endl;
    event->accept();
}
