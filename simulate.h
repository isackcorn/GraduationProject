#ifndef SIMULATE_H
#define SIMULATE_H

#pragma once
#include <QDialog>
#include "finded_value.h"
#include <QApplication>

namespace Ui {
class Simulate;
}

class Simulate : public QDialog
{
    Q_OBJECT

public:
    explicit Simulate(QWidget *parent = nullptr);
    ~Simulate();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void hide_all_widgets();

    void on_calc_prop_clicked();

private:
    Ui::Simulate *ui;
    finded_value finded_value;
};

#endif // SIMULATE_H
