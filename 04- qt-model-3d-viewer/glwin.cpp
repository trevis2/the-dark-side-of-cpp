#include "glwin.h"

GLWin::GLWin(QWidget *parent)
    : QGLWidget(parent)
{
    wireFrameMode = false;
    scale = 1.0f;
    s0 = 1.001f;
    xTra = 0;
    yTra = 0;
    zTra = 0;
    iRot = 0;
    m_xRot = 0;
    m_yRot = 0;
    m_zRot = 0;
    shadingMode = true;//true is SMOOTH
    fov = 45;// Field of view in degrees
    zN = 5;  //near Z near
    zF = 100;// Z far
    LightAmbient[0] = 1.0f; // R
    LightAmbient[1] = 1.0f;  // G
    LightAmbient[2] = 1.0f;  // B
    LightAmbient[3] = 1.0f;

    LightDiffuse[0] = 1.0f; // R Shadows
    LightDiffuse[1] = 1.0f; // G
    LightDiffuse[2] = 1.0f; // B
    LightDiffuse[3] = 1.0f;

    LightSpecular[0] = 1.0f; // R Shadows
    LightSpecular[1] = 1.0f; // G
    LightSpecular[2] = 1.0f; // B
    LightSpecular[3] = 1.0f;

    LightPosition[0] = 0.0f; // X
    LightPosition[1] = 0.0f; // Y
    LightPosition[2] = 1.5f; // Z
    LightPosition[3] = 1.0f;

    resize(500,500);//window size
    model = new ModelObj();
    model->updateModelSourceFile(QString(":/Models/Patrick.obj"));
    idx = 0;

    timer = new QTimer(this);
    timer->start(20);//50 fps

    //connectors
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
}
GLWin::~GLWin()
{
    glDeleteLists(idx, 1);
}
void GLWin::initializeGL()
{
    qglClearColor(Qt::blue);
    idx = paintMdl();
    //glClearDepth( 1.0f );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LEQUAL );
    glEnable (GL_LIGHTING); //enable the lighting
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.3);
    glEnable(GL_LIGHT0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    glShadeModel(GL_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
    glEnable(GL_POLYGON_SMOOTH);
}
void GLWin::resizeGL(int nWidth, int nHeight)
{
    GLdouble ratio = nWidth/nHeight; //aspect ratio
    GLdouble t = tan((fov*M_PI)/360.0)*zN;
    GLdouble b = -t;
    GLdouble l = ratio*b;
    GLdouble r = -l;
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(l, r, b, t, zN, zF);
    glTranslatef(0.0, 0.0, -20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWin::lights()
{
  using namespace std;
  glEnable(GL_LIGHTING);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT0,GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR,LightSpecular);
}

void GLWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    paintMdl();
    glTranslatef(xTra, yTra, zTra);
    glRotatef(iRot, 1.0, 0.0, 0.0);
    glRotatef(m_xRot, 1.0, 0.0, 0.0);
    glRotatef(m_yRot, 0.0, 1.0, 0.0);
    glRotatef(m_zRot, 0.0, 0.0, 1.0);
    glScalef(scale, scale, scale);
    lights();
    glCallList(idx);
}

void GLWin::keyPressEvent(QKeyEvent *ke)
{
    qDebug() << Q_FUNC_INFO;
    switch (ke->key())
    {
    case Qt::Key_S:
        if(shadingMode) {
            glEnable (GL_LIGHTING);
            shadingMode = false;
        }
        else {
            glDisable(GL_LIGHTING);
            shadingMode = true;
        }
        break;
    case Qt::Key_1:
        iRot=iRot+1;
        break;
    case Qt::Key_2:
        iRot=iRot-1;
        break;
    case Qt::Key_Up:
        yTra=yTra-0.2;
        break;
    case Qt::Key_Down:
        yTra=yTra+0.2;
        break;
    case Qt::Key_Left:
        xTra=xTra-0.2;
        break;
    case Qt::Key_Right:
        xTra=xTra+0.2;
        break;
    case Qt::Key_W:
        wireFrameMode = !wireFrameMode;
        if(wireFrameMode == true) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        break;
//        GLuint image = loadBMP_custom("./my_texture.bmp");
    case Qt::Key_Comma:
        zTra=zTra-0.2;
        break;
    case Qt::Key_Period:
        zTra=zTra+0.2;
        break;
    case Qt::Key_M:{
        model->updateModelSourceFile(QString(":/Models/suzanne.obj"));
        idx = paintMdl();
        break;
        }
    case Qt::Key_P:{
        // Turn on wireframe mode
        model->updateModelSourceFile(QString(":/Models/Patrick.obj"));
        idx = paintMdl();
        break;
        }
    }
}

GLuint GLWin::paintMdl()
{
    GLuint list;
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    qglColor(Qt::red);
    glBegin(GL_TRIANGLES);
    faceArray faces = model->GetFaces();
    uint facesNum = faces.size();
    vtxArray vetices = model->GetVertices();

    for(uint i=0;i<facesNum;i++) {
        face curFace = faces.at(i);
        vertex v1 = vetices.at((curFace.x-1));
        vertex v2 = vetices.at((curFace.y-1));
        vertex v3 = vetices.at((curFace.z-1));
        //calculating normal
        glNormal3f(((v2.y-v1.y)*(v3.z-v1.z))-((v3.y-v1.y)*(v2.z-v1.z)), ((v2.x-v1.x)*(v3.z-v1.z))-((v3.x-v1.x)*(v2.z-v1.z)), ((v2.x-v1.x)*(v3.y-v1.y))-((v3.x-v1.x)*(v2.y-v1.y)));
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd();
    glEndList();
    return list;
}

void GLWin::paintModelFromFile(const QString filePath) {
    model->updateModelSourceFile(filePath);
    idx = paintMdl();
}

void GLWin::wheelEvent(QWheelEvent *event)
{
    scale *= 1 + event->delta() * (s0 - 1);
    update();
}

void GLWin::setXRotation(int xAngle) {
    m_xRot = static_cast<float>(xAngle);
    update();
}

void GLWin::setYRotation(int yAngle)
{
    m_yRot = static_cast<float>(yAngle);
    update();
}

void GLWin::setZRotation(int zAngle)
{
    m_zRot = static_cast<float>(zAngle);
    update();
}

void GLWin::setLightIntensity(int intensity) {
    qDebug() << "setLightIntensity" << intensity;
    LightPosition[3] = static_cast<float>(intensity);
    update();
}

void GLWin::setLightXPosition(int xPosition) {
    qDebug() << "setLightXPosition" << xPosition;
    LightPosition[0] = static_cast<float>(xPosition);
    update();
}

void GLWin::setAmbientLightR(double value)
{
    LightAmbient[0] = static_cast<float>(value); // R
}

void GLWin::setAmbientLightG(double value)
{
    LightAmbient[1] = static_cast<float>(value); // G
}
void GLWin::setAmbientLightB(double value)
{
    LightAmbient[2] = static_cast<float>(value); // B

}

void GLWin::setDiffuseLightR(double value)
{
    LightDiffuse[0] = static_cast<float>(value); // R
}

void GLWin::setDiffuseLightG(double value)
{
    LightDiffuse[1] = static_cast<float>(value); // G
}
void GLWin::setDiffuseLightB(double value)
{
    LightDiffuse[2] = static_cast<float>(value); // B

}

void GLWin::setSpecularLightR(double value)
{
    LightSpecular[0] = static_cast<float>(value); // R
}

void GLWin::setSpecularLightG(double value)
{
    LightSpecular[1] = static_cast<float>(value); // G
}
void GLWin::setSpecularLightB(double value)
{
    LightSpecular[2] = static_cast<float>(value); // B

}
void GLWin::setLightYPosition(int yPosition) {
    qDebug() << "setLightYPosition" << yPosition;
    LightPosition[1] = static_cast<float>(yPosition);
    update();
}
void GLWin::setLightZPosition(int zPosition) {
    qDebug() << "setLightZPosition" << zPosition;
    LightPosition[2] = static_cast<float>(zPosition);
    update();
}

void GLWin::setScale(double scaleFactor) {
    float scaleFloat = static_cast<float>(scaleFactor);
    glScalef(scaleFloat, scaleFloat, scaleFloat);
    update();
}
