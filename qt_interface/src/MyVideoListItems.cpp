#include "MyVideoListItems.hpp"
#include <iostream>
#include <QWidget>
#include <QListWidgetItem>
#include <QString>
#include <QMouseEvent>
#include <QMessageBox>
#include <QApplication>

MyVideoListItems::MyVideoListItems(QWidget *parent) : QWidget(parent)
{
    this->_widget = new QListWidgetItem();
//    connect(this->_widget, SIGNAL(clicked()), this,  SLOT(monSlot()));
}

void    MyVideoListItems::setText(std::string str)
{
    QString text(str.c_str());
    this->_widget->setText(text);
}

QListWidgetItem *MyVideoListItems::getItem()
{
    return this->_widget;
}

void MyVideoListItems::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        emit monSignal();
    }
}

void MyVideoListItems::monSlot()
{
    exit(0);
}

void    MyVideoListItems::setId(std::string id)
{
    this->_id = id;
}

void    MyVideoListItems::setName(std::string name)
{
    this->_name = name;
}

void    MyVideoListItems::setPath(std::string path)
{
    this->_path = path;
}
