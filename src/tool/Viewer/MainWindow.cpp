#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "generator.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createMenuBar();
    createToolBar();

    mainView = new MainView();
    setCentralWidget(mainView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenuBar()
{
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));

    QAction * genAct = new QAction(QString("gen"),fileMenu);
    QAction * openAct = new QAction(QString("open"),fileMenu);
    QAction * saveAct = new QAction(QString("save"),fileMenu);
    fileMenu->addAction(genAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    connect(genAct,SIGNAL(triggered()),this,SLOT(genData()));
    connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));
}

void MainWindow::createToolBar()
{
}

void MainWindow::genData()
{
    Generator* gen = new Generator;
    gen->Start();
    delete gen;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open data file"), "", tr("Data Files (*.dat)"));
    mainView->readObjects(fileName);
}
