#ifndef ASCIIART_H
#define ASCIIART_H

#include <QImage>

class asciiArt
{
public:
    asciiArt() = delete;
    //根据公式(r*11+g*16+b*5)/32转灰度图像
    static QImage toGray(const QImage& image );
    //随机阈值法转离散二值图像
    static QImage toDiscreteBinaryValue(QImage &image);
    QImage byFloydSteinburg(QImage& image);
};

#endif // ASCIIART_H
