#ifndef PERCEPTUALHASHALGORITHM_H
#define PERCEPTUALHASHALGORITHM_H

#include <QImage>

//1.浮点算法：Gray=R*0.3+G*0.59+B*0.11

//2.整数方法：Gray=(R*30+G*59++B*11)/100

//3.移位方法：Gray =(R*28+G*151+B*77)>>8;

//4.平均值法：Gray=（R+G+B）/3;

//5.仅取绿色：Gray=G；
struct picture
{
    QImage *srcImage;
    QImage *cmpImage;
    uchar grays[64];
    qulonglong hash;
};

typedef struct picture Picture;

class PerceptualHashAlgorithm
{
public:
    enum RGBToGrayMode{
        RGBToGrayMode_FLOAT,
        RGBToGrayMode_INT,
        RGBToGrayMode_SHIFT,
        RGBToGrayMode_AVG,
        RGBToGrayMode_ONLYG
    };
    PerceptualHashAlgorithm();
  //  PerceptualHashAlgorithm(QImage *src = NULL, QImage *des = NULL, RGBToGrayMode mode);
    void setSrcPicture(QImage *image);
    void setDesPicture(QImage *image);
    void setRGBToGrayMode(RGBToGrayMode mode);
    QImage *getSrcPicture();
    QImage *getDesPicture();
    QImage *getSrcCmpPicture();
    QImage *getDesCmpPicture();
    RGBToGrayMode getRGBToGrayMode();
    uint compare();
    uint compare(QImage *src, QImage *des);
    void pictureScaling();
    ~PerceptualHashAlgorithm();
private:
    void pictureScaling(Picture &picture);
    void imageRGBToGray(Picture &picture);
    uchar averageGray(Picture &picture);
    void perceptualHashByGray(Picture &picture);
    RGBToGrayMode rgbtograymode;
    Picture srcPicture;
    Picture desPicture;
    uint  hammingDistance;
};

#endif // PERCEPTUALHASHALGORITHM_H
