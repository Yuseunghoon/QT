#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scratchpad.h"
#include "memoalbum.h"
#include <QDoubleSpinBox>
#include <QStyle>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scratchPad = new ScratchPad(ui->tabWidget);
    m_memoAlbum = new MemoAlbum(ui->tabWidget);
    ui->tabWidget->addTab(m_memoAlbum, tr("Memo Album"));
    ui->tabWidget->addTab(m_scratchPad, tr("ScratchPad"));
    ui->actionSave->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->actionColor->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));

    QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
    spinBox->setValue(1.0f);
    connect(spinBox, SIGNAL(valueChanged(double)),m_scratchPad,SLOT(setPaintSize(qreal)));
    ui->mainToolBar->addWidget(spinBox);

    resize(1024, 800);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    m_scratchPad->saveimage();
}

void MainWindow::on_actionColor_triggered()
{
    m_scratchPad->setPaintColor();
}
