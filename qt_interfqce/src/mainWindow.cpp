#include "mainwindow.hpp"
#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include <iostream>

mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
{
    std::cout << "building the window" << std::endl;
    setFixedSize(800, 600);

    QPushButton *quit = new QPushButton(tr("Quit"), this);
    quit->setGeometry(700, 550, 50, 20);

    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

mainWindow::~mainWindow()
{
    std::cout << "deleting the window" << std::endl;
}


