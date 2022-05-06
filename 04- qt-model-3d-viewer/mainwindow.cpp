#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLoadModel, &QPushButton::released, this, &MainWindow::onBtnLoadModelClicked);
//    connect(ui->xAngleSlider, &QSlider::valueChanged ,[this](int value){
//        ui->xLabel->setText(QString("X Rotation value:") + QString::number(value));
//        ui->openGLWidget->setXRotation(value);
//    });
    connect(ui->xAngleSlider, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setXRotation);
    connect(ui->yAngleSlider, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setYRotation);
    connect(ui->zAngleSlider, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setZRotation);
    connect(ui->sb_scale, qOverload<double>(&QDoubleSpinBox::valueChanged), ui->openGLWidget, &GLWin::setScale);
    connect(ui->lightIntensitySlider, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setLightIntensity);
    connect(ui->lightXpositionSlider, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setLightXPosition);
    connect(ui->lightYpositionSlider, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setLightYPosition);
    connect(ui->lightZPositionSlider, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setLightZPosition);
    connect(ui->slAmbientR, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setAmbientLightR);
    connect(ui->slAmbientG, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setAmbientLightG);
    connect(ui->slAmbientB, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setAmbientLightB);
    connect(ui->slDiffuseR, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setDiffuseLightR);
    connect(ui->slDiffuseG, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setDiffuseLightG);
    connect(ui->slDiffuseB, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setDiffuseLightB);
    connect(ui->slSpecularR, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setSpecularLightR);
    connect(ui->slSpecularG, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setSpecularLightG);
    connect(ui->slSpecularB, &QSlider::valueChanged, ui->openGLWidget, &GLWin::setSpecularLightB);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *ke) {
    qDebug() << Q_FUNC_INFO;
     ui->openGLWidget->keyPressEvent(ke);
}

void MainWindow::onBtnLoadModelClicked() {
    qDebug() << Q_FUNC_INFO;
    QString filePath = QFileDialog::getOpenFileName(this, "Load ASCII .stl model", QString(), "STL Files (*.stl)");
    if( QFile(filePath).exists() == true ) {
        ui->openGLWidget->paintModelFromFile(filePath);
    }
}
