#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include "asciiart.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showImgOnQLabel(const QImage& image, QLabel* label)
{
    QPixmap pixMap = QPixmap::fromImage(image);
    //pixMap = pixMap.scaled(label->size(), Qt::KeepAspectRatioByExpanding);
    label->setPixmap(pixMap);
}

void MainWindow::on_pushButton_load_clicked(bool checked)
{
    Q_UNUSED(checked);
    QString fileName = QFileDialog::getOpenFileName(this, "", "./");
    QImage image(fileName);
    qDebug() << image.format();
    showImgOnQLabel(image, ui->label_2);

    m_image = image;
}

void MainWindow::on_pushButton_g_clicked(bool checked)
{
    Q_UNUSED(checked);
    QImage grayImg = asciiArt::toGray(m_image);
    showImgOnQLabel(grayImg, ui->label);
    m_grayImage = grayImg;
}

void MainWindow::on_pushButton_dbg_clicked(bool checked)
{
    Q_UNUSED(checked);
#if 1
    QImage binValue_img = m_grayImage.scaled( 2 * m_grayImage.size());
    binValue_img = asciiArt::toDiscreteBinaryValue(binValue_img);
#else
    QImage binValue_img = asciiArt::toDiscreteBinaryValue(m_grayImage);
#endif
    showImgOnQLabel(binValue_img, ui->label);
    QString saveFile = QFileDialog::getSaveFileName(this);
    binValue_img.save(saveFile);
}
