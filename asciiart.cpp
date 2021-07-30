#include "asciiart.h"

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
    switch(image.format())
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

QImage asciiArt::byFloydSteinburg(QImage &image)
{
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
}
