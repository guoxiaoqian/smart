#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MainView.h"
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MainView* mainView;
private slots:
    void genData();
    void openFile();
private:
    void createMenuBar();
    void createToolBar();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
