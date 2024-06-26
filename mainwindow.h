#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>  // Include QTabWidget for tab functionality
#include <QStandardPaths>
#include "dialog.h"


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
    void on_addButton_clicked();
    void on_clearButton_2_clicked();
    void on_SortButton_clicked();
    void on_DeleteButton_clicked();

    void on_historyButton_clicked();

private:
    Ui::MainWindow *ui;
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/toDoFile.txt";

};
#endif // MAINWINDOW_H
