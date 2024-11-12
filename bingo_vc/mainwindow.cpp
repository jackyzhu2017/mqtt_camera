// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>

#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace Qt::StringLiterals;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_client = new QMqttClient(this);
    m_client->setHostname(ui->lineEditHost->text());
    m_client->setPort((ui->lineEditPort->text()).toShort());

    m_client->setUsername("test");
    m_client->setPassword("test");

    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
        + " Received Topic: "_L1
            + topic.name()
            + " Message: "_L1
            //+ message
            + u'\n';
        //ui->editLog->insertPlainText(content);

        destImage = QByteArrayToMat(message);

        // circle(destImage, Point(destImage.cols / 2, destImage.rows / 2), 50, Scalar(0, 255, 0), 3);

        this->update();	//发送刷新消息
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
        + "PingResponse\n"_L1;
        ui->editLog->insertPlainText(content);
    });

    connect(ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    //connect(ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);
    updateLogStateChange();

    isSubscribed = 0;
    isPublished = 0;

    connect(&theTimer, &QTimer::timeout, this, &MainWindow::updateImage);
    //从摄像头捕获视频
    if(videoCap.open(0))
    {
        srcImage = Mat::zeros(videoCap.get(CAP_PROP_FRAME_HEIGHT), videoCap.get(CAP_PROP_FRAME_WIDTH), CV_8UC3);
        theTimer.start(33);
    }
    //设置显示视频用的Label
    imageLabel = new QLabel(this);
    ui->verticalLayout->addWidget(imageLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateImage()
{
    if (isSubscribed == 1 && isPublished == 1){
        videoCap>>srcImage;

        if(srcImage.data)
        {
            cvtColor(srcImage, srcImage, COLOR_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
            QByteArray byteArray = matToQByteArray(srcImage);

            if (m_client->publish(ui->lineEditTopic->text(), byteArray) == -1)
                QMessageBox::critical(this, u"Error"_s, u"Could not publish message"_s);
        }
    }
}

Mat MainWindow::QByteArrayToMat(const QByteArray &byteArray) {
    vector<uchar> buf(byteArray.begin(), byteArray.end());
    Mat mat = imdecode(buf, cv::IMREAD_COLOR); // 解码为 OpenCV 图像
    return mat;
}

QByteArray MainWindow::matToQByteArray(const Mat &mat) {
    vector<uchar> buf;
    imencode(".jpg", mat, buf); // 将图像编码为 JPEG 格式
    QByteArray byteArray(reinterpret_cast<const char*>(buf.data()), buf.size());
    return byteArray;
}


void MainWindow::paintEvent(QPaintEvent *e)
{
    //显示方法一
    // QPainter painter(this);
    // QImage image1 = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
    // painter.drawImage(QPoint(20,20), image1);
    //显示方法二
    // QImage image2 = QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);

    QImage image2 = QImage((uchar*)(destImage.data), destImage.cols, destImage.rows, QImage::Format_RGB888);
    imageLabel->setPixmap(QPixmap::fromImage(image2));
    imageLabel->resize(image2.size());
    imageLabel->show();
}


void MainWindow::on_buttonConnect_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->lineEditHost->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        ui->buttonConnect->setText(tr("Disconnect"));
        m_client->connectToHost();
    } else {
        ui->lineEditHost->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
        ui->buttonConnect->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }
}

void MainWindow::on_buttonQuit_clicked()
{
    QApplication::quit();
}

void MainWindow::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
    + ": State Change"_L1
        + QString::number(m_client->state())
        + u'\n';
    ui->editLog->insertPlainText(content);
}

void MainWindow::brokerDisconnected()
{
    ui->lineEditHost->setEnabled(true);
    ui->lineEditPort->setEnabled(true);
    ui->buttonConnect->setText(tr("Connect"));
}

void MainWindow::setClientPort(int p)
{
    m_client->setPort(static_cast<quint16>(p));
}

void MainWindow::on_buttonPublish_clicked()
{
    if (m_client->publish(ui->lineEditTopic->text(), ui->lineEditMessage->text().toUtf8()) == -1)
        QMessageBox::critical(this, u"Error"_s, u"Could not publish message"_s);

    isPublished = 1;

}

void MainWindow::on_buttonSubscribe_clicked()
{
    auto subscription = m_client->subscribe(ui->lineEditTopic->text());
    if (!subscription) {
        QMessageBox::critical(this, u"Error"_s,
                              u"Could not subscribe. Is there a valid connection?"_s);
        return;
    }

    isSubscribed = 1;

}
