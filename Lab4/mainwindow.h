#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setMoveX(int newMoveX);

    void setMoveY(int newMoveY);

    void setRotation(int newRotation);

    void setScale(float newScale);

private:
    Ui::MainWindow *ui;

    QImage ref_img;
    QImage trans_img;

    int moveX;
    int moveY;

    int rotation;

    float scale;

public slots:
    void openImage();
    void resetImage();

    void moveImage();
    void rotateImage();
    void scaleImage();
};
#endif // MAINWINDOW_H
