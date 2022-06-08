#ifndef MODELOBJ_H
#define MODELOBJ_H
#include <QtCore>
#include <QFile>
#include "BaseModel.h"

class ModelObj : public BaseModel
{
public:
    ModelObj();

    /**
     * @see  BaseModel::LoadMdl
     */
    void LoadMdl() override; //Load model file

private:

    /**
     * @details This method parses input textual line in order to extract vertex data
     * @param IN::line Input 3d model file text line.
     */
    void ParseVertexData(QByteArray line);

    /**
     * @details This method parses input textual line in order to extract face data
     * @param IN::line Input 3d model file text line.
     */
    void ParseFacesData(QByteArray line);
};
#endif // MODELOBJ_H
