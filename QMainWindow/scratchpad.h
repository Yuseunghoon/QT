#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H
#include <QWidget>

class ScratchPad : public QWidget
{
    Q_OBJECT

public:
    ScratchPad(QWidget *parent = 0);
    void setPaintColor();
    void saveimage();
public slots:
    void setPaintSize(qreal size);

protected:
    void paintEvent(QPaintEvent *evnet) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *ecent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *ecent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *ecent) Q_DECL_OVERRIDE;


private:
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    QImage image;
    QPointF prevPos;
    QColor paintColor;
    qreal paintSize;
};

#endif // SCRATCHPAD_H
