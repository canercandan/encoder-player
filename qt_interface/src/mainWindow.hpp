#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QApplication>
#include <QFont>
#include <QPushButton>
#include <QWidget>
#include "myVideoList.hpp"

class mainWindow : public QWidget
{
private:
public:
    mainWindow(QWidget *parent = 0);
    ~mainWindow();
};

#endif // MAINWINDOW_HPP
