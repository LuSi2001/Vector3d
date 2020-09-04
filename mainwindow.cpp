#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    int i = 0;

    while (NameOperation[i].op != Nop)
    {
        g_namedOperations.insert({NameOperation[i].name, NameOperation[i]});
        ++i;
    }

    ui->setupUi(this);

    QMenu *fileMenu = ui->menubar->addMenu("&File");

    QAction *quit = fileMenu->addAction("&Quit", qApp, SLOT(quit()));
    QAction *reset = fileMenu->addAction("&Reset", ui->canvas, SLOT(reset()));

    quit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    reset->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

    ui->groupVec3->setReadOnly(true);

    ui->comboBox->addItem("+");
    ui->comboBox->addItem("-");
    ui->comboBox->addItem("*");
    ui->comboBox->addItem("/");
    ui->comboBox->addItem("x");
    ui->comboBox->addItem("°");

    connect(ui->groupVec1, &Vector3EditWidget::valueChanged,
            [this](const mats::Vec3 &v){ui->canvas->setVector(v, Operand::Op1);});
    connect(ui->groupVec2, &Vector3EditWidget::valueChanged,
            [this](const mats::Vec3 &v){ui->canvas->setVector(v, Operand::Op2);});
    connect(ui->comboBox, &QComboBox::currentTextChanged,
            [this](const QString &text){
                            ui->canvas->setOperator(text);
                            checkOp(getOp(text));
                            });
    connect(ui->equals, &QPushButton::clicked, this, &MainWindow::on_equals_clicked);
    connect(ui->canvas, &Canvas::finished,
            [this](const mats::Vec3 &v, const int mode){ui->groupVec3->setResult(v, mode);});
    connect(ui->canvas, &Canvas::deleteAllEntries, [this](){
        ui->comboBox->setCurrentIndex(0);
        ui->groupVec1->deleteEntries();
        ui->groupVec2->deleteEntries();
        ui->equals->click();
        ui->groupVec3->deleteEntries();
    });

//    connect(ui->resetBtn, SIGNAL(clicked()), ui->canvas, SLOT(reset()));

//    connect(ui->resetBtn, &QPushButton::clicked, ui->canvas, &Canvas::reset);

//    int mode = 2;

//    connect(ui->resetBtn, &QPushButton::clicked,
//            [this, mode](){this->ui->canvas->reset(mode);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_equals_clicked(){
    ui->canvas->calcResult();
}

void MainWindow::checkOp(Operation op){

//    if(op == Geteilt or op == Mal){
//        ui->groupVec2->toScalar();
//    } else {
//        if(ui->groupVec2->scalarMode()){
//            ui->groupVec2->toVector();
//        }
//    }
//    if(op == Skalarprodukt){
//        ui->groupVec3->toScalar();
//    } else {
//        if(ui->groupVec3->scalarMode()){
//            ui->groupVec3->toVector();
//        }
//    }
    switch(op){
        case Geteilt:
        case Mal:
            ui->groupVec2->toScalar();
            if(ui->groupVec3->scalarMode()){
                ui->groupVec3->toVector();
            }
            break;
        case Skalarprodukt:
            ui->groupVec3->toScalar();
            if(ui->groupVec2->scalarMode()){
                ui->groupVec2->toVector();
            }
            break;
        default:
            if(ui->groupVec2->scalarMode()){
                ui->groupVec2->toVector();
            }
            if(ui->groupVec3->scalarMode()){
                ui->groupVec3->toVector();
            }
            break;
    }
}
