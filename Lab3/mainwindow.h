#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "convpopup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    static MainWindow instance;

    Ui::MainWindow *ui;

    ConvPopup* conv_popup;

    QImage ref_img;
    QImage trans_img;

    int medianRadius;

    int** filter;
    int filterRadius;

public slots:
    void openImage();
    void resetImage();

    void showConvOptions();
    void saveConvOptions();

    void applyMedianFilter();
    void setMedianRadius(int newMedianRadius);
};
#endif // MAINWINDOW_H
