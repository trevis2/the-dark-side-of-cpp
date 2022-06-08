#ifndef MODELOBJ_H
#define MODELOBJ_H
#include <QtCore>
#include <QFile>
#include "BaseModel.h"

class ModelObj
{
public:
    ModelObj();
    ~ModelObj();
    void updateModelSourceFile(QString file);
    void LoadMdl();//Load model file
    vtxArray GetVertices();//Get model vertices
    faceArray GetFaces();//Get model faces
private:
    int * vertices;
    QFile* objFile;
    vtxArray vtxArr;
    faceArray fArr;
    void ParseVertexData(QByteArray line);
    void ParseFacesData(QByteArray line);
};
#endif // MODELOBJ_H
