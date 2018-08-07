#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

}

Widget::~Widget()
{

}

/*
void Widget::writeSettings()
{
    QSettings settings("myapp.ini", QSettings::IniFormat);
    settings.beginGroup("MainWindow");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.setValue("fullScreen",isFullScreen());
    settings.endGroup();

    if(settings.value("fullScreen").toBool())
        setWindowState(windowState()^Qt::WindownFullscreen);
    settings.endGroup();
}
*/
