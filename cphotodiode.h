#ifndef CPHOTODIODE_H
#define CPHOTODIODE_H
#include "cfiles.h"
#include "loadsharedmemory.h"



class CPhotodiode : private QSharedMemory
{
    Q_OBJECT

public:

    CPhotodiode();
    ~CPhotodiode();

public:
    Q_INVOKABLE void                    getvalue(bool state);
    Q_INVOKABLE void        calibrationFDS(double powerref);
    Q_INVOKABLE void        calibrationTrans1(double powerref);
    Q_INVOKABLE void        calibrationTrans2(double powerref);




private slots :

    void        getparam();                         //Collect ADC value

private:

    void        memorizing();                       //Place parametres in SharedMemory
    double      ADC_Voltage (double value);
    void        getPowerFSD();
    void        getPowerTrans1();
    void        getPowerTrans2();
    void        getSharedMemory();

    CFiles              m_data;
    QTimer              *m_timer;
    uint32_t            m_maxADC;                    //Nominal voltage corresponding to maximal power on phd, ADC value (12 bits)
    uint8_t             m_error;                     //Uncertainty measurement
    uint32_t            m_ADCvalue;                  //Store the ADC value during calibration
    double              m_ratiopowerFSD;             // mW/bit convert bit in mW
    double              m_ratiopowerTr1;
    double              m_ratiopowerTr2;
    double              m_powerFSD;
    double              m_powertrans1;
    double              m_powertrans2;
    bool                m_calstateFDS;
    bool                m_calstateTrans1;
    bool                m_calstateTrans2;

};

#endif // CPHOTODIODE_H
