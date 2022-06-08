#ifndef MODELSTL_H
#define MODELSTL_H
#include <QtCore>
#include <QFile>
#include "BaseModel.h"

class ModelStl: public BaseModel
{
public:
    ModelStl();
    ~ModelStl();
    void updateModelSourceFile(QString file);
    void LoadMdl();//Load model file

private:
    int * vertices;

 private:
    void readBinary();
    void readText();
    vertex coordinateFromString(const QString &line);
};
#endif // MODELSTL_H
