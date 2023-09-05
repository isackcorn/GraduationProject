#include "two_samples.h"
#include "ui_two_samples.h"
#include "calculate_error.h"
#include "finded_value.h"

QVector<double> sample_2;

QVector<double> x_dots_2;

QVector<double> y_dots_2;

two_samples::two_samples(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::two_samples)
{
    ui->setupUi(this);
}

two_samples::~two_samples()
{
    delete ui;
}

void two_samples::on_pushButton_3_clicked()
{
    QString num = ui->to_find->text();
    if (x_dots_2.empty() || y_dots_2.empty()){
        QMessageBox::warning(this, "Ошибка" ,"Данные не были введены");

    }
    else {
    finded_value.FindedValue(FindProbability(num.toDouble(), x_dots_2, y_dots_2));
    finded_value.open();
    }
}

void two_samples::on_pushButton_clicked()
{
    close();
}

void two_samples::on_Start_Calculatings_clicked()
{
    bool ok = true;

    ui->Summary->clear();
    x_dots_2.clear();
    y_dots_2.clear();

    QVector<double> reference = StringToVecDouble(ui->Reference_readings->toPlainText());
    QVector<double> readings = StringToVecDouble(ui->Readings_to_verify->toPlainText());

    if (reference.size() < readings.size()){
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Ошибка",
                                                                  "Выборки не равны, желаете использовать режим с одним эталоном? "
                                                                  "(Будет выбрано первое значение из эталонной выборки)",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
           double to_fill = reference[0];
           reference.resize(readings.size());
           std::fill(reference.begin(), reference.end(), to_fill);
        }

        else {
            ok = false;
        }

    }

    sample_2 = CalculateError(readings, reference);

    if (sample_2.empty()){
        QMessageBox::warning(this, "Ошибка", "Данные не были введены");
        ok = false;
    }



    if (ok == true){
    ui->Summary->insertPlainText("Математическое ожидание погрешности: ");
    ui->Summary->insertPlainText(QString::number(FindExpect(sample_2)));

    ui->Summary->insertPlainText("\nДисперсия: ");
    ui->Summary->insertPlainText(QString::number(FindDispersion(sample_2)));

    ui->Summary->insertPlainText("\nСКО: ");
    ui->Summary->insertPlainText(QString::number(std::pow(FindDispersion(sample_2), 0.5)));

    MakeDistribution(ui->plotnos, sample_2, x_dots_2, y_dots_2);
    }

}

void two_samples::on_pushButton_4_clicked()
{
    ui->Reference_readings->clear();
    QFile file(QFileDialog::getOpenFileName(this, "Open file", "", "Text files (*.txt)"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream (&file);
    QString text = stream.readAll();
    ui->Reference_readings->insertPlainText(text);
    file.close();
}

void two_samples::on_pushButton_5_clicked()
{
    ui->Readings_to_verify->clear();
    QFile file(QFileDialog::getOpenFileName(this, "Open file", "", "Text files (*.txt)"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream (&file);
    QString text = stream.readAll();
    ui->Readings_to_verify->insertPlainText(text);
    file.close();
}

