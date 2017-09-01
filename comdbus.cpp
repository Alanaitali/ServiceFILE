#include "comdbus.h"

#include <QDebug>
#include <QThread>

Combus::Combus()
{

    //DBUS INIT

    if (!QDBusConnection::systemBus().isConnected())
    {
        qDebug() << "DBUS not started !";
    }
    if (!QDBusConnection::systemBus().registerService(SERVICE_NAME))
    {
        qDebug() << "Already Registered !";
    }

    QDBusConnection::systemBus().registerObject(PROPERTY_PATH, this, QDBusConnection::ExportAllInvokables | QDBusConnection::ExportScriptableSignals);
}

Combus::~Combus()
{

}

void Combus::calibrationFDS(double powerref)
{
     m_Photodiode.calibrationFDS(powerref);
     qDebug()<<"powerrefFDS"<<powerref;
}

void Combus::calibrationPSD(double powerref)
{
    m_Psd.calibrationPSD(powerref);
    qDebug()<<"powerrefpsd"<<powerref;
}

void Combus::calibrationTrans1(double powerref)
{
    m_Photodiode.calibrationTrans1(powerref);
    qDebug()<<"powerref tr1"<<powerref;
}

void Combus::calibrationTrans2(double powerref)
{
    qDebug()<<"powerref tr2"<<powerref;
    return m_Photodiode.calibrationTrans2(powerref);
}

void Combus::photodiodeValue(bool state)
{
    m_Photodiode.getvalue(state);
    qDebug()<<"getvalue state"<<state;
}

void Combus::psdValue(bool state)
{
    m_Psd.getvalue(state);
    qDebug()<<"psdcomm bus"<<state;
}

void Combus::setGPIO(QString path, bool state)
{
    qDebug()<<"gpio"<<path<<"set";
    m_CFiles.setGPIO(path,state);

}

