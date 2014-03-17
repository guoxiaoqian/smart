#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "generator.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createMenuBar();
    createToolBar();

    mainView = new MainView();
    setCentralWidget(mainView);

    setFixedSize(1000,700);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenuBar()
{
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));

    QAction * openAct = fileMenu->addAction(QString("open"));
    QAction * genAct = fileMenu->addAction(QString("gen"));

    connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(genAct,SIGNAL(triggered()),this,SLOT(genData()));
}

void MainWindow::createToolBar()
{
}

void MainWindow::genData()
{
    Generator* gen = new Generator;
    gen->Start();
    delete gen;
    QMessageBox::information(this,"tip","generate success!");
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open data file"), "", tr("Data Files (*.dat)"));
    if(!fileName.isEmpty())
        mainView->readObjects(fileName);
}
