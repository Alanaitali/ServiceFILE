#include "cphotodiode.h"


CPhotodiode::CPhotodiode() : QSharedMemory ("PowerPhotodiode")                                          //give a key to share memory space
{
    m_maxADC=4000;
    m_error=5;
    m_ADCvalue=0;
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(getparam()));
    this->detach();
    this->create(24,ReadWrite);                                                                         //config and attach the share memory
}

CPhotodiode::~CPhotodiode()
{
    delete m_timer;
}

void CPhotodiode::getvalue(bool state)
{
    qDebug()<<"in value state"<<state;
    if(state==true)
    {
      m_timer->start(500);
    }
    else
    {
        m_timer->stop();
    }
}

void CPhotodiode::calibrationFDS(double powerref)
{
    int i=0;
    m_data.setRdacPhotodiode(128);
    m_ADCvalue=m_data.getAdcPhotodiode();
    while(((m_ADCvalue>m_maxADC+m_error)||(m_ADCvalue<m_maxADC-m_error))&&(i<10))
    {
        QThread::msleep(1000);
        i++;
        m_ADCvalue=m_data.getAdcPhotodiode();
        qDebug() <<"ADCphotodiode"<< m_ADCvalue;
        if(m_ADCvalue>m_maxADC+m_error)
        {
            m_data.setRdacPhotodiode((m_data.getRdacPhotodiode())+(128>>i));
            qDebug() <<"Rdacpos"<< m_data.getRdacPhotodiode();
        }
        if(m_ADCvalue<m_maxADC-m_error)
        {
            m_data.setRdacPhotodiode((m_data.getRdacPhotodiode())-(128>>i));
            qDebug() <<"Rdacneg"<< m_data.getRdacPhotodiode();
        }
    }
    if (((m_maxADC+m_error)>= m_data.getAdcPhotodiode())&&(m_maxADC-m_error)<=m_data.getAdcPhotodiode())
    {
        m_ratiopowerFSD = powerref/m_maxADC;
        m_calstateFDS = true;
    }
    else
    {
        m_calstateFDS = true;
    }
}


void CPhotodiode::calibrationTrans1(double powerref)
{
    int i=0;
    m_data.setRdacTr1(128);
    qDebug() <<"debut"<< m_data.getRdacTr1();
    while(((m_ADCvalue>m_maxADC+m_error)||(m_ADCvalue<m_maxADC-m_error))&&(i<10))
    {
        QThread::msleep(1000);
        i++;
        m_ADCvalue=m_data.getAdcTr1();
        qDebug() <<"ADC Tr1"<< m_ADCvalue;
        if(m_ADCvalue>m_maxADC+m_error)
        {
            m_data.setRdacTr1((m_data.getRdacTr1())+(128>>i));
            qDebug() <<"Rdacpos"<< m_data.getRdacTr1();
        }
        if(m_ADCvalue<m_maxADC-m_error)
        {
            m_data.setRdacTr1((m_data.getRdacTr1())-(128>>i));
            qDebug() <<"Rdacneg"<< m_data.getRdacTr1();
        }
    }
    if (((m_maxADC+m_error)>= m_data.getAdcTr1())&&(m_maxADC-m_error)<=m_data.getAdcTr1())
    {
        m_ratiopowerTr1 = powerref/m_maxADC;
        m_calstateTrans1 = true;
    }
    else
    {
        m_calstateTrans1 = false;
    }
}

void CPhotodiode::calibrationTrans2(double powerref)
{
    int i=0;
    m_data.setRdacTr2(128);

    while(((m_ADCvalue>m_maxADC+m_error)||(m_ADCvalue<m_maxADC-m_error))&&(i<10))
    {
        i++;
        QThread::msleep(1000);
        qDebug() <<"ADCTr2"<< m_ADCvalue;
        m_ADCvalue=m_data.getAdcTr2();
        if(m_ADCvalue>m_maxADC+m_error)
        {
            m_data.setRdacTr2((m_data.getRdacTr2()+(128>>i)));
            qDebug() <<"Rdacpos"<< m_data.getRdacTr2();
        }
        if(m_ADCvalue<m_maxADC-m_error)
        {
            m_data.setRdacTr2((m_data.getRdacTr2()-(128>>i)));
            qDebug() <<"Rdacneg"<< m_data.getRdacTr2();
        }
    }
    if (((m_maxADC+m_error)>= m_data.getAdcTr2())&&(m_maxADC-m_error)<=m_data.getAdcTr2())
    {
        m_ratiopowerTr2 = powerref/m_maxADC;
        m_calstateTrans2 = true;
    }
    else
    {
        m_calstateTrans2 = false;
    }
}

void CPhotodiode::getPowerFSD()
{
    m_powerFSD = m_data.getAdcPhotodiode()*m_ratiopowerFSD;
}

void CPhotodiode::getPowerTrans1()
{
    m_powertrans1=m_data.getAdcTr1()*m_ratiopowerTr1;
}

void CPhotodiode::getPowerTrans2()
{
    m_powertrans2=m_data.getAdcTr2()*m_ratiopowerTr2;
}

void CPhotodiode::memorizing()
{
    if(this->isAttached())
    {
        QByteArray sharedata;
        QDataStream stream(&sharedata,QIODevice::ReadWrite);
        qDebug()<<"FSD"<< m_powerFSD;
        qDebug()<<"tr1"<< m_powertrans1;
        qDebug()<<"tr2"<< m_powertrans2;
        stream << m_powerFSD;
        stream << m_powertrans1;
        stream << m_powertrans2;
        this->lock();
        char *to=(char*)this->data();
        memcpy(to, sharedata.data(), qMin(this->size(), (qint32)sharedata.size()));
        this->unlock();
    }
    else
    {
        this->attach();
        qDebug()<<"no shared";
    }
}


void CPhotodiode::getparam()
{
    getPowerFSD();
    getPowerTrans1();
    getPowerTrans2();
    memorizing();
}

double CPhotodiode::ADC_Voltage (double value)
{
    value = (5 * value)/ 4095;
    qDebug() << value;
    return value;
}
