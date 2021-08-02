#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_load_clicked(bool checked);

    void on_pushButton_g_clicked(bool checked);

    void on_pushButton_dbg_clicked(bool checked);

    void on_pushButton_clicked(bool checked);

private:
    static void showImgOnQLabel(const QImage &image, QLabel *label);
    Ui::MainWindow *ui;
    QImage m_image;
    QImage m_grayImage;
};

#endif // MAINWINDOW_H
