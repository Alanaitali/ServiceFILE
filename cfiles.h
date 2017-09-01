#ifndef CFILES_H
#define CFILES_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include <QSharedMemory>
#include <QTimer>
#include <QCoreApplication>
#include <QThread>



#define P1A             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002c/rdac0"
#define P1B             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002c/rdac1"
#define P2A             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002d/rdac0"
#define P2B             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002d/rdac1"
#define P3A             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002e/rdac0"
#define P3B             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002e/rdac1"
#define P4A             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002f/rdac0"
#define P4B             "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-002f/rdac1"

#define FSD_OUT         "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage0_raw"
#define PSD1_OUT        "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage1_raw"
#define PSD2_OUT        "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage2_raw"
#define PSD3_OUT        "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage3_raw"
#define PSD4_OUT        "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage4_raw"
#define T1_OUT          "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage5_raw"
#define T2_OUT          "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage6_raw"
#define AIN7            "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage7_raw"
#define AIN8            "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage8_raw"
#define AIN9            "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage9_raw"
#define AIN10           "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage10_raw"
#define AIN11           "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0035/iio:device1/in_voltage11_raw"

#define INTERLOCK       "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio504/value"
#define IN_PA1          "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio505/value"
#define IN_PA2          "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio506/value"
#define OUT_PA3         "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio507/value"
#define IN_PA4          "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio508/value"
#define OUT_PA5         "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio509/value"
#define OUT_PA6         "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio510/value"
#define OUT_PA7         "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio511/value"
#define OUT_PWM_GPIO    "/sys/devices/platform/soc/30800000.aips-bus/30a40000.i2c/i2c-2/2-0020/gpio/gpio200/value"



class CFiles: public QFile
{

public:

    CFiles();
    ~CFiles();

    /* Pot_num AD5282 I2C */

    void        setRdacPhotodiode(uint8_t);
    void        setRdacTr1(uint8_t);
    void        setRdacTr2(uint8_t);
    void        setRdacPSD1(uint8_t);
    void        setRdacPSD2(uint8_t);
    void        setRdacPSD3(uint8_t);
    void        setRdacPSD4(uint8_t);

    uint8_t     getRdacPhotodiode();
    uint8_t     getRdacTr1();
    uint8_t     getRdacTr2();
    uint8_t     getRdacPSD1();
    uint8_t     getRdacPSD2();
    uint8_t     getRdacPSD3();
    uint8_t     getRdacPSD4();

    /* adc MAX1238 I2C */

    quint16    getAdcPhotodiode();
    uint16_t    getAdcTr1();
    uint16_t    getAdcTr2();
    uint16_t    getAdcPSD1();
    uint16_t    getAdcPSD2();
    uint16_t    getAdcPSD3();
    uint16_t    getAdcPSD4();
    uint16_t    getAdcAIN7();
    uint16_t    getAdcAIN8();
    uint16_t    getAdcAIN9();
    uint16_t    getAdcAIN10();
    uint16_t    getAdcAIN11();

    /* GPIO */

   Q_INVOKABLE void        setGPIO (QString path,bool state);
   Q_INVOKABLE bool        getGPIO(QString path);

private:

    void Write_files(QString path, const char data);
    QByteArray Read_files(QString path);

};





#endif // CFILES_H
