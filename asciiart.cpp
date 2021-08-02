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
    int bytePerLine = image.bytesPerLine();    // ÿһ�е��ֽ���
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
���磬
�Ҷ���ĻҶ�ֵΪg�����ֵΪe��
����ÿ������ֵ���Ҷ��������m��127���������ػҶ�ƽ��ֵ������ϲ��������ôpixels��i��=#ffffffff����ף�e=g-255��
���򣬴�ڣ�pixels��i��=#ff000000��e=g��Ȼ��������ص���ұߣ��±ߣ������·������ص㣬��Ӧ�ļ���3e/8,3e/8,e/4��
*/
QImage asciiArt::byFloydSteinburg(QImage image)
{
    const int width = image.width();
    const int height = image.height();
    const int bytePerLine = image.bytesPerLine();    // ÿһ�е��ֽ���
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
            //���ж�ֵ��
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
            // ��������
            if(j < width-1) // ������ĩ
            {
                //�ұ�
                *(data + i*bytePerLine + j+1) += (3*e/8);
            }
            if(i < height-1) // ���ǵײ�
            {
                //�±�
                *(data + (i+1)*bytePerLine + j) += (3*e/8);
            }
            if(j < width-1 && i < height-1)
            {
                //����
                *(data + (i+1)*bytePerLine + j+1) += (e/4);
            }
        }
    }
    QImage ret(binarydata, width, height, bytePerLine, QImage::Format_Grayscale8);
    return ret;
}
