#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QQueue>
#include <QTimer>
#include "qcgaugewidget.h"
#include "uavairqualityprotocol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_UpdateArcTimer();
    void onReadTimerTimeOut();
    void onSerializeTimerTimeout();

private:
    Ui::MainWindow *ui;
    QTimer* arcUpdateTimer;
    QcGaugeWidget *SO2_Gauge,*NO2_Gauge,*CO_Gauage,*CO2_Gauage;
    QcNeedleItem *SO2_Needle,*NO2_Needle,*CO_Needle,*CO2_Needle;
    QSerialPort *pPort;
    QQueue<char> mDataQueue;
    QQueue<Event_t> mEventQueue;
    UAVairQualityProtocol mprotocol;
    QTimer *pReadTimer,*pSerializeTimer;
};
#endif // MAINWINDOW_H
