#include "myVideoList.hpp"
#include "myVideoListItems.hpp"
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <iostream>
#include <fstream>
#include <QContextMenuEvent>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QDebug>

myVideoList::myVideoList(QWidget *parent) : QWidget(parent)
{
    qDebug() << "building the videoList...";
    this->_layout = new QVBoxLayout;
    this->_list = new QListWidget;

    this->_layout->addWidget(this->_list);
    setLayout( this->_layout);
    connect(this->_list, SIGNAL(itemSelectionChanged()), this,  SLOT(getSelectedPath()));
    qDebug() << "done.";
}

myVideoList::~myVideoList()
{
    qDebug() << "deleting the videoList...";
    delete (this->_layout);
    delete (this->_list);
    qDebug() << "done.";
}

void    myVideoList::fillInTheList()
{
    qDebug() << "putting informations in the videoList...";
    std::fstream    filestr;
    filestr.open    (PATH);
    std::string     fileLine;
    size_t          found = 0;
    size_t          found2 = 0;

    if (filestr.is_open())
    {
        qDebug() << "reading the \"" << PATH << "\" file...";
        while (filestr.getline((char *)fileLine.c_str(), 512))
        {
            found = 0;
            found2 = 0;
            myVideoListItems widgetItem;
            std::string str2 = fileLine.c_str();
            found2 = str2.find(";", found);
            std::string str = str2.substr((int)found, (int)found2 - (int)found);
            widgetItem.setId(str);

            found = found2 + 1;
            found2 = str2.find(";", found);
            str += " " + str2.substr((int)found, (int)found2 - (int)found);
            widgetItem.setName(str2.substr((int)found, (int)found2 - (int)found));

            found = found2 + 1;
            found2 = str2.find(";", found);
            str += " " + str2.substr((int)found, (int)found2 - (int)found);
            widgetItem.setPath(str2.substr((int)found, (int)found2 - (int)found));

            widgetItem.setText(str);
            this->_list->addItem(widgetItem.getItem());
        }
        filestr.close();
    }
    else
      {
        qDebug() << "Error opening file";
      }
    qDebug() << "done.";
}

void    myVideoList::w_clicked()
{
    QList<QListWidgetItem *>    items;
    QListWidgetItem             selected;

    items = this->_list->selectedItems();
    if (items.length() > 0)
        this->_list->addItem(items.first()->text());
}

std::string    myVideoList::getSelectedPath()
{
    QList<QListWidgetItem *>    items;
    QListWidgetItem             selected;
    size_t                      pos = 0;

    qDebug() << "Signal itemSelectionChanged received";
    items = this->_list->selectedItems();
    if (items.length() > 0)
    {
        std::string str = items.first()->text().toStdString();
        pos = str.rfind(" ", pos);
        str = str.substr(pos + 1, str.length());
        pos = str.rfind(" ", pos);
        str = str.substr(pos + 1, str.length());
        qDebug() << "You have selected the file :" << str.c_str();
        return (str);
//        QString text(str.c_str());
//        this->_list->addItem(text);
    }
}
