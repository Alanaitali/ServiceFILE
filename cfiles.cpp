#include "cfiles.h"


CFiles::CFiles()
{

}

CFiles::~CFiles()
{
    
}

void CFiles::Write_files(QString path, const char data)
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(QByteArray::number(data));
        file.close();
    }
    else
        qDebug() << "Couldn't open file" << path;
}



QByteArray CFiles::Read_files(QString path)
{
    QByteArray test;

    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        test = file.readAll();
        test.remove(test.length()-1,1);
        file.close();
    }
    return test;
}

/* Set AD5282 Potentiometers  */

void CFiles::setRdacPhotodiode(uint8_t value)
{

    Write_files(P4A, value);
}

void CFiles::setRdacTr1(uint8_t value)
{
    Write_files(P3B, value);
}

void CFiles::setRdacTr2(uint8_t value)
{
    Write_files(P3A, value);
}

void CFiles::setRdacPSD1(uint8_t value)
{
    Write_files(P2B, value);
}

void CFiles::setRdacPSD2(uint8_t value)
{
    Write_files(P1B, value);
}

void CFiles::setRdacPSD3(uint8_t value)
{
    Write_files(P1A, value);
}

void CFiles::setRdacPSD4(uint8_t value)
{
    Write_files(P2A, value);
}

/* Get AD5282 Potentiometers  */

uint8_t CFiles::getRdacPhotodiode()
{
    return (Read_files(P4A).toUInt());
}

uint8_t CFiles::getRdacTr1()
{
    return (Read_files(P3B).toUInt());
}

uint8_t CFiles::getRdacTr2()
{
    return (Read_files(P3A).toUInt());
}

uint8_t CFiles::getRdacPSD1()
{
    return (Read_files(P2B).toUInt());
}

uint8_t CFiles::getRdacPSD2()
{
   return (Read_files(P1B).toUInt());
}

uint8_t CFiles::getRdacPSD3()
{
    return (Read_files(P1A).toUInt());
}

uint8_t CFiles::getRdacPSD4()
{
    return (Read_files(P2A).toUInt());
}

/* Get MAX1238 voltage  */

quint16 CFiles::getAdcPhotodiode()
{
    return (Read_files(FSD_OUT).toUInt());
}

uint16_t CFiles::getAdcTr1()
{
    return (Read_files(T1_OUT).toUInt());
}

uint16_t CFiles::getAdcTr2()
{
    return (Read_files(T2_OUT).toUInt());
}

uint16_t CFiles::getAdcPSD1()
{
    return (Read_files(PSD1_OUT).toUInt());
}

uint16_t CFiles::getAdcPSD2()
{
    return (Read_files(PSD2_OUT).toUInt());
}

uint16_t CFiles::getAdcPSD3()
{
    return (Read_files(PSD3_OUT).toUInt());
}

uint16_t CFiles::getAdcPSD4()
{
    return (Read_files(PSD4_OUT).toUInt());
}

uint16_t CFiles::getAdcAIN7()
{
    return (Read_files(AIN7).toUInt());
}

uint16_t CFiles::getAdcAIN8()
{
    return (Read_files(AIN8).toUInt());
}

uint16_t CFiles::getAdcAIN9()
{
    return (Read_files(AIN9).toUInt());
}

uint16_t CFiles::getAdcAIN10()
{
    return (Read_files(AIN10).toUInt());
}

uint16_t CFiles::getAdcAIN11()
{
    return (Read_files(AIN11).toUInt());
}



/* Get & Set GPIO */


void CFiles::setGPIO(QString path,bool state)
{
    Write_files(path,state);
}

bool CFiles::getGPIO(QString path)
{
    return  Read_files(path).toInt();
}






