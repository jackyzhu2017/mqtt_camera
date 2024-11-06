#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>
#include <QAudioInput>
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QMediaMetaData>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QVideoSink>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMessageBox>

#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <opencv2/opencv.hpp>

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setClientPort(int p);

private slots:
    void on_buttonConnect_clicked();
    void on_buttonQuit_clicked();
    void updateLogStateChange();

    void brokerDisconnected();

    void on_buttonPublish_clicked();

    void on_buttonSubscribe_clicked();

    void updateImage();

    Mat QByteArrayToMat(const QByteArray &byteArray);

    QByteArray matToQByteArray(const Mat &mat);

    // void handleFrame(const QVideoFrame &frame);

private:
    Ui::MainWindow *ui;
    QMqttClient *m_client;

    QTimer theTimer;
    Mat srcImage;
    Mat destImage;
    VideoCapture videoCap;
    QLabel *imageLabel;

    int8_t isSubscribed = 0;
    int8_t isPublished = 0;

protected:
    void paintEvent(QPaintEvent *e);

};
#endif // MAINWINDOW_H
