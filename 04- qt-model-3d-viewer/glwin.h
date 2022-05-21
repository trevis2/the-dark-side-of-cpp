#ifndef GLWIN_H
#define GLWIN_H

#include <QtGui>
#include <QGLWidget>
#include <QtOpenGL>
//#include <GL/glu.h>
#include <QTimer>
#include <math.h>
#include <vector>
#include  "modelobj.h"

typedef struct
{
    GLfloat posX,posY,posZ;
    GLfloat rotX,rotY,rotZ;
    QPoint  lastPos;
}
Camera_t;

class GLWin : public QGLWidget
{
    Q_OBJECT
    
public:
    GLWin(QWidget *parent = 0);
    ~GLWin();
    void keyPressEvent(QKeyEvent *ke) override;
    void paintModelFromFile(const QString filePath);

public slots:
    void setDirectionalLightMode(const bool isDirectional);
    void setXRotation(int xAngle);
    void setYRotation(int yAngle);
    void setZRotation(int zAngle);
    void setScale(int scaleFactor);
    void setLightIntensity(int intensity);
    void setLightZPosition(int zPosition);
    void setLightYPosition(int yPosition);
    void setLightXPosition(int xPosition);
    void setAmbientLightR(double value);
    void setAmbientLightG(double value);
    void setAmbientLightB(double value);
    void setDiffuseLightR(double value);
    void setDiffuseLightG(double value);
    void setDiffuseLightB(double value);
    void setSpecularLightR(double value);
    void setSpecularLightG(double value);
    void setSpecularLightB(double value);

    void setCameraXPosition(int xPosition);
    void setCameraYPosition(int yPosition);
    void setCameraZPosition(int zPosition);

    void setModelXPosition(int xPosition);
    void setModelYPosition(int yPosition);
    void setModelZPosition(int zPosition);
private:
    void drawFloorGrid(float size, float step);
    void drawAxis(GLfloat axisLength);

private slots:
    void wheelEvent(QWheelEvent *event) override;
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    GLuint paintMdl();
    ModelObj *model;
    vtxArray vtxArr;
    QTimer *timer;
    ushort iRot;
    float m_xRot;
    float m_yRot;
    float m_zRot;
    GLuint idx;
    GLfloat xTra, yTra, zTra;
    GLuint fov;
    GLdouble zN;
    GLdouble zF;
    GLboolean shadingMode;
    GLfloat LightAmbient[4];
    GLfloat LightDiffuse[4];
    GLfloat LightSpecular[4];
    GLfloat LightPosition[4];
    GLfloat CameraPosition[3];
    GLfloat m_lightIntensity;
    bool m_isDirectionalLight;
    bool wireFrameMode;
    float scale, s0;
    void lights();
    GLuint m_gridLenght;
    GLuint vao;
    Camera_t m_camera;
    void setFrustum(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
};

#endif // GLWIN_H
