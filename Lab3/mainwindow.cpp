#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageprocessing.h"

#include <QFileDialog>
#include "convpopup.h"
#include "ui_convpopup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    conv_popup = new ConvPopup(nullptr);

    medianRadius = 1;

    filter = new int*[3];

    for (int i = 0; i < 3; i++) {
        filter[i] = new int[3];

        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                filter[i][j] = 1;
            } else {
                filter[i][j] = 0;
            }
        }
    }

    filterRadius = 1;

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->reset_button, SIGNAL(pressed()), this, SLOT(resetImage()));

    connect(ui->median_radius_box, SIGNAL(valueChanged(int)), this, SLOT(setMedianRadius(int)));
    connect(ui->median_button, SIGNAL(pressed()), this, SLOT(applyMedianFilter()));

    connect(ui->conv_settings_button, SIGNAL(pressed()), this, SLOT(showConvOptions()));
    connect(ui->conv_button, SIGNAL(pressed()), this, SLOT(applyConv()));
    conv_popup->connect(conv_popup->ui->save_button, SIGNAL(pressed()), this, SLOT(saveConvOptions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isEmpty()) {
        ref_img.load(fileName);
        trans_img = ref_img;
        ui->img_label->setPixmap(QPixmap::fromImage(trans_img));
    }
}

void MainWindow::resetImage()
{
    ui->img_label->setPixmap(QPixmap::fromImage(ref_img));
}

void MainWindow::showConvOptions()
{
    conv_popup->show();
}

void MainWindow::saveConvOptions()
{
    filterRadius = conv_popup->ui->filter_radius->value();

    filter = new int*[2*filterRadius + 1];

    for (int row = 0; row < 2*filterRadius + 1; row++) {
        filter[row] = new int[2*filterRadius + 1];

        for (int col = 0; col < 2*filterRadius + 1; col++) {
            filter[row][col] = conv_popup->ui->filter_values->item(col, row)->text().toInt();
        }
    }

    conv_popup->hide();
}

void MainWindow::applyConv()
{
    customConv(&ref_img, &trans_img, filter, filterRadius);
    ui->img_label->setPixmap(QPixmap::fromImage(trans_img));
}

void MainWindow::applyMedianFilter()
{
    medianFilter(&ref_img, &trans_img, medianRadius);
    ui->img_label->setPixmap(QPixmap::fromImage(trans_img));
}

// Setters

void MainWindow::setMedianRadius(int newMedianRadius)
{
    medianRadius = newMedianRadius;
}
