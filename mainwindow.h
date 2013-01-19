#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include "itunescontroller.h"

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
    void readDatagrams();
    void on_actionClear_triggered();
    void on_actionMinimize_triggered();
    void on_actionPreferences_triggered();

    void on_lineEditCommand_returnPressed();

private:
    Ui::MainWindow *ui;
    iTunesController m_controller;
    QUdpSocket m_socket;
};

#endif // MAINWINDOW_H
