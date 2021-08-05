#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers/notepad.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_action6_triggered();

    void on_action12_triggered();

    void on_action18_triggered();

    void on_action24_triggered();

    void on_action30_triggered();

    void on_action36_triggered();

private:
    Ui::MainWindow *ui;
    Notepad notepad;
};
#endif // MAINWINDOW_H
