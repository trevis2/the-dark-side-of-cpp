#ifndef MODELOBJ_H
#define MODELOBJ_H
#include <QtCore>
#include <QFile>

struct vertex {
    float x;
    float y;
    float z;
    vertex() { }
    vertex(const float xCord,const float yCord,const float zCord):
    x(xCord),y(yCord) , z(zCord) { }
};
struct face {
    uint x;
    uint y;
    uint z;
    face() { }
    face(const uint xCord,const uint yCord,const uint zCord):
    x(xCord),y(yCord) , z(zCord) { }
};

typedef std::vector<vertex> vtxArray;
typedef std::vector<face> faceArray;

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
