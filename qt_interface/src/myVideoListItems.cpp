#include "myVideoListItems.hpp"
#include <iostream>
#include <QWidget>
#include <QListWidgetItem>
#include <QString>
#include <QMouseEvent>
#include <QMessageBox>
#include <QApplication>

myVideoListItems::myVideoListItems(QWidget *parent) : QWidget(parent)
{
    this->_widget = new QListWidgetItem();
//    connect(this->_widget, SIGNAL(clicked()), this,  SLOT(monSlot()));
}

void    myVideoListItems::setText(std::string str)
{
    QString text(str.c_str());
    this->_widget->setText(text);
}

QListWidgetItem *myVideoListItems::getItem()
{
    return this->_widget;
}

void myVideoListItems::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit monSignal();
    }
}

void myVideoListItems::monSlot()
{
    exit(0);
}

void    myVideoListItems::setId(std::string id)
{
    this->_id = id;
}

void    myVideoListItems::setName(std::string name)
{
    this->_name = name;
}

void    myVideoListItems::setPath(std::string path)
{
    this->_path = path;
}
