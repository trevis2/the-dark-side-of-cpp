#ifndef BASEMODEL_H
#define BASEMODEL_H
#include <QtCore>

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

#endif // BASEMODEL_H
