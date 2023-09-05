#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QtMath"
#include <algorithm>
#include <QVector>
#include <QtAlgorithms>
#include <cmath>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() //Переход в режим симуляции
{
    simulate.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    two_samples_.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    one_sample_.show();
}








