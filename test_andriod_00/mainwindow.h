#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudioInput>
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QMediaMetaData>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QMainWindow>
#include <QVideoSink>
#include <QPainter>
#include <QVideoWidget>
#include <Qlabel>

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

private slots:
    void init();

    void setCamera(const QCameraDevice &cameraDevice);
    void updateCameras();
    void updateCameraDevice(QAction *action);
    void onVideoFrameChanged(const QVideoFrame &frame);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    QActionGroup *videoDevicesGroup = nullptr;

    QMediaDevices m_devices;
    QScopedPointer<QImageCapture> m_imageCapture;
    QMediaCaptureSession m_captureSession;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;
    QVideoSink videoSink;
    QVideoFrame currentFrame;
    QVideoWidget videoWidget;
    QLabel *imageLabel;

};
#endif // MAINWINDOW_H
