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

class GLWin : public QGLWidget
{
    Q_OBJECT
    
public:
    GLWin(QWidget *parent = 0);
    ~GLWin();
    void keyPressEvent(QKeyEvent *ke);
    void paintModelFromFile(const QString filePath);
private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    GLuint paintMdl();
    ModelObj *model;
    vtxArray vtxArr;
    QTimer *timer;
    ushort iRot;
    GLuint idx;
    GLfloat xTra, yTra, zTra;
    GLuint fov;
    GLdouble zN;
    GLdouble zF;
    GLboolean shadingMode;
    GLfloat LightAmbient[4];
    GLfloat LightDiffuse[4];
    GLfloat LightPosition[4];
    bool wireFrameMode;
};

#endif // GLWIN_H
