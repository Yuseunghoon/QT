#include "qteditor.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QApplication>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QFontDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>

Qteditor::Qteditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);
    QTextEdit *textedit = new QTextEdit(this);
    connect(textedit,SIGNAL(cursorPositionChanged()),SLOT(setFontWidget()));
    mdiArea->addSubWindow(textedit);

    QLabel *label=new QLabel("Dock Widget",this);
    QDockWidget *dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(label);


    //setCentralWidget(textedit);
    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    /*
    QAction *newAct=new QAction(QIcon("new.png"), "&New", this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("make new file"));
    connect(newAct, SIGNAL(triggered()),SLOT(newFile()));

    */

    QAction *newAct = makeAction("new.png","&New","Ctrl+N","Make New FIle", this, SLOT(newFile()));
    QAction *openAct = makeAction("Open.png","&Open","Ctrl+O","Open New FIle", this, SLOT(openFile()));
    QAction *saveAct = makeAction("save.png","&Save","Ctrl+S","Save the FIle", this, SLOT(Save()));
    QAction *saveasAct = makeAction("saveas.png","&Saveas","Ctrl+D","Save the New name", this, SLOT(Saveas()));
    QAction *quitAct = makeAction("quit.png","&Quit","Ctrl+Q","Quit this program", qApp, SLOT(quit()));
    QAction *print = makeAction("","&Print","","Print", this, SLOT(print()));

    QMenu *fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addAction(quitAct);
    fileMenu->addAction(print);

    QAction *undo=new QAction(QIcon("undo.png"),"&Undo", this);
    connect(undo,SIGNAL(triggered()),SLOT(undo1()));
    QAction *redo=new QAction(QIcon("redo.png"),"&Redo", this);
    connect(redo,SIGNAL(triggered()),SLOT(redo1()));
    //QAction *undo = makeAction("undo.png","&Undo","Ctrl+U","undo", textedit, SLOT(undo()));
    //QAction *redo = makeAction("redo.png","&Redo","Ctrl+Y","redo", textedit, SLOT(redo()));
    QAction *copy = makeAction("copy.png","&Copy","Ctrl+C","copy", textedit, SLOT(copy()));
    QAction *cut = makeAction("cut.png","&Cut","Ctrl+X","cut", textedit, SLOT(cut()));
    QAction *paste = makeAction("paste.png","&Paste","Ctrl+V","paste", textedit, SLOT(paste()));
    QAction *zoomin = makeAction("zoomin.png","&Zoomin","Ctrl+I","zoomin", textedit, SLOT(zoomIn()));
    QAction *zoomout = makeAction("zoomout.png","&Zoomout","Ctrl+O","zoomout", textedit, SLOT(zoomOut()));

    QMenu *fileMenu2 = menubar->addMenu("&Edit");
    fileMenu2->addAction(undo);
    fileMenu2->addAction(redo);
    fileMenu2->addAction(copy);
    fileMenu2->addAction(cut);
    fileMenu2->addAction(paste);
    fileMenu2->addAction(zoomin);
    fileMenu2->addAction(zoomout);

    QAction *alignCenterAct1=new QAction(QIcon(":/images/new.jpg"),"&Center", this);
    connect(alignCenterAct1,SIGNAL(triggered()),SLOT(alignCenter()));
    QAction *alignCenterAct2=new QAction("&Right", this);
    connect(alignCenterAct2,SIGNAL(triggered()),SLOT(alignright()));
    QAction *alignCenterAct3=new QAction("&Left", this);
    connect(alignCenterAct3,SIGNAL(triggered()),SLOT(alignleft()));
    QAction *alignCenterAct4=new QAction("&Justify", this);
    connect(alignCenterAct4,SIGNAL(triggered()),SLOT(alignjustify()));

    QAction *font=new QAction("&Font", this);
    connect(font,SIGNAL(triggered()),SLOT(setFont()));
    QAction *setcolor = makeAction("","&Setcolor","","Setcolor",this,SLOT(setcolor()));
    QMenu *fileMenu3 = menubar->addMenu("&Format");
    fileMenu3->addAction(font);
    fileMenu3->addAction(setcolor);
    QMenu *alignMenu=fileMenu3->addMenu("&Align");
    alignMenu->addAction(alignCenterAct1);
    alignMenu->addAction(alignCenterAct2);
    alignMenu->addAction(alignCenterAct3);
    alignMenu->addAction(alignCenterAct4);


    QAction *cascade = makeAction("","&Cascade","","Cascade", this,SLOT(cascade()));
    QAction *tile = makeAction("","&Tile","","Tile", this,SLOT(tile()));
    QAction *prev = makeAction("","&Prev","","Prev", this,SLOT(prev()));
    QAction *next = makeAction("","&Next","","Next", this,SLOT(next()));
    QAction *windows = makeAction("","&Windows","","Windows", this,SLOT(windows()));

    QMenu *fileMenu4 = menubar->addMenu("&Window");
    fileMenu4->addAction(cascade);
    fileMenu4->addAction(tile);
    fileMenu4->addAction(prev);
    fileMenu4->addAction(next);
    fileMenu4->addAction(windows);

    QAction *help = makeAction("","&Help","","Help", qApp, SLOT(aboutQt()));
    QAction *help2=new QAction("&Help2", this);
    connect(help2,SIGNAL(triggered()),SLOT(help()));

    QMenu *fileMenu5 = menubar->addMenu("&Help");
    fileMenu5->addAction(help);
    fileMenu5->addAction(help2);

    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(openAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(saveAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);


    fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),textedit,SLOT(setCurrentFont(QFont)));
    sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));
    addToolBarBreak();

    QToolBar *formatToolbar=addToolBar("&Format");

    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);


    statusbar = statusBar();
    statusLabel = new QLabel("Qt Editor",statusbar);
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);


}

QAction *Qteditor::makeAction(QString icon, QString name, QString shortCut, QString toolTip, QObject *recv, const char *slot)
{
    QAction *act = new QAction(name, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act,SIGNAL(triggered()),recv,slot);
    return act;
}

void Qteditor::cascade(){
    qDebug("cascade");
}

void Qteditor::tile(){
    qDebug("tile");
}

void Qteditor::prev(){
    qDebug("prev");
}

void Qteditor::next(){
    qDebug("next");
}

void Qteditor::windows(){
    qDebug("windows");
}

void Qteditor::print(){
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec()==QDialog::Accepted){
        QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->print(&printer);
    }
}

void Qteditor::setFontWidget(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    QFont font = textedit->currentFont();
    fontComboBox->setCurrentFont(font);
    sizeSpinBox->setValue(font.pointSize());
}

void Qteditor::setcolor(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor(textedit->textColor(),this);
    textedit->setTextColor(color);
}

void Qteditor::help(){
    QMessageBox::information(this,"about","Made by Yu",QMessageBox::Ok);
}

void Qteditor::setFont(){
    bool ok;
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    QFont font = QFontDialog::getFont(&ok,textedit->currentFont(),this);
    if(ok) textedit->setCurrentFont(font);
}
void Qteditor::newFile(){
    qDebug("Make New File");
    QTextEdit *textedit = new QTextEdit;
    mdiArea->addSubWindow(textedit);
    textedit->show();
}

void Qteditor::undo1(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    textedit->undo();
}

void Qteditor::redo1(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    textedit->redo();
}

void Qteditor::alignCenter(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignCenter);
}

void Qteditor::alignright(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignRight);
}

void Qteditor::alignleft(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignLeft);
}

void Qteditor::alignjustify(){
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    textedit->setAlignment(Qt::AlignJustify);
}

void Qteditor::openFile()
{
    qDebug("open file");
    QString filename = QFileDialog::getOpenFileName(this,"Select file to open",".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;

    QFileInfo *fileinfo = new QFileInfo(filename);
    if(fileinfo->isReadable()){
        QByteArray msg;
        QFile *file = new QFile(filename);
        file->open(QIODevice::ReadOnly);
        msg=file->readAll();
        file->close();
        delete file;
        QTextEdit *textedit = new QTextEdit(this);
        textedit->setWindowTitle(filename);
        textedit->setHtml(msg);
        mdiArea->addSubWindow(textedit);
        textedit->show();
    }
    else{
        QMessageBox::warning(this,"Error","Cam't Read this file",QMessageBox::Ok);
    }

}
void Qteditor::Save()
{
    qDebug("save file");
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    QString filename = textedit->windowTitle();
    //QString filename = QFileDialog::getSaveFileName(this,"Select file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
    //qDebug() << filename;
    if(!filename.length()){
        filename = QFileDialog::getSaveFileName(this,"Select a file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
        textedit->setWindowTitle(filename);
    }

    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QFileInfo *fileinfo = new QFileInfo(filename);
    if(fileinfo->isWritable()){
        QByteArray msg;
        msg.append(textedit->toHtml());
        file->write(msg);
    }
    else{
        QMessageBox::warning(this,"Error","Can't Save this file",QMessageBox::Ok);
    }
    file->close();
    delete file;

}
void Qteditor::Saveas()
{
    qDebug("save file");
    QTextEdit *textedit = (QTextEdit *)mdiArea->currentSubWindow()->widget();
    QString filename = QFileDialog::getSaveFileName(this,"Select a file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
    //QString filename = QFileDialog::getSaveFileName(this,"Select file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
    //qDebug() << filename;
    if(!filename.length()){
        filename = QFileDialog::getSaveFileName(this,"Select a file to save",".","Text File(*.txt *.html *.c *.cpp *.h)");
        textedit->setWindowTitle(filename);
    }

    QFile *file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QFileInfo *fileinfo = new QFileInfo(filename);
    if(fileinfo->isWritable()){
        QByteArray msg;
        msg.append(textedit->toHtml());
        file->write(msg);
    }
    else{
        QMessageBox::warning(this,"Error","Can't Save this file",QMessageBox::Ok);
    }
    file->close();
    delete file;

}


Qteditor::~Qteditor()
{

}



