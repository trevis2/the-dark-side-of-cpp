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
     * @details This method intercept keyboard button pressed event.
     * @param IN::ke keyboard event.
     */
    void keyPressEvent(QKeyEvent *ke) override;

    /**
     * @details This method requests 3d model painting providing a 3d model file path.
     * @param In::filePath 3d model file path.
     */
    void paintModelFromFile(const QString filePath);

public slots:

    /**
     * @details This method sets ambient light mode
     * @param IN::isDirectional Directional light mode flag
     */
    void setDirectionalLightMode(const bool isDirectional);

    /**
     * @details This method returns directional light mode flag value.
     * @return True if ambient light mode is directional.
     */
    inline bool directionalLightMode() const { return m_isDirectionalLight; }

    /**
     * @details This method sets X axis rotation value.
     * @param IN::xAngle Rotation angle value
     */
    void setXRotation(int xAngle);

    /**
     * @details This method returns X axis rotation value.
     * @return X axis Rotation angle value
     */
    inline int modelXRotation() const { return qRound(m_xRot); }

    /**
     * @details This method sets Y axis rotation value.
     * @param IN::yAngle Rotation angle value
     */
    void setYRotation(int yAngle);

    /**
     * @details This method returns Y axis rotation value.
     * @return Y axis Rotation angle value
     */
    inline int modelYRotation() const { return qRound(m_yRot);}

    /**
     * @details This method sets Z axis rotation value.
     * @param IN::zAngle Rotation angle value
     */
    void setZRotation(int zAngle);

    /**
     * @details This method returns Z axis rotation value.
     * @return Z axis Rotation angle value
     */
    inline int modelZRotation() const { return qRound(m_zRot);}

    /**
     * @details This method sets 3d model scale factor.
     * @param 3D model scale factor.
     */
    void setScale(int scaleFactor);

    /**
     * @details This method returns 3d model scale factor.
     * @return 3d model scale factor.
     */
    int scaleFactor() const {return static_cast<int>(scale * 10.0f);}

    /**
     * @details This method sets light intensity.
     * @param Light intensity value.
     */
    void setLightIntensity(int intensity);

    /**
     * @details This method sets light x position.
     * @param Light x position.
     */
    void setLightXPosition(int xPosition);

    /**
     * @details This method sets light y position.
     * @param Light y position.
     */
    void setLightYPosition(int yPosition);

    /**
     * @details This method sets light z position.
     * @param Light z position.
     */
    void setLightZPosition(int zPosition);

    /**
     * @details This method sets ambient light red component.
     * @param Ambient light red component intensity.
     */
    void setAmbientLightR(double value);

    /**
     * @details This method sets ambient light green component.
     * @param Ambient light green component intensity.
     */
    void setAmbientLightG(double value);

    /**
     * @details This method sets ambient light blue component.
     * @param Ambient light blue component intensity.
     */
    void setAmbientLightB(double value);

    /**
     * @details This method sets diffuse light red component.
     * @param Diffuse light red component intensity.
     */
    void setDiffuseLightR(double value);

    /**
     * @details This method sets diffuse light green component.
     * @param Diffuse light green component intensity.
     */
    void setDiffuseLightG(double value);

    /**
     * @details This method sets diffuse light blue component.
     * @param Diffuse light blue component intensity.
     */
    void setDiffuseLightB(double value);

    /**
     * @details This method sets specular light red component.
     * @param Specular light red component intensity.
     */
    void setSpecularLightR(double value);

    /**
     * @details This method sets specular light green component.
     * @param Specular light green component intensity.
     */
    void setSpecularLightG(double value);

    /**
     * @details This method sets specular light blue component.
     * @param Specular light blue component intensity.
     */
    void setSpecularLightB(double value);

    /**
     * @details This method sets camera x position.
     * @param Camera x position.
     */
    void setCameraXPosition(int xPosition);

    /**
     * @details This method sets camera y position.
     * @param Camera y position.
     */
    void setCameraYPosition(int yPosition);

    /**
     * @details This method sets camera z position.
     * @param Camera z position.
     */
    void setCameraZPosition(int zPosition);

    /**
     * @details This method sets model x position.
     * @param Model x position.
     */
    void setModelXPosition(int xPosition);

    /**
     * @details This method returns model x position.
     * @return Model x position.
     */
    inline int modelXPosition() const {return static_cast<int>(xTra);}

    /**
     * @details This method sets model y position.
     * @param Model y position.
     */
    void setModelYPosition(int yPosition);

    /**
     * @details This method returns model y position.
     * @return Model y position.
     */
    inline int modelYPosition() const {return static_cast<int>(yTra);}

    /**
     * @details This method sets model z position.
     * @param Model z position.
     */
    void setModelZPosition(int zPosition);

    /**
     * @details This method returns model z position.
     * @return Model z position.
     */
    inline int modelZPosition() const {return static_cast<int>(zTra);}

private:
    /**
     * @details This method draws plane grid.
     * @param IN::size size of grid plane
     * @param IN::step grid step
     */
    void drawFloorGrid(float size, float step);

    /**
     * @details This method draws axis.
     * @param IN::axisLength Length of axis line.
     */
    void drawAxis(GLfloat axisLength);

private slots:
    /**
     * @details This method intercepts mouse wheel events.
     * @param IN::event Wheel event.
     */
    void wheelEvent(QWheelEvent *event) override;
private:

    /**
     * @details This method initializes opengl view.
     */
    void initializeGL() override;
    /**
     * @details This method handles opengl view resize events
     * @param IN::w View width
     * @param IN::h View height
     */
    void resizeGL(int w, int h) override;

    /**
     * @details This method paints opengl content into view
     */
    void paintGL() override;

    /**
     * @details This method applies camera parameters to opengl scene.
     * @param IN::fovY Vertical field of view.
     * @param IN::aspect scene aspect ratio.
     * @param IN::zNear The camera's near depth limit.
     * @param In::zFar The camera’s far depth limit.
     */
    void setFrustum(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);

 private:
    /**
     * @details This method paints 3d model into opengl view.
     * @return id of model rendered.
     */
    GLuint paintMdl();

    /**
     * @details This method turns on lights into 3d model scene.
     */
    void lights();

 private:
    BaseModel *model;                   /** 3d Model reference **/
    vtxArray vtxArr;                    /** 3d Model vertices array **/
    QTimer *timer;                      /** Opengl content update timer **/
    ushort iRot;                        /** Automatic rotation angle **/
    float m_xRot;                       /** X axis rotation angle **/
    float m_yRot;                       /** Y axis rotation angle **/
    float m_zRot;                       /** Z axis rotation angle **/
    GLuint idx;                         /** Model id **/
    GLfloat xTra, yTra, zTra;           /** X,Y,Z model translation value **/
    GLuint fov;                         /** Field of view **/
    GLdouble zN;                        /** Camera zNear **/
    GLdouble zF;                        /** Camera zFar **/
    GLboolean shadingMode;              /** Opengl view shading mode **/
    GLfloat LightAmbient[4];            /** Ambient light parameters **/
    GLfloat LightDiffuse[4];            /** Diffuse light parameters**/
    GLfloat LightSpecular[4];           /** Specular light parameters**/
    GLfloat LightPosition[4];           /** Light position parameters**/
    GLfloat CameraPosition[3];          /** Camera position parameters**/
    GLfloat m_lightIntensity;           /** Light intensity **/
    float m_lastDiffuseR = 0.0f ;       /** Last diffuse Red component value **/
    float m_lastDiffuseG = 0.0f;        /** Last diffuse Green component value **/
    float m_lastDiffuseB = 0.0f;        /** Last diffuse Blue component value **/
    bool m_isDirectionalLight;          /** Directional light mode flag **/
    bool wireFrameMode;                 /** Wireframe mode flag **/
    float scale, s0;                    /** Scaling parameters **/
    GLuint m_gridLenght;                /** Grid lenght **/
    GLuint vao;                         /** Vertices array object**/
    Camera_t m_camera;                  /** Opengl view camera **/

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
