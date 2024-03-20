#ifndef CONVPOPUP_H
#define CONVPOPUP_H

#include <QWidget>

namespace Ui {
class ConvPopup;
}

class ConvPopup : public QWidget
{
    Q_OBJECT

public:
    explicit ConvPopup(QWidget *parent = nullptr);
    ~ConvPopup();
    Ui::ConvPopup *ui;

public slots:
    void calculateFilter();
    void changeFilterSize(int);

};

#endif // CONVPOPUP_H
