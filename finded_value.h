#ifndef FINDED_VALUE_H
#define FINDED_VALUE_H

#include <QDialog>
#include <tuple>

namespace Ui {
class finded_value;
}

class finded_value : public QDialog
{
    Q_OBJECT

public:
    explicit finded_value(QWidget *parent = nullptr);

    ~finded_value();

    void FindedValue(std::tuple<double, double, double> x);

private:
    Ui::finded_value *ui;
};

#endif // FINDED_VALUE_H
