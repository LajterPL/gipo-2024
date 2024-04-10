#include "mainwindow.h"

#include <QMouseEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    lineModeFlag = true;
    p1 = QPoint(0, 0);
    p2 = QPoint(0, 0);
}

MainWindow::~MainWindow()
{
}

void MainWindow::drawLine() {

    if (p1.x() == p2.x()) {
        int min;
        int max;

        if (p1.y() < p2.y()) {
            min = p1.y();
            max = p2.y();
        } else {
            min = p2.y();
            max = p1.y();
        }

        for (int y = min; y <= max; y++) {
            img.setPixel(p1.x(), y, 0);
        }
    } else {

        if (p1.x() > p2.x()) {
            QPoint temp = p1;
            p1 = p2;
            p2 = temp;
        }

        int x = p1.x();
        int y = p1.y();

        int dy = p2.y() - y;
        int dx = p2.x() - x;


        if (dx > dy) {

            int d = 2*dy - dx;

            int ai = 2*dy;
            int bi = 2*(dy - dx);

            if (dy > 0) {
                for (; x != p2.x(); x++) {
                    if (d >= 0) {
                        d += bi;
                        y++;
                    } else {
                        d += ai;
                    }

                    img.setPixel(x, y, 0);
                }
            } else {

                bi = bi * -1;

                for (; x != p2.x(); x++) {
                    if (d >= 0) {
                        d += bi;
                        y--;
                    } else {
                        d += ai;
                    }

                    img.setPixel(x, y, 0);
                }
            }

        } else if (dy > dx) {

            int d = 2*dx - dy;

            int ai = 2*dx;
            int bi = 2*(dx - dy);

            int x = p1.x();
            int y = p1.y();


            for (; y != p2.y(); y++) {
                if (d >= 0) {
                    d += bi;
                    x++;
                } else {
                    d += ai;
                }

                img.setPixel(x, y, 0);
            }
        }
    }
}

void MainWindow::drawCircle() {

}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (p1.isNull()) {
            p1 = event->pos();
        } else if (p2.isNull()) {
            p2 = event->pos();

            if (lineModeFlag) {
                drawLine();
            } else {
                drawCircle();
            }

            p1.setX(0);
            p1.setY(0);

            p2.setX(0);
            p2.setY(0);

            update();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Q) {
        lineModeFlag = !lineModeFlag;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.drawImage(0, 0, img);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    img = QImage(event->size(), QImage::Format_RGB32);
    img.fill(0xFFFFFF);
}



