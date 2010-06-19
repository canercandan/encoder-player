#ifndef MYVIDEOLIST_HPP
#define MYVIDEOLIST_HPP

#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QContextMenuEvent>

#define PATH    "video.list"

class   myVideoList : public QWidget
{
private:
    QListWidget *_list;
    QVBoxLayout *_layout;
public:
    myVideoList(QWidget *parent = 0);
    ~myVideoList();
    void    fillInTheList();
protected:
    void    contextMenuEvent(QContextMenuEvent *event);
};

#endif // MYVIDEOLIST_HPP
