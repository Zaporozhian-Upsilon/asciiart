#include "asciiart.h"
#include <QDebug>

QImage asciiArt::toGray(const QImage &image)
{
    int height = image.height();
    int width = image.width();
    QImage ret(width, height, QImage::Format_Indexed8);
    ret.setColorCount(256);
    for(int i = 0; i < 256; i++)
    {
        ret.setColor(i, qRgb(i, i, i));
    }
    switch((int)image.format())
    {
    case QImage::Format_Indexed8:
        for(int i = 0; i < height; i ++)
        {
            const uchar *pSrc = (uchar *)image.constScanLine(i);
            uchar *pDest = (uchar *)ret.scanLine(i);
            memcpy(pDest, pSrc, width);
        }
        break;
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
        for(int i = 0; i < height; i ++)
        {
            const QRgb *pSrc = (QRgb *)image.constScanLine(i);
            uchar *pDest = (uchar *)ret.scanLine(i);

            for( int j = 0; j < width; j ++)
            {
                pDest[j] = qGray(pSrc[j]);
            }
        }
        break;
    }
    return ret;
}

QImage asciiArt::toDiscreteBinaryValue(QImage &image)
{
    qDebug() << "Gray Image Format is:" << image.format();
    int width = image.width();
    int height = image.height();
    int bytePerLine = image.bytesPerLine();    // 每一行的字节数
    unsigned char *data = image.bits();
    unsigned char *binarydata = new unsigned char[bytePerLine * height];

    unsigned char g = 0;
    for (int i = 0; i < height; ++i) // row
    {
        for (int j = 0; j < width; ++j) // column
        {
            //each pixel
            g = *(data + i * bytePerLine + j);
            if(int(g) >= qrand() % (0xFF+1) )
            {
                binarydata[ i * bytePerLine + j] = 0xFF;
            }
            else
            {
                binarydata[ i * bytePerLine + j] = 0x00;
            }
        }
    }
    QImage ret(binarydata, width, height, bytePerLine, QImage::Format_Grayscale8);
    return ret;
}
/*
例如，
灰度如的灰度值为g，误差值为e。
遍历每个像素值，灰度如果大于m（127，或者像素灰度平均值，看你喜欢），那么pixels【i】=#ffffffff，打白，e=g-255；
否则，打黑，pixels【i】=#ff000000，e=g；然后，这个像素点的右边，下边，和右下方的像素点，对应的加上3e/8,3e/8,e/4。
*/
QImage asciiArt::byFloydSteinburg(QImage image)
{
    const int width = image.width();
    const int height = image.height();
    const int bytePerLine = image.bytesPerLine();    // 每一行的字节数
    unsigned char *data = image.bits();
    unsigned char *binarydata = new unsigned char[bytePerLine * height];

    unsigned char g = 0;
    // Umm........
    int e = 0;
    for (int i = 0; i < height; ++i) // row
    {
        for (int j = 0; j < width; ++j) // column
        {
            //each pixel
            g = *(data + i * bytePerLine + j);
            //进行二值化
            if(int(g) > 127)
            {
                e = (int)g - 255;
                binarydata[i*bytePerLine+j] = 0xFF;
            }
            else
            {
                e = g;
                binarydata[i*bytePerLine+j] = 0x00;
            }
            // 抖动部分
            if(j < width-1) // 不是行末
            {
                //右边
                *(data + i*bytePerLine + j+1) += (3*e/8);
            }
            if(i < height-1) // 不是底部
            {
                //下边
                *(data + (i+1)*bytePerLine + j) += (3*e/8);
            }
            if(j < width-1 && i < height-1)
            {
                //右下
                *(data + (i+1)*bytePerLine + j+1) += (e/4);
            }
        }
    }
    QImage ret(binarydata, width, height, bytePerLine, QImage::Format_Grayscale8);
    return ret;
}
