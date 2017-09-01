#ifndef COMDBUS_H
#define COMDBUS_H

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include "cphotodiode.h"
#include "cpsd.h"

#define SERVICE_NAME            "amplitude.systemes.service.warptool"
#define PROPERTY_PATH           "/"

class Combus : public QObject
{
    Q_OBJECT
public:
    Combus();
    ~Combus();

    //SETTERS

    Q_INVOKABLE void calibrationFDS(double powerref);
    Q_INVOKABLE void calibrationPSD(double powerref);
    Q_INVOKABLE void calibrationTrans1(double powerref);
    Q_INVOKABLE void calibrationTrans2(double powerref);
    Q_INVOKABLE void photodiodeValue(bool state);
    Q_INVOKABLE void psdValue(bool state);
    Q_INVOKABLE void setGPIO (QString path,bool state);

private:
    CPhotodiode m_Photodiode;
    CPsd        m_Psd;
    CFiles      m_CFiles;

};

#endif // COMDBUS_H
