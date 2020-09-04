#include "vector3editwidget.h"
#include "ui_vector3editwidget.h"

Vector3EditWidget::Vector3EditWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::GroupBox)
{
    ui->setupUi(this);

    connect(ui->xLineEdit, &QLineEdit::textChanged, this, &Vector3EditWidget::coordinateChanged);
    connect(ui->yLineEdit, &QLineEdit::textChanged, this, &Vector3EditWidget::coordinateChanged);
    connect(ui->zLineEdit, &QLineEdit::textChanged, this, &Vector3EditWidget::coordinateChanged);
}

Vector3EditWidget::~Vector3EditWidget()
{
    delete ui;
}

void Vector3EditWidget::coordinateChanged()
{
    mats::Vec3  v;

    v.x() = ui->xLineEdit->text().toDouble();
    v.y() = ui->yLineEdit->text().toDouble();
    v.z() = ui->zLineEdit->text().toDouble();

    emit valueChanged(v);
}

void Vector3EditWidget::toScalar(){
    ui->xLabel->setText("");
    ui->yLabel->setText("Scalar");
    ui->zLabel->setText("");
    ui->xLineEdit->setEnabled(false);
    ui->zLineEdit->setEnabled(false);
    ui->xLineEdit->hide();
    ui->zLineEdit->hide();
    m_scalarMode = true;
}

void Vector3EditWidget::toVector(){
    ui->xLabel->setText("x");
    ui->yLabel->setText("y");
    ui->zLabel->setText("z");
    ui->xLineEdit->setEnabled(true);
    ui->zLineEdit->setEnabled(true);
    ui->xLineEdit->show();
    ui->zLineEdit->show();
    m_scalarMode = false;
}

bool Vector3EditWidget::scalarMode() const{
    return m_scalarMode;
}

void Vector3EditWidget::setResult(const mats::Vec3 &v, const int mode){
    if(mode == 3){
        ui->xLineEdit->setText(QString::number(v.x()));
        ui->yLineEdit->setText(QString::number(v.y()));
        ui->zLineEdit->setText(QString::number(v.z()));
        return;
    }
}

void Vector3EditWidget::setReadOnly(bool r){
    if(r){
        ui->xLineEdit->setReadOnly(true);
        ui->yLineEdit->setReadOnly(true);
        ui->zLineEdit->setReadOnly(true);
    }
}

void Vector3EditWidget::deleteEntries(){
    ui->xLineEdit->setText("");
    ui->yLineEdit->setText("");
    ui->zLineEdit->setText("");
}
