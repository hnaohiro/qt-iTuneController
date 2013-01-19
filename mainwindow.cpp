#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include "preferencesdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
    if (!m_socket.bind(7777,  QUdpSocket::ShareAddress)) {
        QMessageBox::critical(this, NULL, "failed to bind");
    }
    m_socket.joinMulticastGroup(QHostAddress("224.0.0.1"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readDatagrams()
{
    while (m_socket.hasPendingDatagrams()) {
        QByteArray data;
        QHostAddress address;
        quint16 port;
        data.resize(m_socket.pendingDatagramSize());
        m_socket.readDatagram(data.data(), data.size(), &address, &port);

        QStringList commands = QString(data).split(":");
        if (commands.length() != 2) {
            continue;
        }

        QString tokenID = commands.at(0);
        if (tokenID != QSettings().value("tokenID").toString()) {
            qDebug() << "invalid token ID";
            continue;
        } else {
            QString time = QDateTime::currentDateTime().toString("MM/dd hh:mm:ss");
            QString info(time + " : From %2 : [%3]");
            ui->plainTextEdit->appendPlainText(info.arg(address.toString()).arg(commands.at(1)));
        }

        if (commands.at(1) == "prev") {
            m_controller.back();
        } else if (commands.at(1) == "play") {
            m_controller.play();
        } else if (commands.at(1) == "pause") {
            m_controller.pause();
        }  else if (commands.at(1) == "stop") {
            m_controller.stop();
        } else if (commands.at(1) == "next") {
            m_controller.next();
        } else if (commands.at(1).startsWith("volume")) {
            int volume = QString(commands.at(1)).remove("volume").toInt();
            m_controller.setVolume(volume);
        }
    }
}

void MainWindow::on_actionClear_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_actionMinimize_triggered()
{
    showMinimized();
}

void MainWindow::on_actionPreferences_triggered()
{
    PreferencesDialog dialog;
    dialog.exec();
}

void MainWindow::on_lineEditCommand_returnPressed()
{
    this->m_controller.runScript(ui->lineEditCommand->text());
}
