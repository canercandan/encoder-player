#include "mainwindow.hpp"
#include "myVideoList.hpp"
#include "myPlayer.hpp"
#include "playButton.hpp"
#include "pauseButton.h"
#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <iostream>
#include <QGridLayout>
#include <QDebug>
#include <QSlider>

mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
{
    qDebug() << "building the window";
    setFixedSize(800, 600);

    QPushButton *quit = new QPushButton(tr("Quit"), this);
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QGridLayout *grid = new QGridLayout;
    myVideoList *videoList = new myVideoList;
    videoList->fillInTheList();
    grid->addWidget(videoList, 0, 0);

    qtInterface::myPlayer *tmp = new qtInterface::myPlayer;
    grid->addWidget(tmp, 0, 1, 0, 2);
    grid->setColumnMinimumWidth(1, 550);

    QGridLayout *grid2 = new QGridLayout;
    qtInterface::playButton *play = new qtInterface::playButton(0);
    grid2->addWidget(play, 0, 0);

    qtInterface::pauseButton *pause = new qtInterface::pauseButton;
    grid2->addWidget(pause, 0, 1);

    QSlider *slider = new QSlider(Qt::Horizontal);
    grid2->addWidget(slider, 0, 3);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(grid);
    layout->addLayout(grid2);
    layout->addWidget(quit);
    setLayout(layout);
}

mainWindow::~mainWindow()
{
    qDebug() <<"deleting the window";
}


