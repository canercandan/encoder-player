#ifndef MYVIDEOLISTITEMS_HPP
#define MYVIDEOLISTITEMS_HPP

#include <iostream>
#include <QWidget>
#include <QListWidgetItem>
#include <QMouseEvent>

class   myVideoListItems : public QWidget
{
Q_OBJECT
private:
    QListWidgetItem     *_widget;
    std::string         _id;
    std::string         _name;
    std::string         _path;
public:
    myVideoListItems(QWidget *parent = 0);
    void                setText(std::string);
    QListWidgetItem     *getItem();
    void                mousePressEvent(QMouseEvent *event);
    void                setId(std::string);
    void                setName(std::string);
    void                setPath(std::string);

public slots:
    void monSlot();
signals:
    void clicked();

};

#endif // MYVIDEOLISTITEMS_HPP
