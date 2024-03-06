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


public slots:
    void openImage();
    void changeBrightness(int);
    void changeContrast(int);
    void changeGamma(int);

    void showHistR();
    void showHistG();
    void showHistB();
    void showHistL();
    void showHistogram(int);
};
#endif // MAINWINDOW_H
