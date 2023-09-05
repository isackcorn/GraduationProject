#ifndef TWO_SAMPLES_H
#define TWO_SAMPLES_H

#pragma once
#include <QDialog>
#include "finded_value.h"

namespace Ui {
class two_samples;
}

class two_samples : public QDialog
{
    Q_OBJECT

public:
    explicit two_samples(QWidget *parent = nullptr);
    ~two_samples();

private slots:
    void on_Start_Calculatings_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::two_samples *ui;
    finded_value finded_value;
};

#endif // TWO_SAMPLES_H
