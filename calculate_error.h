#pragma once
#include <iostream>
#include <vector>
#include <QString>
#include <QtAlgorithms>
#include <algorithm>
#include <numeric>
#include <complex>
#include <QVector>
#include <QLabel>
#include "qcustomplot.h"

double FindExpect(const QVector<double> &numbers);


double FindDispersion(const QVector<double> &numbers);

QVector<QString> SplitIntoNumbers(const QString &text);

QVector<double> StringToVecDouble(const QString& to_double);

QVector<double> CalculateError(const QVector<double>& reference, const QVector<double>& verify);

void MakeDistribution(QCustomPlot* &plotnos, QVector<double>& sample,
                      QVector<double> &x_freq, QVector<double> &y_dots);

std::tuple<double, double, double> FindProbability(double to_find, const QVector<double> &x_freq, const QVector<double> &y_dots);

void FindMisses(QVector<double> &sample);
