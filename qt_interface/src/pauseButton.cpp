#include "pauseButton.h"
#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QDebug>

qtInterface::pauseButton::pauseButton(QWidget *parent)
{
    qDebug() << "building the pause button...";
    this->_layout = new QVBoxLayout;
    this->_button = new QPushButton(tr("Pause"), this);

    this->_layout->addWidget(this->_button);
    setLayout( this->_layout);
    connect(this->_button, SIGNAL(clicked()), this,  SLOT(pauseSlot()));
    qDebug() << "done.";
}

void    qtInterface::pauseButton::pauseSlot()
{
    qDebug() << "the clicked signal has been received for the pause button";
}
