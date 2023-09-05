#include "simulate.h"
#include "ui_simulate.h"
#include <random>
#include "calculate_error.h"
#include <QMessageBox>
#include "finded_value.h"
#include <QApplication>

QVector<double> sample_sim (100000);

QVector<double> x_dots_sim;

QVector<double> y_dots_sim;

Simulate::Simulate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Simulate)
{
    ui->setupUi(this);
    Simulate::hide_all_widgets();

}

Simulate::~Simulate()
{
    delete ui;
}

void Simulate::hide_all_widgets(){
    ui->label_disp->hide();
    ui->label_exp->hide();
    ui->label_mean_norm->hide();

    ui->disp_norm->hide();
    ui->mean_norm->hide();
    ui->lambda_exp->hide();
};

void Simulate::on_pushButton_clicked()
{
    ui->Summary->clear();
    sample_sim.clear();
    ui->plotnos->clearGraphs();
    ui->plotnos->clearPlottables();

    std::mt19937 gen(1701);




    if (ui->comboBox->currentIndex() == 1){

        double mean = ui->mean_norm->text().toDouble();
        double disp = ui->disp_norm->text().toDouble();

        std::normal_distribution<> distr(mean, disp);

        for(int i = 0; i < 100000; ++i){
            sample_sim.push_back(distr(gen));
        }

        MakeDistribution(ui->plotnos, sample_sim, x_dots_sim, y_dots_sim);

        ui->Summary->insertPlainText("Максимальный элемент: ");
        ui->Summary->insertPlainText(QString::number(sample_sim[sample_sim.size() - 1]));

        ui->Summary->insertPlainText("\nМинимальный элемент: ");
        ui->Summary->insertPlainText(QString::number(sample_sim[0]));
    }

    else if (ui->comboBox->currentIndex() == 2){

        double lambda = ui->lambda_exp->text().toDouble();

        std::exponential_distribution<> distr(lambda);

        for(int i = 0; i < 100000; ++i){
            sample_sim.push_back(distr(gen));
        }

        MakeDistribution(ui->plotnos, sample_sim, x_dots_sim, y_dots_sim);

        ui->Summary->insertPlainText("Математическое ожидание погрешности: ");
        ui->Summary->insertPlainText(QString::number(FindExpect(sample_sim)));

        ui->Summary->insertPlainText("\nДисперсия: ");
        ui->Summary->insertPlainText(QString::number(FindDispersion(sample_sim)));

    }

    else {
            QMessageBox::warning(this, "Ошибка" ,"Данные не были введены");
        }



}


void Simulate::on_comboBox_currentIndexChanged(int index)
{
    Simulate::hide_all_widgets();

    if (index == 1){
        ui->label_mean_norm->show();
        ui->label_disp->show();
        ui->disp_norm->show();
        ui->mean_norm->show();
    }

    if (index == 2){
        ui->lambda_exp->show();
        ui->label_exp->show();
    }
}


void Simulate::on_calc_prop_clicked()
{
   QString num = ui->prop->text();

   if (x_dots_sim.empty() || y_dots_sim.empty()){
       QMessageBox::warning(this, "Ошибка" ,"Данные не были введены");

   }
   else {
   finded_value.FindedValue(FindProbability(num.toDouble(), x_dots_sim, y_dots_sim));
   finded_value.open();
   }
}
