#include "mainwindow.hpp"
#include "myVideoList.hpp"
#include "myPlayer.hpp"
#include "playButton.hpp"
#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <iostream>
#include <QGridLayout>

mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
{
    std::cout << "building the window" << std::endl;
    setFixedSize(800, 600);

    QPushButton *quit = new QPushButton(tr("Quit"), this);
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QGridLayout *grid = new QGridLayout;
    myVideoList *videoList = new myVideoList;
    videoList->fillInTheList();
    grid->addWidget(videoList, 0, 0);

    qtInterface::myPlayer *tmp = new qtInterface::myPlayer;
    grid->addWidget(tmp, 0, 1, 0, 2);
    grid->setColumnMinimumWidth(1, 500);

    qtInterface::playButton *play = new qtInterface::playButton(0);
    grid->addWidget(play, 1, 1);

    qtInterface::playButton *pause = new qtInterface::playButton;
    grid->addWidget(pause, 1, 2);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(grid);
    layout->addWidget(quit);
    setLayout(layout);
}

mainWindow::~mainWindow()
{
    std::cout << "deleting the window" << std::endl;
}


