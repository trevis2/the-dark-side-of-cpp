#ifndef MODELOBJ_H
#define MODELOBJ_H
#include <QtCore>
#include <QFile>
#include "BaseModel.h"

class ModelObj : public BaseModel
{
public:
    ModelObj();
    ~ModelObj();
    void updateModelSourceFile(QString file);
    void LoadMdl();//Load model file

private:
    int * vertices;
    void ParseVertexData(QByteArray line);
    void ParseFacesData(QByteArray line);
};
#endif // MODELOBJ_H
