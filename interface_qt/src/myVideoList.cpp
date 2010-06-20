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

myVideoList::myVideoList(QWidget *parent) : QWidget(parent)
{
    std::cout << "building the videoList...";
    this->_layout = new QVBoxLayout;
    this->_list = new QListWidget;

    this->_layout->addWidget(this->_list);
    setLayout( this->_layout);
    std::cout << "done." <<std::endl;
    connect(this->_list, SIGNAL(itemSelectionChanged()), this,  SLOT(getSelectedPath()));
}

myVideoList::~myVideoList()
{
    std::cout << "deleting the videoList...";
    delete (this->_layout);
    delete (this->_list);
    std::cout << "done." <<std::endl;
}

void    myVideoList::fillInTheList()
{
    std::cout << "putting informations in the videoList...";
    std::fstream    filestr;
    filestr.open    (PATH);
    std::string     fileLine;
    size_t          found = 0;
    size_t          found2 = 0;

    if (filestr.is_open())
    {
        std::cout << " reading the " << PATH << "file...";
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
        std::cout << "Error opening file";
      }
    std::cout << " done." << std::endl;
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

    items = this->_list->selectedItems();
    if (items.length() > 0)
    {
        std::string str = items.first()->text().toStdString();
        pos = str.rfind(" ", pos);
        str = str.substr(pos + 1, str.length());
        pos = str.rfind(" ", pos);
        str = str.substr(pos + 1, str.length());
        return (str);
//        QString text(str.c_str());
//        this->_list->addItem(text);
    }
}
