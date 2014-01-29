#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>

#include "perceptualhashalgorithm.h"

namespace Ui {
class PictureWidget;
}

class PictureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PictureWidget(QWidget *parent = 0);
    ~PictureWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PictureWidget *ui;
    PerceptualHashAlgorithm cmp;
};

#endif // PICTUREWIDGET_H
