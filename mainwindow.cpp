#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *fileMenu = ui->menubar->addMenu("&File");

    QAction *act = fileMenu->addAction("&Quit", qApp, SLOT(quit()));

    act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
}

MainWindow::~MainWindow()
{
    delete ui;
}

