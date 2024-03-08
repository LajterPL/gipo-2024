#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage ref_img;
    QImage trans_img;
    int brightness;
    int contrast;
    int gamma;


public slots:
    void openImage();

    void setBrightness(int);
    void setContrast(int);
    void setGamma(int);
    void transformImage();
    void resetTransform();

    void showHistR();
    void showHistG();
    void showHistB();
    void showHistL();
    void showHistogram(int);
};
#endif // MAINWINDOW_H
