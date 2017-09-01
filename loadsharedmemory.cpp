#include "loadsharedmemory.h"

loadSharedMemory::loadSharedMemory() : QSharedMemory("Calibration")
{
    m_powerrefPSD=0;
    m_powerrefFSD=0;
    m_powerrefTr1=0;
    m_powerrefTr2=0;
    this->attach();
    this->create(50,ReadWrite);
    qDebug()<<"classe appelée";
    getSharedMemory();
}

void loadSharedMemory::getSharedMemory()
{
    this->attach(QSharedMemory::ReadWrite);
    QByteArray data;
    this->lock();
    data.setRawData((char*)this->constData(),this->size());
    this->unlock();
    QDataStream stream(&data,QIODevice::ReadWrite);
    stream >> m_powerrefPSD;
    stream >> m_powerrefFSD;
    stream >> m_powerrefTr1;
    stream >> m_powerrefTr2;
    qDebug()<<"calpsd"<<m_powerrefPSD;
    qDebug()<<"calfds"<<m_powerrefFSD;
    qDebug()<<"caltr1"<<m_powerrefTr1;
    qDebug()<<"caltr2"<<m_powerrefTr2;
}






