#ifndef MYVIDEOLIST_HPP
#define MYVIDEOLIST_HPP

#include <iostream>

#include <QWidget>

class QListWidget;
class QVBoxLayout;
class QContextMenuEvent;

#define PATH    "video.list"

class   MyVideoList : public QWidget
{
private:
  QListWidget *_list;
  QVBoxLayout *_layout;
public:
  MyVideoList(QWidget *parent = 0);
  ~MyVideoList();

  void    fillInTheList();
protected:
  void    contextMenuEvent(QContextMenuEvent *event);
};

#endif // MYVIDEOLIST_HPP
