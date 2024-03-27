#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageprocessing.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    moveX = 0;
    moveY = 0;
    rotation = 0;

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->reset_button, SIGNAL(pressed()), this, SLOT(resetImage()));

    connect(ui->x_move_box, SIGNAL(valueChanged(int)), this, SLOT(moveImage()));
    connect(ui->y_move_box, SIGNAL(valueChanged(int)), this, SLOT(moveImage()));

    connect(ui->rotation_slider, SIGNAL(sliderReleased()), this, SLOT(rotateImage()));
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

void MainWindow::moveImage()
{
    this->setMoveX(ui->x_move_box->value());
    this->setMoveY(ui->y_move_box->value());

    IMAGEPROCESSING_H::moveImage(&ref_img, &trans_img, moveX, moveY);
    ui->img_label->setPixmap(QPixmap::fromImage(trans_img));

}

void MainWindow::rotateImage()
{
    this->setRotation(ui->rotation_slider->value());

    IMAGEPROCESSING_H::rotateImage(&ref_img, &trans_img, (float) rotation);
    ui->img_label->setPixmap(QPixmap::fromImage(trans_img));
}

// Setters

void MainWindow::setMoveX(int newMoveX)
{
    moveX = newMoveX;
}

void MainWindow::setMoveY(int newMoveY)
{
    moveY = newMoveY;
}

void MainWindow::setRotation(int newRotation)
{
    rotation = newRotation;
}
