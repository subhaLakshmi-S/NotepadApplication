#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include<QFontDialog>
#include<QtPrintSupport/QtPrintSupport>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path="";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
   QString file_name=QFileDialog::getOpenFileName(this,"Open the file");
   QFile file(file_name);
   file_path=(file_name);
   if(!file.open(QFile::ReadOnly | QFile::Text)){
       QMessageBox::warning(this,"..","file not open");
       return;
   }
   QTextStream in(&file);
   QString text=in.readAll();
   ui->textEdit->setText(text);
   file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"Save the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);
    QString text=ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionBold_triggered()
{
    bool bold;
    ui->textEdit->setFontWeight(QFont::Bold);
}

void MainWindow::on_actionItalic_triggered()
{
    bool italic;
    ui->textEdit->setFontItalic(true);
}

void MainWindow::on_actionUnderLine_triggered()
{
   bool underline;
   ui->textEdit->setFontUnderline(true);
}

void MainWindow::on_actionSelect_Font_triggered()
{
    bool fontSelected;
    QFont font=QFontDialog::getFont(&fontSelected,this);
    if(fontSelected){
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_actionPrint_triggered()
{
   #if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
       QPrinter print;
   #if QT_CONFIG(printdialog)
       QPrintDialog dialog(&printBow,this);
       if(dialog.exec()==QDialog::Rejected)
           return;
   #endif   //QT_CONFIG(printdialog)
       ui->textEdit->print(&print);
   #endif  //QT_CONFIG(printer)
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
