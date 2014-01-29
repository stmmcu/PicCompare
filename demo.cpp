//#include <QImage>
//#include <QRgb>
//#include <demo.h>
#include <QDebug>

#include "perceptualhashalgorithm.h"

//QImage pictureScalingDemo(const char *fileName)
//{
//    QImage image(fileName);

//    QImage scalingImage = image.scaled(8,8,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//    scalingImage.save("./1scling.jpg");

//    return scalingImage;
//}
////1.浮点算法：Gray=R*0.3+G*0.59+B*0.11

////2.整数方法：Gray=(R*30+G*59++B*11)/100

////3.移位方法：Gray =(R*28+G*151+B*77)>>8;

////4.平均值法：Gray=（R+G+B）/3;

////5.仅取绿色：Gray=G；

//uchar *imageRGBToGray(QImage &image)
//{
//    uchar *bits = image.bits();
//    int h = image.height();
//    int w = image.width();
//    uchar b;
//    uchar g;
//    uchar r;
//    uchar *grays = (uchar *)malloc(64);

//    for (int i = 0; i < h; ++i)
//    {
//        for (int j = 0; j < w; ++j)
//        {
//            b = bits[i * w * 4 + j * 4 + j];
//            g = bits[i * w * 4 + j * 4 + j + 1];
//            r = bits[i * w * 4 + j * 4 + j + 2];
//            grays[i * w + j] = (r*28 + g*151 + b * 77) >> 8;
//            //grays[i * w + j] = (uchar)(r*0.3+g*0.59+b*0.11);
//        }
//    }

//    return grays;
//}
//uchar averageGray(uchar *grays, int size)
//{
//    int sum = 0;
//    for (int i = 0; i < size; ++i)
//    {
//        sum += grays[i];
//    }

//    return sum / size;
//}
//qulonglong perceptualHashByGray(uchar *grays, int size)
//{
//    qulonglong hash = 0;
//    qulonglong bit = 0;
//    uchar avg = averageGray(grays, 64);
//    size = size;
//    for (int i = 0; i < 8; ++i)
//    {
//        for (int j = 0; j < 8; ++j)
//        {
//            bit = (grays[i * 8 + j] >= avg);
//            hash = hash | (bit << (i * 8 + j));
//        }
//    }
//    return hash;
//}

void demo()
{
//    int c = 0;
//    qulonglong hash1 = 0;
//    qulonglong hash2 = 0;
//    QImage image = pictureScalingDemo("./image/1.jpg");
//    uchar *grays = imageRGBToGray(image);
//    hash1 = perceptualHashByGray(grays, 64);
//    qDebug() << hash1;
//    free(grays);

//    image = pictureScalingDemo("./image/1.jpg");
//    grays = imageRGBToGray(image);
//    hash2 = perceptualHashByGray(grays, 64);
//    qDebug() << hash2;
//    free(grays);

//    hash1 = hash1 ^ hash2;
//    for (c =0; hash1; ++c)
//    {
//        hash1 &= (hash1 -1) ; // 清除最低位的1
//    }
//    qDebug() << c;
    PerceptualHashAlgorithm t;
    QImage *image1 = new QImage("./image/1.jpg");
    QImage *image2 = new QImage("./image/1.jpg");

    t.setSrcPicture(image1);
    t.setDesPicture(image2);
    qDebug() << t.compare();
}
