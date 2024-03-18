#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "imageprocessing.h"
#include "xyz.h"
#include "lab.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hue = 0;
    saturation = 0;
    lumination = 0;

    l = 0;
    a = 0;
    b = 0;

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));

    connect(ui->hue_slider, SIGNAL(valueChanged(int)), this, SLOT(setHue(int)));
    connect(ui->saturation_slider, SIGNAL(valueChanged(int)), this, SLOT(setSaturation(int)));
    connect(ui->lumination_slider, SIGNAL(valueChanged(int)), this, SLOT(setLumination(int)));

    connect(ui->hue_slider, SIGNAL(sliderReleased()), this, SLOT(transformHSL()));
    connect(ui->saturation_slider, SIGNAL(sliderReleased()), this, SLOT(transformHSL()));
    connect(ui->lumination_slider, SIGNAL(sliderReleased()), this, SLOT(transformHSL()));

    connect(ui->l_slider, SIGNAL(valueChanged(int)), this, SLOT(setL(int)));
    connect(ui->a_slider, SIGNAL(valueChanged(int)), this, SLOT(setA(int)));
    connect(ui->b_slider, SIGNAL(valueChanged(int)), this, SLOT(setB(int)));

    connect(ui->l_slider, SIGNAL(sliderReleased()), this, SLOT(transformLAB()));
    connect(ui->a_slider, SIGNAL(sliderReleased()), this, SLOT(transformLAB()));
    connect(ui->b_slider, SIGNAL(sliderReleased()), this, SLOT(transformLAB()));

    connect(ui->reset_button, SIGNAL(clicked()), this, SLOT(resetImage()));
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

void MainWindow::transformLAB()
{
    changeLAB(&ref_img, &trans_img, l, a, b);
    ui->img_label->setPixmap(QPixmap::fromImage(trans_img));
}

// Setters

void MainWindow::setB(int newB)
{
    b = newB;
}



void MainWindow::resetImage()
{
    hue = 0;
    saturation = 0;
    lumination = 0;

    ui->hue_slider->setSliderPosition(hue);
    ui->saturation_slider->setSliderPosition(saturation);
    ui->lumination_slider->setSliderPosition(lumination);

    l = 0;
    a = 0;
    b = 0;

    ui->l_slider->setSliderPosition(l);
    ui->a_slider->setSliderPosition(a);
    ui->b_slider->setSliderPosition(b);

    ui->img_label->setPixmap(QPixmap::fromImage(ref_img));
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
