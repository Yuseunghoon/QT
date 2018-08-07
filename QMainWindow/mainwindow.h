#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ScratchPad;
class MemoAlbum;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();

    void on_actionColor_triggered();

private:
    Ui::MainWindow *ui;
    ScratchPad* m_scratchPad;
    MemoAlbum* m_memoAlbum;

};

#endif // MAINWINDOW_H
