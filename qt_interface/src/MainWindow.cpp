#include "MainWindow.hpp"
#include "MyVideoList.hpp"
#include "MyPlayer.hpp"
#include "playButton.hpp"
#include "pauseButton.h"
#include "windowTitleBar.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <iostream>
#include <QGridLayout>
#include <QDebug>
#include <QSlider>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    qDebug() << "building the window";
    setFixedSize(800, 600);
//    setWindowFlags(Qt::FramelessWindowHint);

    QGridLayout *titleBarLayout = new QGridLayout;
    titleBarLayout->setMargin(0);  // No space between window's element and the border
    titleBarLayout->setSpacing(0); // No space between window's element
    titleBarLayout->addWidget(&(this->titleBar), 0, 0);
//    titleBarLayout->setRowStretch(1, 1); // Put the title bar at the top of the window

    QPushButton *quit = new QPushButton(tr("Quit"), this);
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QGridLayout *grid = new QGridLayout;
    MyVideoList *videoList = new MyVideoList;
    videoList->fillInTheList();
    grid->addWidget(videoList, 0, 0);

    qtInterface::MyPlayer *tmp = new qtInterface::MyPlayer;
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
 //   layout->addLayout(titleBarLayout);
    layout->addLayout(grid);
    layout->addLayout(grid2);
    layout->addWidget(quit);
    setLayout(layout);
}

MainWindow::~MainWindow()
{
    qDebug() <<"deleting the window";
}

void MainWindow::paintEvent2(QPaintEvent *event)
{
    Q_UNUSED(event);

      if(m_Cache != NULL)
      {
        QPainter painter(this);

        painter.drawPixmap(0, 0, *(this->m_Cache));
      }
}

void MainWindow::resizeEvent2(QResizeEvent *event)
{
  Q_UNUSED(event);

  delete m_Cache;

  m_Cache = new QPixmap(size());

  m_Cache->fill(Qt::transparent);

  QPainter painter(m_Cache);

  QColor darkBlue ( 23,  23,  34);
  QColor lightBlue(177, 177, 203);

  /********** Window's background **********/
  QPolygon background;

  background << QPoint(           0,            16)
             << QPoint(          16,             0)
             << QPoint(width() -  1,             0)
             << QPoint(width() -  1, height() - 33)
             << QPoint(width() - 17, height() - 17)
             << QPoint(         272, height() - 17)
             << QPoint(         256, height() -  1)
             << QPoint(          16, height() -  1)
             << QPoint(          16,           272)
             << QPoint(           0,           256);

  painter.setPen  (QPen  (darkBlue));
  painter.setBrush(QBrush(darkBlue));

  painter.drawPolygon(background);
  /*****************************************/

  /********** Window's frame **********/
  QPolygon frame;

  frame << QPoint(           4,            20)
        << QPoint(          20,             4)
        << QPoint(width() -  4,             4)
        << QPoint(width() -  4, height() - 37)
        << QPoint(width() - 20, height() - 21)
        << QPoint(         268, height() - 21)
        << QPoint(         252, height() -  5)
        << QPoint(          20, height() -  5)
        << QPoint(          20,           268)
        << QPoint(           4,           252);

  painter.setPen  (QPen(lightBlue));
  painter.setBrush(Qt::NoBrush    );

  painter.drawPolygon(frame);
  /*****************************************/

}



