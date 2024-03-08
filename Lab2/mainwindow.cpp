#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageprocessing.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hue = 0;
    saturation = 0;
    lumination = 0;

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));

    connect(ui->hue_slider, SIGNAL(valueChanged(int)), this, SLOT(setHue(int)));
    connect(ui->saturation_slider, SIGNAL(valueChanged(int)), this, SLOT(setSaturation(int)));
    connect(ui->value_slider, SIGNAL(valueChanged(int)), this, SLOT(setLumination(int)));

    connect(ui->hue_slider, SIGNAL(sliderReleased()), this, SLOT(transformHSL()));
    connect(ui->saturation_slider, SIGNAL(sliderReleased()), this, SLOT(transformHSL()));
    connect(ui->value_slider, SIGNAL(sliderReleased()), this, SLOT(transformHSL()));



    connect(ui->l_slider, SIGNAL(valueChanged(int)), this, SLOT(setL(int)));
    connect(ui->a_slider, SIGNAL(valueChanged(int)), this, SLOT(setA(int)));
    connect(ui->b_slider, SIGNAL(valueChanged(int)), this, SLOT(setB(int)));
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

void MainWindow::transformHSL()
{
    changeHSL(&ref_img, &trans_img, hue, saturation, lumination);
    ui->img_label->setPixmap(QPixmap::fromImage(trans_img));
}


// Setters

void MainWindow::setB(int newB)
{
    b = newB;
}

void MainWindow::setA(int newA)
{
    a = newA;
}

void MainWindow::setL(int newL)
{
    l = newL;
}

void MainWindow::setLumination(int newLumination)
{
    lumination = newLumination;
}


void MainWindow::setSaturation(int newSaturation)
{
    saturation = newSaturation;
}

void MainWindow::setHue(int newHue)
{
    hue = newHue;
}
