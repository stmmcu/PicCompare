#ifndef DEMO_H
#define DEMO_H

QImage pictureScalingDemo(const char *fileName);

uchar averageGray(uchar *grays, int size);

uchar *imageRGBToGray(QImage &image);

qulonglong perceptualHashByGray(uchar *grays, int size);

void demo();
#endif // DEMO_H
