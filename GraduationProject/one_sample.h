#pragma once
#include <QDialog>
#include <numeric>
#include "finded_value.h"

namespace Ui {
class one_sample;
}

class one_sample : public QDialog
{
    Q_OBJECT

public:
    explicit one_sample(QWidget *parent = nullptr);
    ~one_sample();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::one_sample *ui;
    finded_value finded_value;
};
