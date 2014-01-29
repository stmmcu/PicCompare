#include "picturewidget.h"
#include "ui_picturewidget.h"

PictureWidget::PictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureWidget)
{
    ui->setupUi(this);
}

PictureWidget::~PictureWidget()
{
    delete ui;
}

void PictureWidget::on_pushButton_clicked()
{
    uint res;
    QString src = ui->srcFile->displayText();
    QString des = ui->desFile->displayText();
    QImage *srcImage = new QImage(src);
    QImage *desImage = new QImage(des);
    ui->srcPicture->setPixmap(QPixmap(src));
    ui->desPicture->setPixmap(QPixmap(des));
    res = cmp.compare(srcImage, desImage);
    ui->lcdNumber->display((int)res);
    if (res <= 5)
    {
        ui->label->setText("Very Similarity");
    }
    else if (res <= 15)
    {
        ui->label->setText("Similarity");
    }
    else
    {
        ui->label->setText("Not Similarity");
    }
}
