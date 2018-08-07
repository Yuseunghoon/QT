#include <QtWidgets>

#include "scratchpad.h"

#define RADIUS      5

ScratchPad::ScratchPad(QWidget *parent) :                        QWidget(parent), paintSize(1), modified(false) {
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_StaticContents);
    paintColor = Qt::black;
}

void ScratchPad::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    const QRect rect = event->rect();
    painter.drawImage(rect.topLeft(), image, rect);       /* �붾㈃�� �대�吏�瑜� �쒕줈�� */
}

void ScratchPad::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();            /* �댁쟾�� �곸뿭蹂대떎 �꾩옱 �곸뿭�� 而ㅼ��� 寃쎌슦�먮쭔 �ш린 議곗젙*/
    }
    QWidget::resizeEvent(event);
}

void ScratchPad::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize) return;         /* �덈줈�� �ш린濡� 踰꾪띁瑜� �덈∼寃� �앹꽦 */
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScratchPad::mousePressEvent(QMouseEvent* event)    /* 留덉슦�ㅻ� �뚮졇�� �� */
{
    prevPos = event->pos();                     /* �댁쟾 �먯쓽 �꾩튂 湲곗뼲 */
    QPen pen(paintColor, paintSize);
    pen.setCapStyle(Qt::RoundCap);
    QPainter painter(&image);
    painter.setPen(pen);
    painter.drawPoint(prevPos);                 /* �꾩옱�� �꾩튂�� �� 洹몃━湲� */
    painter.end();
    modified = true;
}

void ScratchPad::mouseMoveEvent(QMouseEvent* event)       /* 留덉슦�� �대룞�� */
{
    QPointF newPos = event->pos();         /* �댁쟾 �먯쓽 �꾩튂 湲곗뼲 */
    if(modified) {
        QPen pen(paintColor, paintSize);
        pen.setCapStyle(Qt::RoundCap);     /* 蹂대떎 遺��쒕윭�� �좎쓣 �꾪빐 �ㅼ젙 */
        pen.setJoinStyle(Qt::RoundJoin);
        QPainter painter(&image);
        painter.setPen(pen);
        painter.drawLine(prevPos, newPos);      /* �댁쟾 �먯뿉�� �꾩옱 �먭퉴吏� �� 洹몃━湲� */
        painter.end();
    }
    int x1, x2, y1, y2;                                    /* �띾룄瑜� �꾪빐 �꾩옱 蹂��붾맂 遺�遺꾩쓣 */
    if(prevPos.x() < newPos.x()) {                  /* 怨꾩궛�댁꽌 �붾㈃ �낅뜲�댄듃 */
        x1 = prevPos.x(); x2 = newPos.x();
    } else {
        x1 = newPos.x(); x2 = prevPos.x();
    }

    if(prevPos.y() < newPos.y()) {
        y1 = prevPos.y(); y2 = newPos.y();
    } else {
        y1 = newPos.y(); y2 = prevPos.y();
    }

    QRectF rect(x1, y1, x2, y2);
    update(rect.toRect().adjusted(-RADIUS, -RADIUS, +RADIUS, +RADIUS));
    prevPos = newPos;
}

void ScratchPad::mouseReleaseEvent(QMouseEvent* event)  /* 留덉슦�ㅻ� �볦븯�꾨븣 */
{
    QPen pen(paintColor, paintSize);
    pen.setCapStyle(Qt::RoundCap);
    QPainter painter(&image);
    painter.setPen(pen);
    painter.drawPoint(prevPos);             /* �� 洹몃━湲� */
    painter.end();
    modified = false;

    update();
}

void ScratchPad::setPaintColor(){
    paintColor = QColorDialog::getColor(paintColor,this);
}

void ScratchPad::saveimage(){
    QString filename=QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+".png";
    image.save(filename);
}

void ScratchPad::setPaintSize(qreal size){
    paintSize = size;
}

