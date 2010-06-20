#include <iostream>

#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QDebug>

#include "MainWindow.h"
#include "MyVideoList.h"
#include "MyPlayer.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
  qDebug() << "building the window";
  setFixedSize(800, 600);

  QPushButton* quit = new QPushButton(tr("Quit"), this);
  connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

  QGridLayout* grid = new QGridLayout;
  MyVideoList* videoList = new MyVideoList;
  videoList->fillInTheList();
  grid->addWidget(videoList, 0, 0);

  MyPlayer* tmp = new MyPlayer;
  grid->addWidget(tmp, 0, 1);
  grid->setColumnMinimumWidth(1, 500);

  QVBoxLayout* layout = new QVBoxLayout;
  layout->addLayout(grid);
  layout->addWidget(quit);
  setLayout(layout);
}

MainWindow::~MainWindow()
{
  qDebug() << "deleting the window";
}
