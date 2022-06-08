#ifndef MODELSTL_H
#define MODELSTL_H
#include <QtCore>
#include <QFile>
#include "BaseModel.h"

class ModelStl
{
public:
    ModelStl();
    ~ModelStl();
    void updateModelSourceFile(QString file);
    void LoadMdl();//Load model file
    vtxArray GetVertices();//Get model vertices
    vtxArray GetNormals();//Get model vertices
    faceArray GetFaces();//Get model faces
private:
    int * vertices;
    QFile* stlFile;
    vtxArray vtxArr;
    vtxArray normalsArr;
    faceArray fArr;

 private:
    void readBinary();
    void readText();
    vertex coordinateFromString(const QString &line);
};
#endif // MODELSTL_H
