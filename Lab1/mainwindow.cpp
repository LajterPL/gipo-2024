#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageprocessing.h"

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

