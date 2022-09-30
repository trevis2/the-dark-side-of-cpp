#include "modelobj.h"

ModelObj::ModelObj(): BaseModel()
{

}


void ModelObj::LoadMdl()
{
    if(!modelFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        //Error loading file
        qDebug("Loading obj model failed");
        return;
    }
    if(vtxArr.size() >0 ) {
        vtxArr.clear();
    }
    if(fArr.size() >0) {
        fArr.clear();
    }
    while(!modelFile->atEnd()) {
        QByteArray line = modelFile->readLine();
        switch(line.at(0))
        {
        case 'v':
            ParseVertexData(line);
            break;
        case 'f':
            ParseFacesData(line);
            break;
        }
    }
}

void ModelObj::ParseVertexData(QByteArray line) {
    QString lineString(line);
    QStringList lineArgs = lineString.split(" ");
    if(lineArgs.count() == 4) {
        vertex tmpVtx;
        sscanf(line.data(),"v %f %f %f",&tmpVtx.x,&tmpVtx.y,&tmpVtx.z);
        vtxArr.push_back(tmpVtx);
    } else if(lineArgs.count() == 5) {
        vertex tmpVtx (lineArgs[1].toFloat(), lineArgs[2].toFloat(), lineArgs[3].toFloat());
        vtxArr.push_back(tmpVtx);
        vertex tmpVtx1 (lineArgs[3].toFloat(), lineArgs[4].toFloat(), lineArgs[1].toFloat());
        vtxArr.push_back(tmpVtx1);
    }
}

void ModelObj::ParseFacesData(QByteArray line)
{
//    GL_QUAD 1 2 3 4 = G_TRIANGLE 123 + 341 G_TRIANGLE
    QString lineString(line);
    QStringList lineArgs = lineString.split(" ");
    (void) lineArgs.removeAll("\n");
    if(lineArgs.count() == 4) {
            if ( lineString.contains("//") ) {
                face tmpFace (lineArgs[1].split("//").at(0).toUInt(),
                              lineArgs[2].split("//").at(0).toUInt(),
                              lineArgs[3].split("//").at(0).toUInt());
                fArr.push_back(tmpFace);

            } else if ( lineString.contains("/") ) {
                face tmpFace (lineArgs[1].split("/").at(0).toUInt(),
                              lineArgs[2].split("/").at(0).toUInt(),
                              lineArgs[3].split("/").at(0).toUInt());
                fArr.push_back(tmpFace);
            } else {
                 face tmpFace;
                 sscanf(line.data(),"f %d %d %d",&tmpFace.x,&tmpFace.y,&tmpFace.z);
                 fArr.push_back(tmpFace);
            }
    } else  if(lineArgs.count() == 5) {
        if ( lineString.contains("//") ) {
            face tmpFace (lineArgs[1].split("//").at(0).toUInt(),
                          lineArgs[2].split("//").at(0).toUInt(),
                          lineArgs[3].split("//").at(0).toUInt());
            fArr.push_back(tmpFace);
            face tmpFace1 (lineArgs[3].split("//").at(0).toUInt(),
                           lineArgs[4].split("//").at(0).toUInt(),
                           lineArgs[1].split("//").at(0).toUInt());
            fArr.push_back(tmpFace1);
        } else if ( lineString.contains("/") ) {
            face tmpFace (lineArgs[1].split("/").at(0).toUInt(),
                          lineArgs[2].split("/").at(0).toUInt(),
                          lineArgs[3].split("/").at(0).toUInt());
            fArr.push_back(tmpFace);
            face tmpFace1 (lineArgs[3].split("/").at(0).toUInt(),
                           lineArgs[4].split("/").at(0).toUInt(),
                           lineArgs[1].split("/").at(0).toUInt());
            fArr.push_back(tmpFace1);
        } else {
            face tmpFace (lineArgs[1].toUInt(),
                          lineArgs[2].toUInt(),
                          lineArgs[3].toUInt());
            fArr.push_back(tmpFace);
            face tmpFace1 (lineArgs[3].toUInt(),
                           lineArgs[4].toUInt(),
                           lineArgs[1].toUInt());
            fArr.push_back(tmpFace1);
        }
   }
}

