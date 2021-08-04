#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textbox);
    this->setWindowTitle("Notepad");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered() // If open file button clicked
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file"); // Get open file name
    QFile file(file_name);

    notepad.currentFile_name = file_name;


    if(!file.open(QIODevice::ReadOnly | QFile::Text)) // If can't read file then error
    {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
    }
    else // Else set window title to the file name and paste all the content in textbox
    {
        setWindowTitle(file_name);
        QTextStream inputText(&file);

        QString textFile = inputText.readAll();

        ui->textbox->setText(textFile);

        file.close();
    };
}


void MainWindow::on_actionNew_triggered() // If new button clicked
{
    notepad.currentFile_name.clear();
    ui->textbox->clear();
}


void MainWindow::on_actionExit_triggered() // If exit button clicked
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Notepad", "Are you sure?", QMessageBox::Yes | QMessageBox::No); // Creating a prompt box

    if(reply == QMessageBox::Yes) // If user clicked yes then quit application
    {
        qApp->quit();
    }
}


void MainWindow::on_actionCopy_triggered() // If copy button clicked
{
    ui->textbox->copy();
}


void MainWindow::on_actionPaste_triggered() // If paste button clicked
{
    ui->textbox->paste();
}


void MainWindow::on_actionUndo_triggered() // If undo button clicked
{
    ui->textbox->undo();
}


void MainWindow::on_actionRedo_triggered() // If redo button clicked
{
    ui->textbox->redo();
}


void MainWindow::on_actionSave_as_triggered() // If save as button clicked
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(file_name);

    if(!file.open(QFile::WriteOnly | QFile::Text)) // If cannot write file then error
    {
        QMessageBox::warning(this, "Error", "Cannot save file: " + file.errorString());
    }
    else // Else set window title to the file name and save the file with text from textbox widget
    {
        notepad.currentFile_name = file_name;
        setWindowTitle(file_name);

        QTextStream outputFile(&file);

        QString textFromBox = ui->textbox->toPlainText();

        outputFile << textFromBox;

        file.close();
    }
}

void MainWindow::on_actionPrint_triggered() // If print button clicked
{
    QPrinter printer;
    printer.setPrinterName("Printer");

    QPrintDialog printerDialog(&printer, this);

    if(printerDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Error", "Cannot access printer");
    }
    else
    {
        ui->textbox->print(&printer);
    }
}

