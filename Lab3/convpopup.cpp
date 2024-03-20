#include "convpopup.h"
#include "ui_convpopup.h"
#include "mainwindow.h"

ConvPopup::ConvPopup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConvPopup)
{
    ui->setupUi(this);

    connect(ui->filter_radius, SIGNAL(valueChanged(int)), this, SLOT(changeFilterSize(int)));
    connect(ui->filter_type_box, SIGNAL(currentIndexChanged(int)), this, SLOT(calculateFilter()));

}

ConvPopup::~ConvPopup()
{
    delete ui;
}

void ConvPopup::calculateFilter()
{

    int r = ui->filter_radius->value();

    switch(ui->filter_type_box->currentIndex()) {
    case 1: // Filtr Gaussa
        for (int x = 0; x < 2*r + 1; x++) {
            for (int y = 0; y < 2*r + 1; y++) {

                int row_factor = r - y;
                if (row_factor < 0) {
                    row_factor = row_factor * -1;
                }
                row_factor = r - row_factor;

                int col_factor = r - x;
                if (col_factor < 0) {
                    col_factor = col_factor * -1;
                }
                col_factor = r - col_factor;

                int value = std::pow(2, row_factor) * std::pow(2, col_factor);

                QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));
                item->setTextAlignment(Qt::AlignCenter);
                ui->filter_values->setItem(y, x, item);
            }
        }
        break;
    default:
        for (int x = 0; x < 2*r + 1; x++) {
            for (int y = 0; y < 2*r + 1; y++) {
                int value = 0;

                if (x == r && y == r) {
                    value = 1;
                }

                QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));
                item->setTextAlignment(Qt::AlignCenter);
                ui->filter_values->setItem(y, x, item);
            }
        }
    }
}

void ConvPopup::changeFilterSize(int radius)
{
    ui->filter_values->setColumnCount(2 * radius + 1);
    ui->filter_values->setRowCount(2 * radius + 1);

    calculateFilter();
}
