#ifndef MYVIDEOLIST_HPP
#define MYVIDEOLIST_HPP

#include <iostream>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QList>
#include <QListWidgetItem>

#define PATH    "video.list"

class   myVideoList : public QWidget
{
Q_OBJECT
private:
    QListWidget *_list;
    QVBoxLayout *_layout;

public:
    myVideoList(QWidget *parent = 0);
    ~myVideoList();
    void    fillInTheList();
    void    w_clicked();
public slots:
    std::string getSelectedPath();
};

#endif // MYVIDEOLIST_HPP
