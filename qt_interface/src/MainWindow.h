#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QPaintEvent>
#include <QWidget>
#include <QPixmap>
#include "MyVideoList.hpp"
#include "windowTitleBar.h"

class MainWindow : public QWidget
{
private:
    windowTitleBar  titleBar;
    QPixmap         *m_Cache;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent2(QPaintEvent *event);
    void resizeEvent2(QResizeEvent *event);
};

#endif // MAINWINDOW_HPP
