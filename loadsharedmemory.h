#ifndef LOADSHAREDMEMORY_H
#define LOADSHAREDMEMORY_H

#include <QSharedMemory>
#include <QDataStream>
#include <QDebug>

class loadSharedMemory : private QSharedMemory

{
    Q_OBJECT

public:

    loadSharedMemory();
    void getSharedMemory();


    double                      m_powerrefPSD;
    double                      m_powerrefFSD;
    double                      m_powerrefTr1;
    double                      m_powerrefTr2;
};

#endif // LOADSHAREDMEMORY_H
