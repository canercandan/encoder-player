#include "PlayButton.hpp"
#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QMainWindow>
#include <QApplication>
#include <QDebug>

qtInterface::PlayButton::PlayButton(QWidget *parent)
{
    std::cout << "building the play button...";
    this->_layout = new QVBoxLayout;
    this->_button = new QPushButton(tr("Play"), this);

    this->_layout->addWidget(this->_button);
    setLayout( this->_layout);
    std::cout << "done." <<std::endl;
    connect(this->_button, SIGNAL(clicked()), this,  SLOT(playSlot()));
}

void    qtInterface::PlayButton::playSlot()
{
     qDebug() << "the clicked signal has been received for the play button";
}
