#ifndef ASCIIART_H
#define ASCIIART_H

#include <QImage>

class asciiArt
{
public:
    asciiArt() = delete;
    //���ݹ�ʽ(r*11+g*16+b*5)/32ת�Ҷ�ͼ��
    static QImage toGray(const QImage& image );
    //�����ֵ��ת��ɢ��ֵͼ��
    static QImage toDiscreteBinaryValue(QImage &image);
    QImage byFloydSteinburg(QImage& image);
};

#endif // ASCIIART_H
