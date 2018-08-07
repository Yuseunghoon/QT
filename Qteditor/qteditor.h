#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

class QAction;
class QLabel;
//class QTextEdit;
class QMdiArea;
class QFontComboBox;
class QDoubleSpinBox;

class Qteditor : public QMainWindow
{
    Q_OBJECT

public:
    Qteditor(QWidget *parent = 0);
    ~Qteditor();

private:
    QAction *makeAction(QString icon, QString name, QString shortCut, QString toolTip, QObject *recv, const char *slot);
    QStatusBar *statusbar;
    QLabel *statusLabel;
    //QTextEdit *textedit;
    QMdiArea *mdiArea;
    QFontComboBox *fontComboBox;
    QDoubleSpinBox *sizeSpinBox;

public slots:
    void newFile();
    void openFile();
    void Save();
    void Saveas();
    void alignCenter();
    void alignright();
    void alignleft();
    void alignjustify();
    void undo1();
    void redo1();
    void setFont();
    void help();
    void setcolor();
    void setFontWidget();
    void print();
    void cascade();
    void tile();
    void prev();
    void next();
    void windows();

};


#endif // QTEDITOR_H
