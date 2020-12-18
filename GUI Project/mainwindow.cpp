#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arcUpdateTimer=new QTimer(this);

    connect(arcUpdateTimer,SIGNAL(timeout()),this,SLOT(on_UpdateArcTimer()));

    SO2_Gauge = new QcGaugeWidget;
    SO2_Gauge->addArc(55);
    SO2_Gauge->addDegrees(65)->setValueRange(0,100);
    QcColorBand *clrBand = SO2_Gauge->addColorBand(50);
    clrBand->setValueRange(0,100);
    SO2_Gauge->addValues(80)->setValueRange(0,100);
    QcLabelItem *lab = SO2_Gauge->addLabel(40);
    lab->setText("0");
    SO2_Needle = SO2_Gauge->addNeedle(60);
    SO2_Needle->setLabel(lab);
    SO2_Needle->setColor(Qt::blue);
    SO2_Needle->setValueRange(0,100);
    SO2_Gauge->addBackground(7);
    ui->SO2_Layout->addWidget(SO2_Gauge);


    NO2_Gauge = new QcGaugeWidget;
    NO2_Gauge->addArc(55);
    NO2_Gauge->addDegrees(65)->setValueRange(0,100);
    QcColorBand *clrBand1 = NO2_Gauge->addColorBand(50);
    clrBand1->setValueRange(0,100);
    NO2_Gauge->addValues(80)->setValueRange(0,100);
    QcLabelItem *lab1 = NO2_Gauge->addLabel(40);
    lab1->setText("0");
    NO2_Needle = NO2_Gauge->addNeedle(60);
    NO2_Needle->setLabel(lab1);
    NO2_Needle->setColor(Qt::blue);
    NO2_Needle->setValueRange(0,100);
    NO2_Gauge->addBackground(7);
    ui->NO2_Layout->addWidget(NO2_Gauge);



    CO_Gauage = new QcGaugeWidget;
    CO_Gauage->addArc(55);
    CO_Gauage->addDegrees(65)->setValueRange(0,100);
    QcColorBand *clrBand2 = CO_Gauage->addColorBand(50);
    clrBand2->setValueRange(0,100);
    CO_Gauage->addValues(80)->setValueRange(0,100);
    QcLabelItem *lab2 = CO_Gauage->addLabel(40);
    lab2->setText("0");
    CO_Needle = CO_Gauage->addNeedle(60);
    CO_Needle->setLabel(lab2);
    CO_Needle->setColor(Qt::blue);
    CO_Needle->setValueRange(0,100);
    CO_Gauage->addBackground(7);
    ui->CO_Layout->addWidget(CO_Gauage);

    CO2_Gauage = new QcGaugeWidget;
    CO2_Gauage->addArc(55);
    CO2_Gauage->addDegrees(65)->setValueRange(0,100);
    QcColorBand *clrBand3 = CO2_Gauage->addColorBand(50);
    clrBand3->setValueRange(0,100);
    CO2_Gauage->addValues(80)->setValueRange(0,100);
    QcLabelItem *lab3 = CO2_Gauage->addLabel(40);
    lab3->setText("0");
    CO2_Needle = CO2_Gauage->addNeedle(60);
    CO2_Needle->setLabel(lab3);
    CO2_Needle->setColor(Qt::blue);
    CO2_Needle->setValueRange(0,100);
    CO2_Gauage->addBackground(7);
    ui->CO2_Layout->addWidget(CO2_Gauage);

    pReadTimer=new QTimer(this);
    pSerializeTimer= new QTimer(this);

    pPort=new QSerialPort(this);
    pPort->setBaudRate(115200);
    pPort->setFlowControl(QSerialPort::NoFlowControl);
    pPort->setParity(QSerialPort::NoParity);
    pPort->setPortName("COM4");
    pPort->setStopBits(QSerialPort::OneStop);
    pPort->setDataBits(QSerialPort::Data8);
    pPort->open(QIODevice::ReadWrite);

    connect(pReadTimer,SIGNAL(timeout()),this,SLOT(onReadTimerTimeOut()));
    connect(pSerializeTimer,SIGNAL(timeout()),this,SLOT(onSerializeTimerTimeout()));
    pReadTimer->start(20);
    pSerializeTimer->start(20);
    arcUpdateTimer->start(100);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_UpdateArcTimer()
{
    if(mEventQueue.size()>0)
    {
        Event_t temp=mEventQueue.front();
        mEventQueue.pop_front();
        this->SO2_Needle->setCurrentValue(temp.SO2/40);
        this->NO2_Needle->setCurrentValue(temp.NO2/40);
        this->CO_Needle->setCurrentValue(temp.CO/40);
        this->CO2_Needle->setCurrentValue(temp.CO2/40);
    }

}
void MainWindow::onReadTimerTimeOut()
{
    static char c[2];
    while(1)
    {

            // Read a character until Serial Port has data
            if(pPort->read(c,1)>0)
            {
                // append it to Data  queue
                mDataQueue.append(c[0]);
            }
            else
            {
                break;
            }
    }
}

void MainWindow::onSerializeTimerTimeout()
{
    static char c;
    std::string ss;

    // Serialize the data on DataQueue until '\n' charcater
    while(!mDataQueue.isEmpty())
    {

        c=mDataQueue.front();
        mDataQueue.pop_front();
        if(c!='\n')
        {
            ss.append(&c);
        }
        else
        {
            break;
        }
    }

    // Parse buffer to read needle angle
    if(ss.size()>0)
    {
        Event_t temp=mprotocol.parseFrame((char*)ss.c_str());
        mEventQueue.push_back(temp);

    }
}

