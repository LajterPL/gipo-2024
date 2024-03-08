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

    brightness = 0;
    contrast = 0;
    gamma = 100;

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));

    connect(ui->brightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(setBrightness(int)));
    connect(ui->contrastSlider, SIGNAL(valueChanged(int)), this, SLOT(setContrast(int)));
    connect(ui->gammaSlider, SIGNAL(valueChanged(int)), this, SLOT(setGamma(int)));

    connect(ui->brightnessSlider, SIGNAL(sliderReleased()), this, SLOT(transformImage()));
    connect(ui->contrastSlider, SIGNAL(sliderReleased()), this, SLOT(transformImage()));
    connect(ui->gammaSlider, SIGNAL(sliderReleased()), this, SLOT(transformImage()));

    connect(ui->reset_button, SIGNAL(clicked()), this, SLOT(resetTransform()));

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

    transformImage();
}

void MainWindow::setBrightness(int value)
{
    this->brightness = value;
}

void MainWindow::setContrast(int value)
{
    this->contrast = value;
}

void MainWindow::setGamma(int value)
{
    this->gamma = value;
}

void MainWindow::transformImage()
{
    changeBrightness(&ref_img, &trans_img, this->brightness);
    changeContrast(&trans_img, &trans_img, this->contrast);
    changeGamma(&trans_img, &trans_img, this->gamma);
    ui->label->setPixmap(QPixmap::fromImage(trans_img));
}

void MainWindow::resetTransform()
{
    brightness = 0;
    contrast = 0;
    gamma = 100;

    ui->brightnessSlider->setValue(this->brightness);
    ui->contrastSlider->setValue(this->contrast);
    ui->gammaSlider->setValue(this->gamma);

    transformImage();
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
    hist(&trans_img, hist_arr, color);

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
