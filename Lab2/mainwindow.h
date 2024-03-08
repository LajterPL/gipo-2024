#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

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
    Ui::MainWindow *ui;
    QImage ref_img;
    QImage trans_img;

    int hue;
    int saturation;
    int lumination;

    int l;
    int a;
    int b;

public slots:
    void openImage();

    void setHue(int);
    void setSaturation(int);
    void setLumination(int);
    void transformHSL();

    void setL(int);
    void setA(int);
    void setB(int);

};
#endif // MAINWINDOW_H
