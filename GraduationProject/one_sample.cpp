#include "one_sample.h"
#include "ui_one_sample.h"
#include "calculate_error.h"
#include "cmath"
#include <utility>
#include "QMessageBox"
#include <numeric>

QVector<double> sample;

QVector<double> x_dots;

QVector<double> y_dots;

one_sample::one_sample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::one_sample)
{
    ui->setupUi(this);
}

one_sample::~one_sample()
{
    delete ui;
}

void one_sample::on_pushButton_2_clicked() //Возврат в главное меню
{
    close();
}

void one_sample::on_pushButton_3_clicked()
{
   QString num = ui->to_find->text();
   if (x_dots.empty() || y_dots.empty()){
       QMessageBox::warning(this, "Ошибка" ,"Данные не были введены");

   }
   else {
   finded_value.FindedValue(FindProbability(num.toDouble(), x_dots, y_dots));
   finded_value.open();
   }
}

void one_sample::on_pushButton_clicked()
{
    ui->Summary->clear();

    sample = StringToVecDouble(ui->Reference_readings->toPlainText());

    if (sample.empty()) {
        QMessageBox::warning(this, "Ошибка", "Данные не были введены");
    }

    else {
        double expect = FindExpect(sample);

        ui->Summary->insertPlainText("Математическое ожидание погрешности: ");
        ui->Summary->insertPlainText(QString::number(expect));

        ui->Summary->insertPlainText("\nДисперсия: ");
        ui->Summary->insertPlainText(QString::number(FindDispersion(sample)));

        ui->Summary->insertPlainText("\nСКО: ");
        ui->Summary->insertPlainText(QString::number(std::pow(FindDispersion(sample), 0.5)));

        MakeDistribution(ui->plotnos, sample, x_dots, y_dots);


    }
}


void one_sample::on_pushButton_4_clicked()
{
    ui->Reference_readings->clear();
    QFile file(QFileDialog::getOpenFileName(this, "Open file", "", "Text files (*.txt)"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream (&file);
    QString text = stream.readAll();
    ui->Reference_readings->insertPlainText(text);
    file.close();
}

