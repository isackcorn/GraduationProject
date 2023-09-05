#include "calculate_error.h"
#include "qcustomplot.h"
#include <numeric>
#include <QLabel>
#include <QMessageBox>
#include <tuple>

double FindExpect(const QVector<double> &numbers) {//Нахождение среднего значения по вектору
    double expect = 0;
    for (const auto elem: numbers){
        expect += elem;
    }
    return expect / static_cast<double>(numbers.size());
}


double FindDispersion(const QVector<double> &numbers) { //Нахождение выборочной дисперсии
    auto expect = FindExpect(numbers);
    double to_return = 0;
    for (const auto &elem: numbers) {
        to_return += std::pow(elem - expect, 2);
    }
    return to_return / static_cast<double>(numbers.size() - 1);
}

QVector<QString> SplitIntoNumbers(const QString &text) {//Разбитие на числа
    QVector<QString> numbers;
    QString number;

    for (const auto& c: text) {
        if (c == ' ') {
            if (!number.isEmpty()) {
                numbers.push_back(number);
                number.clear();
            }
        } else {
            number += c;
        }
    }
    if (!number.isEmpty()) {
        numbers.push_back(number);
    }

    return numbers;
}

QVector<double> StringToVecDouble(const QString& to_double){ //Перевод в числа с плавающей запятой
    QVector<QString> to_observe = SplitIntoNumbers(to_double);

    QVector<double> toReturn;

    for(const auto& str: to_observe){
        toReturn.emplace_back(str.toDouble());
    }
    return toReturn;
}

QVector<double> CalculateError(const QVector<double>& reference, const QVector<double>& verify){

    QVector<double> to_return;

    for(int i = 0; i < static_cast<int>(reference.size()); ++i){
        to_return.push_back(reference[i] - verify[i]);
    }

    return to_return;

}

std::tuple<double, double, double> FindProbability(double to_find, const QVector<double> &x_freq, const QVector<double> &y_dots){

    std::tuple<double, double, double> to_return;

    for(int i = 1; i < x_freq.size(); ++i){
        if (x_freq[i] > to_find && to_find > x_freq[i - 1]){
            if (i > 0){
                to_return = {y_dots[i - 1], x_freq[i - 1], x_freq[i]};
            }
            else return {y_dots[0], x_freq[0], x_freq[1]};
        }
    }

    return to_return;
}

void MakeDistribution(QCustomPlot* &plotnos, QVector<double>& sample,
                      QVector<double> &x_freq, QVector<double> &y_dots){

    plotnos->clearGraphs();
    plotnos->clearPlottables();
    x_freq.clear();
    y_dots.clear();

    std::sort(sample.begin(), sample.end());

    QVector<double> x_dots;

    int k = std::ceil(1 + (3.31 * log10(sample.size())));

    int n = sample.size();

    double h = (sample[sample.size() - 1] - sample[0]) / static_cast<double>(k);
    double min = sample[0];

    for(int i = 0; i < k; ++i){
        int count = 0;
        for(auto& j: sample){
            if((min + (static_cast<double>(i) * h)) < j && j < (min + (static_cast<double>(i) * h) + h)){
                ++count;
            }
        }
        x_dots.append(min + (static_cast<double>(i) * h) + h / 2.0);
        y_dots.append(count / (static_cast<double>(n)));

    }

    double x_var = min;
    x_freq.push_back(min);
    for(int i = 1; i <= k; ++i){
        x_freq.push_back(x_var + h);
        x_var += h;
    }


    QCPBars *bars = new QCPBars(plotnos->xAxis, plotnos->yAxis);

    plotnos->yAxis->setRange(0, 1);
    plotnos->xAxis->setRange(sample[0], sample[sample.size() - 1]);
    bars->setBrush(QColor(10, 140, 70, 160));
    bars->setData(x_dots, y_dots);
    bars->setWidth(h); // Ширина столбцов

    plotnos->setInteraction(QCP::iRangeZoom, true); // Возможность зумирования графика
    plotnos->setInteraction(QCP::iRangeDrag, true); // Возможность перемещения графика
    // Отображаем гистограмму плотности вероятности
    plotnos->xAxis->setLabel("Погрешность");
    plotnos->yAxis->setLabel("Плотность вероятности");

    plotnos->replot();

}
