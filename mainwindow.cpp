#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStandardPaths>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');
            if (parts.length() > 1) {  // Ensure the line is correctly formatted
                QListWidgetItem* item = new QListWidgetItem(parts[0], ui->listWidget);
                item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
                item->setCheckState(parts[1].toInt() ? Qt::Checked : Qt::Unchecked);
                ui->listWidget->addItem(item);
            }
        }
        file.close();
    }
}

MainWindow::~MainWindow() {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem* item = ui->listWidget->item(i);
            int checkState = item->checkState() == Qt::Checked ? 1 : 0;
            out << item->text() << "," << checkState << "\n";
        }
        file.close();
    }
    delete ui;
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
    static int sortOrder = 0;  // Static variable to remember the current sort order

    // Increment the sort order and wrap around after reaching the maximum value
    sortOrder = (sortOrder + 1) % 3;

    // Sort items based on the current sort order
    switch (sortOrder) {
    case 0:
        ui->listWidget->sortItems(Qt::AscendingOrder);
        break;
    case 1:
        ui->listWidget->sortItems(Qt::DescendingOrder);
        break;
    case 2:
        // To revert to the original order, just clear the sorting
        ui->listWidget->setSortingEnabled(false);
        ui->listWidget->sortItems(Qt::AscendingOrder);  // Sort to refresh the original order
        ui->listWidget->setSortingEnabled(true);  // Re-enable sorting
        break;
    }
}



void MainWindow::on_DeleteButton_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);

        // Check if the item is checked
        if (item->checkState() == Qt::Checked) {
            // Remove the checked item from the list widget
            delete ui->listWidget->takeItem(i);
            --i; // Decrement i to handle the removal of the current item
        }
    }

}








void MainWindow::on_historyButton_clicked()
{

   Dialog secdialog;
   secdialog.setModal (true);
   secdialog.exec();

}

