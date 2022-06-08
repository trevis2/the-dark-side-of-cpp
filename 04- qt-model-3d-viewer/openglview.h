#ifndef GLWIN_H
#define GLWIN_H

#include <QtGui>
#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <math.h>
#include <vector>
#include "BaseModel.h"

typedef struct
{
    GLfloat posX,posY,posZ;
    GLfloat rotX,rotY,rotZ;
    QPoint  lastPos;
}
Camera_t;

class OpenGLView : public QGLWidget
{
    Q_OBJECT
    
public:
    OpenGLView(QWidget *parent = 0);
    ~OpenGLView();

    /**
     * @brief keyPressEvent
     * @param ke
     */
    void keyPressEvent(QKeyEvent *ke) override;

    /**
     * @brief paintModelFromFile
     * @param filePath
     */
    void paintModelFromFile(const QString filePath);

public slots:
    /**
     * @brief setDirectionalLightMode
     * @param isDirectional
     */
    void setDirectionalLightMode(const bool isDirectional);
    /**
     * @brief directionalLightMode
     * @return
     */
    inline bool directionalLightMode() const { return m_isDirectionalLight; }

    /**
     * @brief setXRotation
     * @param xAngle
     */
    void setXRotation(int xAngle);
    /**
     * @brief modelXRotation
     * @return
     */
    inline int modelXRotation() const { return qRound(m_xRot); }

    /**
     * @brief setYRotation
     * @param yAngle
     */
    void setYRotation(int yAngle);
    /**
     * @brief modelYRotation
     * @return
     */
    inline int modelYRotation() const { return qRound(m_yRot);}

    /**
     * @brief setZRotation
     * @param zAngle
     */
    void setZRotation(int zAngle);
    /**
     * @brief modelZRotation
     * @return
     */
    inline int modelZRotation() const { return qRound(m_zRot);}

    /**
     * @brief setScale
     * @param scaleFactor
     */
    void setScale(int scaleFactor);
    /**
     * @brief scaleFactor
     * @return
     */
    int scaleFactor() const {return static_cast<int>(scale * 10.0f);}

    /**
     * @brief setLightIntensity
     * @param intensity
     */
    void setLightIntensity(int intensity);
    /**
     * @brief setLightZPosition
     * @param zPosition
     */
    void setLightZPosition(int zPosition);
    /**
     * @brief setLightYPosition
     * @param yPosition
     */
    void setLightYPosition(int yPosition);
    /**
     * @brief setLightXPosition
     * @param xPosition
     */
    void setLightXPosition(int xPosition);
    /**
     * @brief setAmbientLightR
     * @param value
     */
    void setAmbientLightR(double value);
    /**
     * @brief setAmbientLightG
     * @param value
     */
    void setAmbientLightG(double value);
    /**
     * @brief setAmbientLightB
     * @param value
     */
    void setAmbientLightB(double value);
    /**
     * @brief setDiffuseLightR
     * @param value
     */
    void setDiffuseLightR(double value);
    /**
     * @brief setDiffuseLightG
     * @param value
     */
    void setDiffuseLightG(double value);
    /**
     * @brief setDiffuseLightB
     * @param value
     */
    void setDiffuseLightB(double value);
    /**
     * @brief setSpecularLightR
     * @param value
     */
    void setSpecularLightR(double value);
    /**
     * @brief setSpecularLightG
     * @param value
     */
    void setSpecularLightG(double value);
    /**
     * @brief setSpecularLightB
     * @param value
     */
    void setSpecularLightB(double value);

    /**
     * @brief setCameraXPosition
     * @param xPosition
     */
    void setCameraXPosition(int xPosition);
    /**
     * @brief setCameraYPosition
     * @param yPosition
     */
    void setCameraYPosition(int yPosition);
    /**
     * @brief setCameraZPosition
     * @param zPosition
     */
    void setCameraZPosition(int zPosition);

    /**
     * @brief setModelXPosition
     * @param xPosition
     */
    void setModelXPosition(int xPosition);
    /**
     * @brief modelXPosition
     * @return
     */
    inline int modelXPosition() const {return static_cast<int>(xTra);}

    /**
     * @brief setModelYPosition
     * @param yPosition
     */
    void setModelYPosition(int yPosition);
    /**
     * @brief modelYPosition
     * @return
     */
    inline int modelYPosition() const {return static_cast<int>(yTra);}

    /**
     * @brief setModelZPosition
     * @param zPosition
     */
    void setModelZPosition(int zPosition);
    /**
     * @brief modelZPosition
     * @return
     */
    inline int modelZPosition() const {return static_cast<int>(zTra);}

private:
    /**
     * @brief drawFloorGrid
     * @param size
     * @param step
     */
    void drawFloorGrid(float size, float step);
    /**
     * @brief drawAxis
     * @param axisLength
     */
    void drawAxis(GLfloat axisLength);

private slots:
    /**
     * @brief wheelEvent
     * @param event
     */
    void wheelEvent(QWheelEvent *event) override;
private:
    /**
     * @brief initializeGL
     */
    void initializeGL() override;
    /**
     * @brief resizeGL
     * @param w
     * @param h
     */
    void resizeGL(int w, int h) override;
    /**
     * @brief paintGL
     */
    void paintGL() override;

    /**
     * @brief setFrustum
     * @param fovY
     * @param aspect
     * @param zNear
     * @param zFar
     */
    void setFrustum(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

private:
    GLuint paintMdl();/** **/
    BaseModel *model;/** **/
    vtxArray vtxArr;/** **/
    QTimer *timer;/** **/
    ushort iRot;/** **/
    float m_xRot;/** **/
    float m_yRot;/** **/
    float m_zRot;/** **/
    GLuint idx;/** **/
    GLfloat xTra, yTra, zTra;/** **/
    GLuint fov;/** **/
    GLdouble zN;/** **/
    GLdouble zF;/** **/
    GLboolean shadingMode;/** **/
    GLfloat LightAmbient[4];/** **/
    GLfloat LightDiffuse[4];/** **/
    GLfloat LightSpecular[4];/** **/
    GLfloat LightPosition[4];/** **/
    GLfloat CameraPosition[3];/** **/
    GLfloat m_lightIntensity;/** **/
    float m_lastDiffuseR = 0.0f ,m_lastDiffuseG = 0.0f ,m_lastDiffuseB = 0.0f;/** **/
    bool m_isDirectionalLight;/** **/
    bool wireFrameMode;/** **/
    float scale, s0;/** **/
    void lights();/** **/
    GLuint m_gridLenght;/** **/
    GLuint vao;/** **/
    Camera_t m_camera;/** **/
    int m_intVal;/** **/

 signals:
    void modelXRotationChanged();
    void modelYRotationChanged();
    void modelZRotationChanged();
    void modelXPositionChanged();
    void modelYPositionChanged();
    void modelZPositionChanged();
    void scaleChanged();
};

#endif // GLWIN_H
