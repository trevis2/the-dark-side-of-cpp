#include "modelstl.h"
#include <QDebug>

ModelStl::ModelStl() : BaseModel()
{

}


void ModelStl::LoadMdl()
{
    if (!modelFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        //Error loading file
        qDebug("Loading obj model failed");
        return;
    }
    if (vtxArr.size() >0 ) {
        vtxArr.clear();
    }
    if (fArr.size() >0) {
        fArr.clear();
    }
    if (normalsArr.size() >0) {
        normalsArr.clear();
    }

    qDebug() << Q_FUNC_INFO  << modelFile->fileName();
    QByteArray header = modelFile->read(80);
    modelFile->close();

    if (header.trimmed().startsWith("solid") && header.contains("\n"))
    {
        qDebug("start to read text");
        readText();
    }
    else
    {
        qDebug("huaile");
        readBinary();
    }

}

void ModelStl::readBinary(){
    if (!modelFile->open(QIODevice::ReadOnly)) {
        //Error loading file
        qDebug("Loading obj model failed");
        return;
    }
    modelFile->seek(0);
    QDataStream in(modelFile);
    in.setByteOrder(QDataStream::LittleEndian);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);

    quint32 n;
    quint16 control_bytes;
    quint32 count = 0;

    modelFile->seek(80);
    in >> n;
    qDebug() << n << "triangles in the model.";
    float nx, ny, nz, x1, x2, x3, y1, y2, y3, z1, z2, z3;
    while (count < n) {
        modelFile->seek(84+count*50+0+0);
        in >> nx;
        modelFile->seek(84+count*50+0+4);
        in >> ny;
        modelFile->seek(84+count*50+0+8);
        in >> nz;
        modelFile->seek(84+count*50+12+0);
        in >> x1;
        modelFile->seek(84+count*50+12+4);
        in >> y1;
        modelFile->seek(84+count*50+12+8);
        in >> z1;
        modelFile->seek(84+count*50+24+0);
        in >> x2;
        modelFile->seek(84+count*50+24+4);
        in >> y2;
        modelFile->seek(84+count*50+24+8);
        in >> z2;
        modelFile->seek(84+count*50+36+0);
        in >> x3;
        modelFile->seek(84+count*50+36+4);
        in >> y3;
        modelFile->seek(84+count*50+36+8);
        in >> z3;
        modelFile->seek(84+count*50+48);
        in >> control_bytes;

       if (control_bytes == 0 && in.status() == QDataStream::Ok)  {
            vertex tmpNormal;
            tmpNormal.x = nx;
            tmpNormal.y = ny;
            tmpNormal.z = nz;

            vertex point1;
            point1.x = x1;
            point1.y = y1;
            point1.z = z1;

            vertex point2;
            point2.x = x2;
            point2.y = y2;
            point2.z = z2;

            vertex point3;
            point3.x = x3;
            point3.y = y3;
            point3.z = z3;
            normalsArr.push_back(tmpNormal);
            const int startIndex = vtxArr.size() + 3;
            vtxArr.push_back(point1);
            vtxArr.push_back(point2);
            vtxArr.push_back(point3);
            face tmpFace (startIndex - 2,
                          startIndex - 1,
                          startIndex);
            fArr.push_back(tmpFace);
            count++;
        } else {
            qDebug() << "CHECK NOT PASSED";
        }
        qDebug() << "I VALUE:"<< n;
    }

    modelFile->close();
    delete modelFile;
    qDebug() << "Vertices array size: " << vtxArr.size();
    qDebug() << "VERTEX USED IN FACES EVALUATION:" << count*3 ;
    qDebug() << "FACES: " << fArr.size() ;
}

void ModelStl::readText()
{
        if (!modelFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
            //Error loading file
            qDebug("Loading obj model failed");
            return;
        }
        QTextStream stream(modelFile);
        int count=0;

        QString line;
        QTextStream in(modelFile);
        line = in.readLine();                   // solid

        while(true)
        {
            line = in.readLine().trimmed();     //facet or endsolid
            if(line.trimmed().startsWith("endsolid"))
            {
                break;
            }
            vertex vn = coordinateFromString(line);
            line = in.readLine();               //outer loop
            line = in.readLine().trimmed();     //vertex 1
            vertex point1 = coordinateFromString(line);
            line = in.readLine().trimmed();     //vertex 2
            vertex point2 = coordinateFromString(line);
            line = in.readLine().trimmed();     //vertex 3
            vertex point3 = coordinateFromString(line);
            line = in.readLine();               //endloop
            line = in.readLine();               //endfacet

            normalsArr.push_back(vn);
            const int startIndex = vtxArr.size() + 3;
            vtxArr.push_back(point1);
            vtxArr.push_back(point2);
            vtxArr.push_back(point3);
            face tmpFace (startIndex - 2,
                          startIndex - 1,
                          startIndex);
            fArr.push_back(tmpFace);
            count++;
        }
        modelFile->close();
        delete modelFile;
        qDebug() << "Vertices array size: " << vtxArr.size();
        qDebug() << "VERTEX USED IN FACES EVALUATION:" << count*3 ;
        qDebug() << "FACES: " << fArr.size() ;
}

vertex ModelStl::coordinateFromString( const QString &line) {
    vertex coordinate;

    QStringList strList = line.split(" ");

   int count = strList.size();
   if(count > 3) {
      int startIndex = count - 3;
      coordinate.x =  strList[startIndex].toDouble();
      coordinate.y =  strList[startIndex + 1].toDouble();
      coordinate.z =  strList[startIndex + 2].toDouble();
   }
   return coordinate;
}
