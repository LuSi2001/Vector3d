#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector.h"
#include "draw.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *fileMenu = ui->menubar->addMenu("&File");

    QAction *quit = fileMenu->addAction("&Quit", qApp, SLOT(quit()));
    QAction *reset = fileMenu->addAction("&Reset", ui->canvas, SLOT(reset()));

    quit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    reset->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

    ui->groupVec1->setValidator();
    ui->groupVec2->setValidator();
    ui->groupVec3->setValidator();
    ui->groupVec3->setReadOnly(true);

    int i = 0;
    while (NameOperation[i].op != Nop)
    {
        ui->comboBox->addItem(NameOperation[i].name, NameOperation[i].op);
        ++i;
    }

    ui->canvas->addDrawFunctor(new PlusDrawOperation);
    ui->canvas->addDrawFunctor(new MinusDrawOperation);
    ui->canvas->addDrawFunctor(new MultiplicationDrawOperation);
    ui->canvas->addDrawFunctor(new DivisionDrawOperation);
    ui->canvas->addDrawFunctor(new CrossProductDrawOperation);
    ui->canvas->addDrawFunctor(new DotProductDrawOperation);

    connect(ui->groupVec1, &Vector3EditWidget::valueChanged,
            [this](const mats::Vec3 &v)
    {
        ui->canvas->setVector(v, Operand::Op1);
        ui->groupVec3->deleteEntries();
        ui->canvas->noResults();
    });
    connect(ui->groupVec2, &Vector3EditWidget::valueChanged,
            [this](const mats::Vec3 &v)
    {
        ui->canvas->setVector(v, Operand::Op2);
        ui->groupVec3->deleteEntries();
        ui->canvas->noResults();
    });
    connect(ui->comboBox, &QComboBox::currentTextChanged,
            [this]()
    {
        Operation op = Operation(ui->comboBox->currentData().toInt());
        ui->canvas->setOperator(op);
        ui->groupVec3->deleteEntries();
        ui->equals->click();
        checkOp(op);
    });
    connect(ui->equals, &QPushButton::clicked, this, &MainWindow::on_equals_clicked);
    connect(ui->canvas, &Canvas::finished,
            [this](const mats::Vec3 &v){ui->groupVec3->setResult(v);});
    connect(ui->canvas, &Canvas::deleteAllEntries, [this]()
    {
        ui->comboBox->setCurrentIndex(0);
        ui->groupVec1->deleteEntries();
        ui->groupVec2->deleteEntries();
        ui->equals->click();
        ui->groupVec3->deleteEntries();
    });
    connect(ui->canvas, &Canvas::vChanged, [this](const mats::Vec3 &v, const int mode)
    {
        if(mode == 0)
        {
            ui->groupVec1->fillEdits(v);
        }
        else
        {
            ui->groupVec2->fillEdits(v);
        }
    });
    connect(ui->canvas, &Canvas::cursorChange, this, &MainWindow::newCursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ++++++++++++++++++++++++++++++++SLOTS+++++++++++++++++++++++++++++++ */
void MainWindow::on_equals_clicked() const
{
    ui->canvas->calcResult();
}

void MainWindow::checkOp(Operation op) const
{
    switch(op)
    {
        case Geteilt:
        case Mal:
            ui->groupVec2->toScalar();
            if(ui->groupVec3->scalarMode())
            {
                ui->groupVec3->toVector();
            }
            break;
        case Skalarprodukt:
            ui->groupVec3->toScalar();
            if(ui->groupVec2->scalarMode())
            {
                ui->groupVec2->toVector();
            }
            break;
        default:
            if(ui->groupVec2->scalarMode())
            {
                ui->groupVec2->toVector();
            }
            if(ui->groupVec3->scalarMode())
            {
                ui->groupVec3->toVector();
            }
            break;
    }
}

void MainWindow::newCursor(const QCursor &cursor)
{
    setCursor(cursor);
}
