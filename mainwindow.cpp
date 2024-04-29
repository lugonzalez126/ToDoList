#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(path);
    if(!file.open(QIODevice::ReadWrite)) { //open file
        QMessageBox::information(0, "error", file.errorString());// gives error if no file for todo list is vailable
    }

    QTextStream in(&file); //Reads File

    while(!in.atEnd()){
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item); // adds the item
        item->setFlags(item->flags() | Qt::ItemIsEditable); //makes the item editable
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // makes the item checkable
        item->setCheckState(Qt::Unchecked);

    }
    file.close();

}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file(path);
    if(!file.open(QIODevice::ReadWrite)) { //open file
        QMessageBox::information(0, "error", file.errorString());// gives error if no file for todo list is vailable
    }

    QTextStream out(&file); //Reads File

    for ( int i = 0; i < ui->listWidget->count(); ++i){
        out<<ui->listWidget->item(i)->text()<<"\n";

    }
    file.close();
}

void MainWindow::on_addButton_clicked()
{
    // Trim the text and check if it's empty
    QString taskText = ui->txtTask->text().trimmed();
    if (taskText.isEmpty()) {
        // If the text is empty, clear the input field and return immediately, ignoring the input
        ui->txtTask->clear();
        ui->txtTask->setFocus();
        return;  // Exit the function early without adding the item
    }

    // Create the new list item since the input is valid
    QListWidgetItem* item = new QListWidgetItem(taskText, ui->listWidget);
    ui->listWidget->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);  // Start with the checkbox unchecked

    // Clear the input field and set focus back to it for a new entry
    ui->txtTask->clear();
    ui->txtTask->setFocus();
}


void MainWindow::on_clearButton_2_clicked()
{
    ui->listWidget->clear(); //clears the list

}



void MainWindow::on_SortButton_clicked()
{

}


