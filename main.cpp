
#include <QCoreApplication>
#include "cfiles.h"
#include "cphotodiode.h"
#include "cpsd.h"
#include "comdbus.h"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
Combus c;
//CFiles *file = new CFiles;
//file->Write_files("/sys/devices/platform/gpio-exporter/out_PA2/value",1);
    /*test photodiode*/
/*CPhotodiode photo;
photo.getvalue(true);
    /*photo.calibrationTrans1();
    photo.calibrationTrans2();*/

    /*test psd
    CPsd psd;
    psd.calibrationPSD();*/



    return a.exec();
}

