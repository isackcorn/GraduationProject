#include "simulation.h"
#include "ui_simulation.h"
#include "calculate_error.h"


Simulation::Simulation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Simulation)
{
    ui->setupUi(this);
}

Simulation::~Simulation()
{
    delete ui;
}

void Simulation::on_pushButton_clicked()
{
    double min = ui->lineEdit->text().toDouble();
    double max = ui->lineEdit_2->text().toDouble();
}

