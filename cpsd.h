#ifndef CPSD_H
#define CPSD_H
#include "cfiles.h"
#include "loadsharedmemory.h"

class CPsd : private QSharedMemory
{
    Q_OBJECT

public:
    
    CPsd();
    ~CPsd();

public :

    Q_INVOKABLE void        calibrationPSD(double powerref);                           //Calibration of PSD: potentiometer are adjust and power ratio is calculate
    Q_INVOKABLE void        getvalue(bool state);

private slots:
    
    void        getparam();

private:
    
    void        initRdac();                                 //Set all Rdac potentiometer to 127
    void        getAdcPSD();                                //Store ADC value from PSD
    void        sumPSD();                                   //Sum ADC value for caculate position
    uint8_t     rdacCalibrationFinder();                    //Find the higher ADC value and return the interrelated potentiometre
    bool        dichoTomy(double powerref);                                //Find the beter Rdac value
    void        getPosition();                              //Position in micrometer is calculate
    void        getPowerPSD();                              //Return PSD power measurement
    void        getSharedMemory();
    void        memorizing();
    
    CFiles              m_data;
    QTimer              *m_timer;
    QSharedMemory       m_SharedMemory;
    uint32_t            m_maxADC;                                   //Nominal voltage corresponding to maximal power on phd, ADC value (12 bits)
    uint8_t             m_error;                                    //Uncertainty measurement
    uint32_t            m_ADCvalue;                                 //Store the ADC value during calibration
    double              m_sumPSD;                                   //ADC value Sum
    double              m_numerateurX;
    double              m_numerateurY;
    double              m_posX[10];
    double              m_posY[10];
    double              m_X;
    double              m_Y;
    double              m_powerratio;
    uint32_t            m_adcvalue[5];
    double              m_psdpower;
    double              m_powerrefPSD;
};

#endif // CPSD_H
