#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageprocessing.h"
#include <iostream>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(changeBrightness(int)));
    connect(ui->contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(changeContrast(int)));
    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(changeGamma(int)));

    connect(ui->hist_r_button, SIGNAL(clicked()), this, SLOT(showHistR()));
    connect(ui->hist_g_button, SIGNAL(clicked()), this, SLOT(showHistG()));
    connect(ui->hist_b_button, SIGNAL(clicked()), this, SLOT(showHistB()));
    connect(ui->hist_l_button, SIGNAL(clicked()), this, SLOT(showHistL()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isEmpty()) {
        ref_img.load(fileName);
        trans_img = ref_img;
        ui->label->setPixmap(QPixmap::fromImage(trans_img));
    }
}

void MainWindow::changeBrightness(int value)
{
    brightness(&ref_img, &trans_img, value);
    ui->label->setPixmap(QPixmap::fromImage(trans_img));
}

void MainWindow::changeContrast(int value)
{
    contrast(&ref_img, &trans_img, value);
    ui->label->setPixmap(QPixmap::fromImage(trans_img));
}

void MainWindow::changeGamma(int value)
{
    float fv = value/50.0f;
    gamma(&ref_img, &trans_img, fv);
    ui->label->setPixmap(QPixmap::fromImage(trans_img));
}

void MainWindow::showHistR()
{
    showHistogram(0);
}

void MainWindow::showHistG()
{
    showHistogram(1);
}

void MainWindow::showHistB()
{
    showHistogram(2);
}

void MainWindow::showHistL()
{
    showHistogram(3);
}

void MainWindow::showHistogram(int color) {
    QImage hist_img(256, 100, QImage::Format_ARGB32);
    hist_img.fill(qRgb(0, 0, 0));

    unsigned int hist_color = 0;

    switch(color) {
    case 0:
        hist_color = qRgb(255, 0, 0);
        break;
    case 1:
        hist_color = qRgb(0, 255, 0);
        break;
    case 2:
        hist_color = qRgb(0, 0, 255);
        break;
    default:
        hist_color = qRgb(255, 255, 255);
        break;
    }

    int hist_arr[256] = {0};
    hist(&ref_img, hist_arr, color);

    int max_hist_value = 0;

    for (int i = 0; i < 256; i++) {

        if (max_hist_value < hist_arr[i]) {
            max_hist_value = hist_arr[i];
        }
    }

    float scale = hist_img.height()/(float)max_hist_value;

    for(int x = 0; x < 256; x++) {

        int v = hist_arr[x];

        for(int y = 0; y < v*scale ; y++) {
            hist_img.setPixel(x, 99 - y, hist_color);
        }
    }

    ui->hist_label->setPixmap(QPixmap::fromImage(hist_img));
}
