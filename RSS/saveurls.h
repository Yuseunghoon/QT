#ifndef SAVEURLS_H
#define SAVEURLS_H

//#include "saveurls_global.h"

class QStringList;

class SaveUrls
{
public:
    SaveUrls();

    void save(QStringList);
    QStringList load();
};

#endif // SAVEURLS_H
