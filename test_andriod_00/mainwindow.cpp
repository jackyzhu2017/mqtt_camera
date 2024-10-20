#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QActionGroup>
#include <QImage>
#include <QKeyEvent>
#include <QPalette>

#include <QDir>
#include <QTimer>
#include <QPainter>

#if QT_CONFIG(permissions)
#include <QPermission>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // ui->verticalLayout->addWidget(&ui->viewfinder);
    imageLabel = new QLabel(this);
    ui->verticalLayout->addWidget(imageLabel);
    // try to actually initialize camera & mic
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
#if QT_CONFIG(permissions)
    // camera
    QCameraPermission cameraPermission;
    switch (qApp->checkPermission(cameraPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cameraPermission, this, &MainWindow::init);
        return;
    case Qt::PermissionStatus::Denied:
        qWarning("Camera permission is not granted!");
        return;
    case Qt::PermissionStatus::Granted:
        break;
    }
    // microphone
    QMicrophonePermission microphonePermission;
    switch (qApp->checkPermission(microphonePermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(microphonePermission, this, &MainWindow::init);
        return;
    case Qt::PermissionStatus::Denied:
        qWarning("Microphone permission is not granted!");
        return;
    case Qt::PermissionStatus::Granted:
        break;
    }
#endif

    m_audioInput.reset(new QAudioInput);
    m_captureSession.setAudioInput(m_audioInput.get());

    // Camera devices:

    videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    updateCameras();
    connect(&m_devices, &QMediaDevices::videoInputsChanged, this, &MainWindow::updateCameras);

    connect(videoDevicesGroup, &QActionGroup::triggered, this, &MainWindow::updateCameraDevice);

    setCamera(QMediaDevices::defaultVideoInput());

}

void MainWindow::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraDevice>(action->data()));
}


void MainWindow::updateCameras()
{
    ui->menuDevice->clear();
    const QList<QCameraDevice> availableCameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraDevice.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraDevice));
        if (cameraDevice == QMediaDevices::defaultVideoInput())
            videoDeviceAction->setChecked(true);

        ui->menuDevice->addAction(videoDeviceAction);
    }
}

void MainWindow::setCamera(const QCameraDevice &cameraDevice)
{
    m_camera.reset(new QCamera(cameraDevice));
    m_captureSession.setCamera(m_camera.data());

    //connect(m_camera.data(), &QCamera::activeChanged, this, &MainWindow::updateCameraActive);
    //connect(m_camera.data(), &QCamera::errorOccurred, this, &MainWindow::displayCameraError);



   // m_captureSession.setVideoOutput(ui->viewfinder);
    m_captureSession.setVideoSink(&videoSink);

    connect(&videoSink, &QVideoSink::videoFrameChanged, this, &MainWindow::onVideoFrameChanged);

    // updateCameraActive(m_camera->isActive());


    m_camera->start();
}


void MainWindow::onVideoFrameChanged(const QVideoFrame &frame) {
    currentFrame = frame;
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)  {
   // QPainter painter(this);
    if (!currentFrame.isValid()) return;

    QImage image = currentFrame.toImage();
   // painter.drawImage(ui->viewfinder->geometry().topLeft(), image);

    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.size());
    imageLabel->show();
   //painter.drawImage(0, 0, image);

    // 在每一帧上绘制一个圆圈
   // painter.setPen(Qt::red);
   // painter.drawEllipse(ui->viewfinder->rect().center(), 50, 50);
}
