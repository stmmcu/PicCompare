#include "perceptualhashalgorithm.h"

PerceptualHashAlgorithm::PerceptualHashAlgorithm()
{
    rgbtograymode = RGBToGrayMode_FLOAT;
    srcPicture.srcImage = NULL;
    srcPicture.cmpImage = NULL;
    desPicture.srcImage = NULL;
    desPicture.cmpImage = NULL;
}

//PerceptualHashAlgorithm::PerceptualHashAlgorithm(QImage *src = NULL, QImage *des = NULL, RGBToGrayMode mode)
//{

//    setSrcPicture(src);
//    setDesPicture(des);

//    rgbtograymode = mode;
//}

void PerceptualHashAlgorithm::setRGBToGrayMode(RGBToGrayMode mode)
{
    rgbtograymode = mode;
}

PerceptualHashAlgorithm::RGBToGrayMode PerceptualHashAlgorithm::getRGBToGrayMode()
{
    return rgbtograymode;
}

void PerceptualHashAlgorithm::setSrcPicture(QImage *image)
{
    if (srcPicture.srcImage)
    {
        delete srcPicture.srcImage;

        if (srcPicture.cmpImage)
        {
            delete srcPicture.cmpImage;
            srcPicture.cmpImage = NULL;
        }
    }

    srcPicture.srcImage = image;
    srcPicture.hash = 0;
}

void PerceptualHashAlgorithm::setDesPicture(QImage *image)
{
    if (desPicture.srcImage)
    {
        delete desPicture.srcImage;

        if (desPicture.cmpImage)
        {
            delete desPicture.cmpImage;
            desPicture.cmpImage = NULL;
        }
    }

    desPicture.srcImage = image;
    desPicture.hash = 0;
}

QImage *PerceptualHashAlgorithm::getSrcPicture()
{
    return srcPicture.srcImage;
}

QImage *PerceptualHashAlgorithm::getDesPicture()
{
    return desPicture.srcImage;
}

QImage *PerceptualHashAlgorithm::getSrcCmpPicture()
{
    return srcPicture.cmpImage;
}

QImage *PerceptualHashAlgorithm::getDesCmpPicture()
{
    return desPicture.cmpImage;
}

void PerceptualHashAlgorithm::pictureScaling(Picture &picture)
{
    if (picture.srcImage)
        picture.cmpImage = new QImage(picture.srcImage->scaled(8,8,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void PerceptualHashAlgorithm::imageRGBToGray(Picture &picture)
{

    uchar b;
    uchar g;
    uchar r;

    if (!picture.cmpImage)
    {
        return;
    }

    uchar *bits = picture.cmpImage->bits();

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            b = bits[i * 8 * 4 + j * 4 + j];
            g = bits[i * 8 * 4 + j * 4 + j + 1];
            r = bits[i * 8 * 4 + j * 4 + j + 2];

            if (rgbtograymode == RGBToGrayMode_FLOAT)
            {
                picture.grays[i * 8 + j] = (uchar)(r*0.3+g*0.59+b*0.11);
            }
            else if (rgbtograymode == RGBToGrayMode_INT)
            {
                picture.grays[i * 8 + j] = (r*30 + g*59 + b * 11) / 100;
            }
            else if (rgbtograymode == RGBToGrayMode_SHIFT)
            {
                picture.grays[i * 8 + j] = (r*28 + g*151 + b * 77) >> 8;
            }
            else if (rgbtograymode == RGBToGrayMode_AVG)
            {
                picture.grays[i * 8 + j] = (r + g + b) / 3;
            }
            else if (rgbtograymode == RGBToGrayMode_ONLYG)
            {
                picture.grays[i * 8 + j] = g;
            }
        }
    }
}

uchar PerceptualHashAlgorithm::averageGray(Picture &picture)
{
    uint sum = 0;

    for (int i = 0; i < 64; ++i)
    {
        sum += picture.grays[i];
    }

    return sum >> 6;
}

void PerceptualHashAlgorithm::perceptualHashByGray(Picture &picture)
{
    qulonglong bit = 0;
    uchar avg = averageGray(picture);

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            bit = (picture.grays[i * 8 + j] >= avg);
            picture.hash = picture.hash | (bit << (i * 8 + j));
        }
    }
}

uint PerceptualHashAlgorithm::compare()
{
    qlonglong hash;

    if (!srcPicture.cmpImage)
    {
        pictureScaling(srcPicture);
        imageRGBToGray(srcPicture);
        perceptualHashByGray(srcPicture);
    }

    if (!desPicture.cmpImage)
    {
        pictureScaling(desPicture);
        imageRGBToGray(desPicture);
        perceptualHashByGray(desPicture);
    }

    hash = srcPicture.hash ^ desPicture.hash;

    for (hammingDistance =0; hash; ++hammingDistance)
    {
        hash &= (hash -1) ;
    }

    return hammingDistance;
}

uint PerceptualHashAlgorithm::compare(QImage *src, QImage *des)
{
    setSrcPicture(src);
    setDesPicture(des);
    return compare();
}

PerceptualHashAlgorithm::~PerceptualHashAlgorithm()
{
    if (srcPicture.srcImage)
    {
        delete srcPicture.srcImage;
        srcPicture.srcImage = NULL;

        if (srcPicture.cmpImage)
        {
            delete srcPicture.cmpImage;
            srcPicture.cmpImage = NULL;
        }
    }

    if (desPicture.srcImage)
    {
        delete desPicture.srcImage;
        desPicture.srcImage = NULL;

        if (desPicture.cmpImage)
        {
            delete desPicture.cmpImage;
            desPicture.cmpImage = NULL;
        }
    }
}
