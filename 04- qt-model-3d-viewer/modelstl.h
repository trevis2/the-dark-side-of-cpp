#ifndef MODELSTL_H
#define MODELSTL_H
#include <QtCore>
#include <QFile>
#include "BaseModel.h"

class ModelStl: public BaseModel
{
public:
    ModelStl();

    /**
     * @see  BaseModel::LoadMdl
     */
    void LoadMdl() override; //Load model file

 private:

    /**
     * @details This method parses stl binary file.
     */
    void readBinary();

    /**
     * @details This method parses stl textual file.
     */
    void readText();

    /**
     * @details This method parses input textual line in order to extract vertex coordinates data
     * @param IN::line Input 3d model file text line.
     * @return Vertex data.
     */
    vertex coordinateFromString(const QString &line);
};
#endif // MODELSTL_H
