#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QPaintEvent>
#include <QWidget>
#include <QPixmap>
#include "myVideoList.hpp"
#include "windowTitleBar.h"

class mainWindow : public QWidget
{
private:
    windowTitleBar  titleBar;
    QPixmap         *m_Cache;
public:
    mainWindow(QWidget *parent = 0);
    ~mainWindow();
protected:
    void paintEvent2(QPaintEvent *event);
    void resizeEvent2(QResizeEvent *event);
};

#endif // MAINWINDOW_HPP
