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

class BaseModel {
public:
    BaseModel();
    virtual ~BaseModel();
    /**
     * @details This method updates 3d model file path.
     * @param IN::file 3d model file path
     */
    void updateModelSourceFile(QString file);

    /**
     * @details This method loads 3d model.
     */
    virtual void LoadMdl();

    /**
     * @details This Method returns the list of vertices.
     * @return Array of model triangle vertices.
     */
    vtxArray GetVertices();

    /**
     * @details This Method returns the list of faces.
     * @return Array of model triangle faces.
     */
    faceArray GetFaces();

    /**
     * @details This Method returns the list of normal vectors.
     * @return Array of normal vectors.
     */
    vtxArray GetNormals();

  protected:
    QFile* modelFile;       /** 3D Model File**/
    vtxArray vtxArr;        /** Array of vertices **/
    vtxArray normalsArr;    /** Array of normal vectors**/
    faceArray fArr;         /** Array of faces **/
};
#endif // BASEMODEL_H
