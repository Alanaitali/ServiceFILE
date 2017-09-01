#include "cpsd.h"
#include <QtGlobal>

CPsd::CPsd(): QSharedMemory ("PSDpower")
{
    m_timer=new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(getparam()));
    m_sumPSD=0;
    m_X=0;
    m_Y=0;
    this->detach();
    this->create(50,ReadWrite);

}

CPsd::~CPsd()
{
    delete m_timer;
}

void CPsd::calibrationPSD(double powerref)
{
    initRdac();
    dichoTomy(powerref);
}

void CPsd::getvalue(bool state)
{
    if(state==true)
    {
       qDebug()<<"timer psd";
      m_timer->start(500);
    }
    else
    {
        m_timer->stop();
    }

}

void CPsd::getPosition()
{
    for(int average=0;average<10;++average)
    {
        getAdcPSD();
        sumPSD();

        // Calculate ADC numerators values for X and Y position
        // Numerator X = ( X2 + Y1 ) - ( X1 + Y2 )
        // Numerator Y = ( X2 + Y2 ) - ( X1 + Y1 )

        m_numerateurX=((m_adcvalue[1]+m_adcvalue[2])-(m_adcvalue[0]+m_adcvalue[3]));
        m_numerateurY=((m_adcvalue[1]+m_adcvalue[3])-(m_adcvalue[0]+m_adcvalue[2]));

        // Calculate X and Y position

        m_posX[average]=(5.0*(m_numerateurX/m_sumPSD))*1000; // *1000 in micrometre
        m_posY[average]=(5.0*(m_numerateurY/m_sumPSD))*1000; // *1000 in micrometre
        m_X+=m_posX[average];
        m_Y+=m_posY[average];
        m_X=m_X/2;
        m_Y=m_Y/2;
    }
}

void CPsd::getPowerPSD()
{
    getAdcPSD();
    sumPSD();
    m_psdpower = (m_sumPSD/4)*m_powerratio;
}

void CPsd::memorizing()
{
    if(this->isAttached())
    {
        QByteArray sharedata;
        QDataStream stream(&sharedata,QIODevice::ReadWrite);
        getPosition();
        getPowerPSD();
        qDebug()<<"psd"<<m_psdpower;
        qDebug()<<"x"<<m_X;
        qDebug()<<"y"<<m_X;
        stream << m_X;
        stream << m_Y;
        stream << m_psdpower;
        this->lock();
        char *to=(char*)this->data();
        memcpy(to, sharedata.data(), qMin(this->size(), (qint32)sharedata.size()));
        this->unlock();
        qDebug()<<"data"<<sharedata;
    }
    else
    {
        this->attach();
        qDebug()<<"nonshared";
    }
}

uint8_t CPsd::rdacCalibrationFinder()
{
    uint8_t     index=0;
    uint16_t    maxvalue=0;

    getAdcPSD();

    for(int i=0;i<3;++i)
    {
        if(maxvalue<m_adcvalue[i])
        {
            maxvalue=m_adcvalue[i];
            index=i;
        }
    }
    return index;
}

bool CPsd::dichoTomy(double powerref)
{
    int i=0;

    switch (rdacCalibrationFinder()){

    case 0:

        while(((m_ADCvalue>m_maxADC+m_error)||(m_ADCvalue<m_maxADC-m_error))&&(i<10))
        {
            QThread::msleep(1000);
            i++;
            m_ADCvalue=m_data.getAdcPSD1();

            if(m_ADCvalue>m_maxADC+m_error)
            {
                m_data.setRdacPSD1((m_data.getRdacPSD1())+(128>>1));
            }

            if(m_ADCvalue<m_maxADC-m_error)
            {
                m_data.setRdacPSD1((m_data.getRdacPSD1())-(128>>1));
            }
        }

        if (((m_maxADC+m_error)>= m_data.getAdcPSD1())&&(m_maxADC-m_error)<=m_data.getAdcPSD1())
        {
            m_powerratio = powerref/m_maxADC;
            return true;
        }

        else
        {
            return false;
        }

    case 1:

        while(((m_ADCvalue>m_maxADC+m_error)||(m_ADCvalue<m_maxADC-m_error))&&(i<10))
        {
            i++;
            m_ADCvalue=m_data.getAdcPSD2();

            if(m_ADCvalue>m_maxADC+m_error)
            {
                m_data.setRdacPSD2((m_data.getRdacPSD2())+(128>>1));
            }

            if(m_ADCvalue<m_maxADC-m_error)
            {
                m_data.setRdacPSD2((m_data.getRdacPSD2())-(128>>1));
            }
        }

        if (((m_maxADC+m_error)>= m_data.getAdcPSD2())&&(m_maxADC-m_error)<=m_data.getAdcPSD2())
        {
            m_powerratio = powerref/m_maxADC;
            return true;
        }

        else
        {
            return false;
        }

    case 2:

        while(((m_ADCvalue>m_maxADC+m_error)||(m_ADCvalue<m_maxADC-m_error))&&(i<10))
        {
            i++;
            m_ADCvalue=m_data.getAdcPSD3();

            if(m_ADCvalue>m_maxADC+m_error)
            {
                m_data.setRdacPSD3((m_data.getRdacPSD3())+(128>>1));
            }

            if(m_ADCvalue<m_maxADC-m_error)
            {
                m_data.setRdacPSD3((m_data.getRdacPSD3())-(128>>1));
            }
        }

        if (((m_maxADC+m_error)>= m_data.getAdcPSD3())&&(m_maxADC-m_error)<=m_data.getAdcPSD3())
        {
            m_powerratio = powerref/m_maxADC;
            return true;
        }

        else
        {
            return false;
        }

    case 3:

        while(((m_ADCvalue>m_maxADC+m_error)||(m_ADCvalue<m_maxADC-m_error))&&(i<10))
        {
            i++;
            m_ADCvalue=m_data.getAdcPSD4();

            if(m_ADCvalue>m_maxADC+m_error)
            {
                m_data.setRdacPSD4((m_data.getRdacPSD4())+(128>>1));
            }

            if(m_ADCvalue<m_maxADC-m_error)
            {
                m_data.setRdacPSD4((m_data.getRdacPSD4())-(128>>1));
            }
        }
        if (((m_maxADC+m_error)>= m_data.getAdcPSD4())&&(m_maxADC-m_error)<=m_data.getAdcPSD4())
        {
            m_powerratio = powerref/m_maxADC;
            return true;
        }
        else
        {
            return false;
        }
    default:
        return false;
    }
}


//Set the Rdac mid value
void CPsd::initRdac()
{
    m_data.setRdacPSD1(128);
    m_data.setRdacPSD2(128);
    m_data.setRdacPSD3(128);
    m_data.setRdacPSD4(128);
}

//Store ADC value to calculate
void CPsd::getAdcPSD()
{
    m_adcvalue[0]=m_data.getAdcPSD1();
    m_adcvalue[1]=m_data.getAdcPSD2();
    m_adcvalue[2]=m_data.getAdcPSD3();
    m_adcvalue[3]=m_data.getAdcPSD4();

}

//Sum ADC value to denominator number
void CPsd::sumPSD()
{
    for(int i=0;i<4;++i)
    {
        m_sumPSD+=m_adcvalue[i];
    }
}

void CPsd::getSharedMemory()
{
    m_SharedMemory.setKey("Calibration");
    m_SharedMemory.attach(QSharedMemory::ReadWrite);
    QByteArray data;
    this->lock();
    data.setRawData((char*)this->constData(),this->size());
    this->unlock();
    QDataStream stream(&data,QIODevice::ReadWrite);
    stream >> m_powerrefPSD;
    qDebug()<<"calpsd"<<m_powerrefPSD;
}

void CPsd::getparam()
{
    getPowerPSD();
    getPosition();
    memorizing();
}
