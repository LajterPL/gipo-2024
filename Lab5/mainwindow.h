#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPoint>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage img;

    QPoint p1;
    QPoint p2;

    bool lineModeFlag;

    void drawLine();
    void drawCircle();

protected:
    void mousePressEvent(QMouseEvent*);
    //void mouseMoveEvent(QMouseEvent*);
    //void mouseReleaseEvent(QMouseEvent*);
    //void mouseDoubleClickEvent(QMouseEvent*);

    //void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
};
#endif // MAINWINDOW_H
