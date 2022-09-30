#include "BaseModel.h"

BaseModel::BaseModel()
{
    modelFile = nullptr;
    #ifdef Q_OS_LINUX
    setlocale(LC_NUMERIC, "C");
    #endif
}

BaseModel::~BaseModel()
{
    if(modelFile != nullptr && modelFile->isOpen())
        modelFile->close();
}

void BaseModel::updateModelSourceFile(QString file)
{
    qDebug() << Q_FUNC_INFO << file;
    if(modelFile != nullptr) {
        delete modelFile;
        modelFile = nullptr;
    }
    modelFile = new QFile(file);
    modelFile->setFileName(file);
    #ifdef Q_OS_LINUX
    setlocale(LC_NUMERIC, "C");
    #endif
    LoadMdl();
}

void BaseModel::LoadMdl() {

}

vtxArray BaseModel::GetVertices()
{
    //Check for vtxArr consistency
    if(vtxArr.capacity() == 0) {
        qDebug("Vertex array is empty:");
        if(!modelFile->isOpen())
            qDebug("Model file not loaded!");
        else
            qDebug("Something goes wrong!");
    }
    return vtxArr;
}

faceArray BaseModel::GetFaces()
{
    return fArr;
}

vtxArray BaseModel::GetNormals()
{
    //Check for normalsArr consistency
    if(normalsArr.capacity() == 0) {
        qDebug("Normals array is empty:");
        if(!modelFile->isOpen())
            qDebug("Model file not loaded!");
        else
            qDebug("Something goes wrong!");
    }
    return normalsArr;
}
