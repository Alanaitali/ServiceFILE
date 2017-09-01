#include "calibration.h"

Calibration::Calibartion();
Calibration::Calibration(QString path)
{
    uint8_t test=0;
    setPot(path,127);
    for(uint8_t i=1;i<5;i++)

    {

        if(getADC(FSD_OUT)<MaxADC)
        {
           setPot(P1A,(getPot(path) +(123/(2*i))));
        }
        if(getADC(FSD_OUT)>MaxADC)
        {
            setPot(P1A,(getPot(path) -(123/(2*i))));
        }
        qDebug()<<(123/(2*i));
        qDebug()<<getPot(path) ;
    }
}

Calibration::Calibration(QString path1, QString path2, QString path3, QString path4)
{

}

