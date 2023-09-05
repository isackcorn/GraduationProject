#include "finded_value.h"
#include "ui_finded_value.h"
#include <tuple>

finded_value::finded_value(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finded_value)
{
    ui->setupUi(this);
}

finded_value::~finded_value()
{
    delete ui;
}

void finded_value::FindedValue(std::tuple<double, double, double> x){
    ui->lineEdit->clear();
    ui->lineEdit->insert("Относительная частота возникновения погрешности в интервале от ");
    ui->lineEdit->insert(QString::number(std::round(std::get<1>(x) * 100) / 100));
    ui->lineEdit->insert(" до ");
    ui->lineEdit->insert(QString::number(std::round(std::get<2>(x) * 100) / 100));
    ui->lineEdit->insert(" = ");
    ui->lineEdit->insert(QString::number(std::round(std::get<0>(x) * 100) / 100));

    ui->lineEdit->isReadOnly();
}
