#include "openglview.h"
#ifdef Q_OS_WIN32
#include <GL/glu.h>
#else
#include <OpenGL/glu.h>
#endif

OpenGLView::OpenGLView(QWidget *parent)
    : QGLWidget(parent)
{
    m_intVal = 0;
    wireFrameMode = false;
    scale = 1.0f;
    s0 = 1.001f;
    xTra = 0.0f;
    yTra = 0.0f;
    zTra = 0.0f;
    iRot = 0;
    m_xRot = 0;
    m_yRot = 0;
    m_zRot = 0;
    m_lightIntensity = 1.0f;
    shadingMode = true;//true is SMOOTH
    fov = 45;// Field of view in degrees
    zN = 0.5;  //near Z near
    zF = 50.0;// Z far

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

    m_camera.rotX=18.50;
    m_camera.rotY=-45.0;
    m_camera.rotZ=  0.0;
    m_camera.posX = 0.0f;
    m_camera.posY = 0.0f;
    m_camera.posZ=-7.0;

    resize(500,500);//window size
    model = nullptr;
//    model = new ModelObj();
    modelStl = new ModelStl();
//    model->updateModelSourceFile(QString(":/Models/Patrick.obj"));
//    modelStl->updateModelSourceFile(QString(":/Models/Darth.stl"));
//    modelStl->updateModelSourceFile(QString(":/Models/cube.stl"));
    modelStl->updateModelSourceFile(QString(":/Models/holecube.stl"));
//    modelStl->updateModelSourceFile(QString(":/Models/eyeball.stl"));
    idx = 0;

    timer = new QTimer(this);
    timer->start(20);//50 fps

    //connectors
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
}

OpenGLView::~OpenGLView()
{
    glDeleteLists(idx, 1);
}

void OpenGLView::initializeGL()
{
//    qglClearColor(Qt::blue);
    qglClearColor(QColor(32,32,32));
    glClearDepth( 1.0f );
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_LIGHTING); //enable the lighting
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.3);
    glEnable(GL_LIGHT0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
    glEnable(GL_POLYGON_SMOOTH);
}

void OpenGLView::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
    float aspectRatio = (float)nWidth / (float)nHeight;
    GLdouble t = tan((fov*M_PI)/360.0)*zN;
    GLdouble b = -t;
    GLdouble l = aspectRatio*b;
    GLdouble r = -l;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(l, r, b, t, zN, zF);
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLView::drawFloorGrid(float size, float step)
{
    glBegin(GL_LINES);

    glColor3f(0.3f, 0.3f, 0.3f);
    for(float i=step; i <= size; i+= step)
    {
        glVertex3f(-size, 0,  i);   // lines parallel to X-axis
        glVertex3f( size, 0,  i);
        glVertex3f(-size, 0, -i);   // lines parallel to X-axis
        glVertex3f( size, 0, -i);

        glVertex3f( i, 0, -size);   // lines parallel to Z-axis
        glVertex3f( i, 0,  size);
        glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
        glVertex3f(-i, 0,  size);
    }

    // x-axis
    glColor3f(0.5f, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f( size, 0, 0);

    // z-axis
    glColor3f(0,0,0.5f);
    glVertex3f(0, 0, -size);
    glVertex3f(0, 0,  size);

    glEnd();
}

void OpenGLView::drawAxis(GLfloat axisLength)
{
    GLfloat offset=0;

    glLineWidth(3.0);

    glBegin(GL_LINES);
    qglColor(Qt::red);
    glVertex3f(offset,offset,offset);
    glVertex3f(axisLength,offset,offset);
    glEnd();

    glBegin(GL_LINES);
    qglColor(Qt::green);
    glVertex3f(offset,offset,offset);
    glVertex3f(offset,axisLength,offset);
    glEnd();

    glBegin(GL_LINES);
    qglColor(Qt::blue);
    glVertex3f(offset,offset,offset);
    glVertex3f(offset,offset,axisLength);
    glEnd();

    glLineWidth(1.0);
}

void OpenGLView::lights()
{
  glLightfv(GL_LIGHT0,GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR,LightSpecular);
}

void OpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera
    glTranslatef(m_camera.posX, m_camera.posY, m_camera.posZ);
    glRotatef(m_camera.rotX, 1.0, 0.0, 0.0);
    glRotatef(m_camera.rotY, 0.0, 1.0, 0.0);
    glRotatef(m_camera.rotZ, 0.0, 0.0, 1.0);

    drawFloorGrid(4.0,0.5);
    drawAxis(1.0);


    idx = paintMdl();

    glTranslatef(xTra, yTra, zTra);
    glRotatef(iRot, 1.0, 0.0, 0.0);
    glRotatef(m_xRot, 1.0, 0.0, 0.0);
    glRotatef(m_yRot, 0.0, 1.0, 0.0);
    glRotatef(m_zRot, 0.0, 0.0, 1.0);
    glScalef(scale, scale, scale);

    lights();

    glCallList(idx);
}

void OpenGLView::keyPressEvent(QKeyEvent *ke)
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

GLuint OpenGLView::paintMdl()
{
    GLuint list;
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    qglColor(Qt::gray);
    glBegin(GL_TRIANGLES);
    faceArray faces;
    uint facesNum;
    vtxArray vertices;
    if (model != nullptr) {
        faces = model->GetFaces();
        facesNum = faces.size();
        vertices = model->GetVertices();
        for(uint i=0;i<facesNum;i++) {
            face curFace = faces.at(i);
            vertex v1 = vertices.at((curFace.x-1));
            vertex v2 = vertices.at((curFace.y-1));
            vertex v3 = vertices.at((curFace.z-1));
            //calculating normal
            glNormal3f(((v2.y-v1.y)*(v3.z-v1.z))-((v3.y-v1.y)*(v2.z-v1.z)), ((v2.x-v1.x)*(v3.z-v1.z))-((v3.x-v1.x)*(v2.z-v1.z)), ((v2.x-v1.x)*(v3.y-v1.y))-((v3.x-v1.x)*(v2.y-v1.y)));
            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
            glVertex3f(v3.x, v3.y, v3.z);
        }
    } else if (modelStl != nullptr) {
        faces = modelStl->GetFaces();
        facesNum = faces.size();
        vertices = modelStl->GetVertices();
        vtxArray normals = modelStl->GetNormals();
        for(uint i=0;i < facesNum;i++) {
            face curFace = faces.at(i);
            vertex v1 = vertices.at((curFace.x-1));
            vertex v2 = vertices.at((curFace.y-1));
            vertex v3 = vertices.at((curFace.z-1));
            glNormal3f(normals.at(i).x, normals.at(i).y, normals.at(i).z);
            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
            glVertex3f(v3.x, v3.y, v3.z);
        }
    }

    glEnd();
    glEndList();
    return list;
}

void OpenGLView::paintModelFromFile(const QString filePath) {
    model->updateModelSourceFile(filePath);
    idx = paintMdl();
}

void OpenGLView::wheelEvent(QWheelEvent *event)
{
    scale *= 1 + event->delta() * (s0 - 1);
    update();
    emit scaleChanged();
}

void OpenGLView::setXRotation(int xAngle) {
    if(xAngle != qRound(m_xRot)) {
        m_xRot = static_cast<float>(xAngle);
        update();
        emit modelXRotationChanged();
    }
}

void OpenGLView::setYRotation(int yAngle)
{
    m_yRot = static_cast<float>(yAngle);
    update();
    emit modelYRotationChanged();
}

void OpenGLView::setZRotation(int zAngle)
{
    m_zRot = static_cast<float>(zAngle);
    update();
    emit modelZRotationChanged();
}

void OpenGLView::setLightIntensity(int intensity) {
    m_lightIntensity = static_cast<float>(intensity);
    LightDiffuse[0] = m_lightIntensity *  m_lastDiffuseR;
    LightDiffuse[1] = m_lightIntensity *  m_lastDiffuseG;
    LightDiffuse[2] = m_lightIntensity *  m_lastDiffuseB;
    update();
}

void OpenGLView::setAmbientLightR(double value)
{
    LightAmbient[0] = static_cast<float>(value/255.0f); // R
    update();
}

void OpenGLView::setAmbientLightG(double value)
{
    LightAmbient[1] = static_cast<float>(value/255.0f); // G
    update();
}
void OpenGLView::setAmbientLightB(double value)
{
    LightAmbient[2] = static_cast<float>(value/255.0f); // B
    update();
}

void OpenGLView::setDiffuseLightR(double value)
{
    m_lastDiffuseR = static_cast<float>(value/255.0f); // R
    LightDiffuse[0] = m_lightIntensity *  m_lastDiffuseR;
    update();
}

void OpenGLView::setDiffuseLightG(double value)
{
    m_lastDiffuseG = static_cast<float>(value/255.0f); // G
    LightDiffuse[1] = m_lightIntensity *  m_lastDiffuseG;

    update();
}
void OpenGLView::setDiffuseLightB(double value)
{
    m_lastDiffuseB = static_cast<float>(value/255.0f); // B
    LightDiffuse[2] = m_lightIntensity *  m_lastDiffuseB;

    update();
}

void OpenGLView::setSpecularLightR(double value)
{
    LightSpecular[0] = static_cast<float>(value/255.0f); // R
    update();
}

void OpenGLView::setSpecularLightG(double value)
{
    LightSpecular[1] = static_cast<float>(value/255.0f); // G
    update();
}
void OpenGLView::setSpecularLightB(double value)
{
    LightSpecular[2] = static_cast<float>(value/255.0f); // B
    update();
}

void OpenGLView::setLightXPosition(int xPosition) {
    LightPosition[0] = static_cast<float>(xPosition);
    update();
}

void OpenGLView::setLightYPosition(int yPosition) {
    LightPosition[1] = static_cast<float>(yPosition);
    update();
}
void OpenGLView::setLightZPosition(int zPosition) {
    LightPosition[2] = static_cast<float>(zPosition);
    update();
}


void OpenGLView::setCameraXPosition(int xPosition) {
    m_camera.posX = static_cast<float>(xPosition);
    update();
}

void OpenGLView::setCameraYPosition(int yPosition) {
    m_camera.posY = static_cast<float>(yPosition);
    update();
}
void OpenGLView::setCameraZPosition(int zPosition) {
    m_camera.posZ = static_cast<float>(zPosition);
    update();
}
void OpenGLView::setScale(int scaleFactor) {
    scale = static_cast<float>(scaleFactor/10.0f);
    update();
    emit scaleChanged();
}

void OpenGLView::setDirectionalLightMode(const bool isDirectional) {
    LightPosition[3] = isDirectional == true ? 0.0f : 1.0f ;
    update();
}


void OpenGLView::setModelXPosition(int xPosition) {
    xTra = static_cast<float>(xPosition);
    update();
    emit modelXPositionChanged();
}

void OpenGLView::setModelYPosition(int yPosition) {
    yTra = static_cast<float>(yPosition);
    update();
    emit modelYPositionChanged();
}
void OpenGLView::setModelZPosition(int zPosition) {
    zTra = static_cast<float>(zPosition);
    update();
    emit modelZPositionChanged();
}
