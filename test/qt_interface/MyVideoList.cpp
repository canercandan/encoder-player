#include <iostream>
#include <fstream>

#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QContextMenuEvent>
#include <QDebug>

#include "MyVideoList.h"

MyVideoList::MyVideoList(QWidget *parent) : QWidget(parent)
{
  qDebug() << "building the videoList...";
  this->_layout = new QVBoxLayout;
  this->_list = new QListWidget;

  this->_layout->addWidget(this->_list);
  setLayout( this->_layout);
  qDebug() << "done.";
}

MyVideoList::~MyVideoList()
{
  qDebug() << "deleting the videoList...";
  delete (this->_layout);
  delete (this->_list);
  qDebug() << "done.";
}

void    MyVideoList::fillInTheList()
{
  qDebug() << "putting informations in the videoList...";
  std::fstream    filestr;
  filestr.open    (PATH);
  std::string     fileLine;
  size_t          found = 0;
  size_t          found2 = 0;

  if (filestr.is_open())
    {
      qDebug() << " reading the " << PATH << "file...";
      while (filestr.getline((char *)fileLine.c_str(), 512))
        {
	  std::string str2 = fileLine.c_str();
	  found2 = str2.find(";", found);
	  std::string str = str2.substr((int)found, (int)found2 - (int)found);

	  found = found2 + 1;
	  found2 = str2.find(";", found);
	  str += " " + str2.substr((int)found, (int)found2 - (int)found);

	  found = found2 + 1;
	  found2 = str2.find(";", found);
	  str += " " + str2.substr((int)found, (int)found2 - (int)found);
	  found = found2 + 1;

	  this->_list->addItem(str.c_str());
        }
      filestr.close();
    }
  else
    {
      qDebug() << "Error opening file";
    }
  qDebug() << " done.";
}

void  MyVideoList::contextMenuEvent(QContextMenuEvent*)
{
  QList<QListWidgetItem *>    items;
  QListWidgetItem             selected;

  items = this->_list->selectedItems();
  if (items.length() > 0)
    this->_list->addItem(items.first()->text());

}
