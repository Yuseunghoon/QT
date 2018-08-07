#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QTimer>

class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = 0);
    ~CustomButton();
private:
    bool m_isEnterd;
    bool m_isHighlighted;
    QTimer m_timer;
protected:
    void paintEvent(QPaintEvent*);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
signals:
    void clicked();
};

#endif // CUSTOMBUTTON_H
