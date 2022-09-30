#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLoadModel, &QPushButton::released, this, &MainWindow::onBtnLoadModelClicked);

    connect(ui->xAngleSlider, &QSlider::valueChanged,this, [this](int value) {
        ui->xLabel->setText(QString("X Rotation value: %1").arg( QString::number(value)));
        ui->openGLWidget->setXRotation(value);
    });
    connect(ui->yAngleSlider, &QSlider::valueChanged,this, [this](int value) {
        ui->yLabel->setText(QString("Y Rotation value: %1").arg( QString::number(value)));
        ui->openGLWidget->setYRotation(value);
    });

    connect(ui->zAngleSlider, &QSlider::valueChanged, this, [this](int value) {
        ui->zLabel->setText(QString("Z Rotation value: %1").arg( QString::number(value)));
        ui->openGLWidget->setZRotation(value);
    });

    connect(ui->scaleSlider, &QSlider::valueChanged, this, [this](int value){
        ui->scaleLabel->setText(QString("Scale: ") + QString::number(value));
        ui->openGLWidget->setScale(value);
    });

    connect(ui->xPosSlider, &QSlider::valueChanged,  this, [this](int value){
        ui->xPositionLabel->setText(QString("X Position value:") + QString::number(value));
        ui->openGLWidget->setModelXPosition(value);
    });

    connect(ui->yPosSlider, &QSlider::valueChanged, this, [this](int value){
        ui->yPositionLabel->setText(QString("Y Position value:") + QString::number(value));
        ui->openGLWidget->setModelYPosition(value);
    });

    connect(ui->zPosSlider, &QSlider::valueChanged, this, [this](int value){
        ui->zPositionLabel->setText(QString("Z Position value:") + QString::number(value));
        ui->openGLWidget->setModelZPosition(value);
    });


    connect(ui->lightIntensitySlider, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setLightIntensity);
    connect(ui->lightXpositionSlider, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setLightXPosition);
    connect(ui->lightYpositionSlider, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setLightYPosition);
    connect(ui->lightZPositionSlider, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setLightZPosition);
    connect(ui->slAmbientR, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setAmbientLightR);
    connect(ui->slAmbientG, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setAmbientLightG);
    connect(ui->slAmbientB, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setAmbientLightB);
    connect(ui->slDiffuseR, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setDiffuseLightR);
    connect(ui->slDiffuseG, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setDiffuseLightG);
    connect(ui->slDiffuseB, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setDiffuseLightB);
    connect(ui->slSpecularR, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setSpecularLightR);
    connect(ui->slSpecularG, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setSpecularLightG);
    connect(ui->slSpecularB, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setSpecularLightB);
    connect(ui->cameraXSlider, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setCameraXPosition);
    connect(ui->cameraYSlider, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setCameraYPosition);
    connect(ui->cameraZSlider, &QSlider::valueChanged, ui->openGLWidget, &OpenGLView::setCameraZPosition);
    connect(ui->cbDirectionalLight, &QCheckBox::toggled,ui->openGLWidget,&OpenGLView::setDirectionalLightMode);
    connect(ui->actionHide_controls, &QAction::toggled, this , &MainWindow::hideControls);


    connect(ui->tabWidget->tabBar(), &QTabBar::currentChanged, this , &MainWindow::updateTabContent);
    ui->actionHide_controls->setChecked(true);
    initModelControls();
    initLights();
    hideControls();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::hideControls() {
    bool needToShow = !ui->actionHide_controls->isChecked();
    ui->tabWidget->setVisible(needToShow);
    if(needToShow == true) {
        ui->tabWidget->setCurrentIndex(0);
        updateTabContent();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ke) {
    qDebug() << Q_FUNC_INFO;
    switch (ke->key()) {
    case Qt::Key_C: {
        bool needToShow = !ui->actionHide_controls->isChecked();
        ui->actionHide_controls->setChecked(needToShow);
        break;
    }
    default:
        ui->openGLWidget->keyPressEvent(ke);
        break;
    }
}

void MainWindow::onBtnLoadModelClicked() {
    qDebug() << Q_FUNC_INFO;
    QString filePath = QFileDialog::getOpenFileName(this, "3D Model Files", QString(), "Model Files (*.stl *.obj)");
    if( QFile(filePath).exists() == true ) {
        ui->openGLWidget->paintModelFromFile(filePath);
    }
}

void MainWindow::initLights() {
    ui->openGLWidget->setAmbientLightR(255);
    ui->openGLWidget->setAmbientLightG(255);
    ui->openGLWidget->setAmbientLightB(255);

    ui->openGLWidget->setSpecularLightR(255);
    ui->openGLWidget->setSpecularLightG(255);
    ui->openGLWidget->setSpecularLightB(255);

    ui->openGLWidget->setDiffuseLightR(255);
    ui->openGLWidget->setDiffuseLightG(255);
    ui->openGLWidget->setDiffuseLightB(255);
}

void MainWindow::initModelControls() {
    ui->openGLWidget->setModelXPosition(0.0f);
    ui->xPositionLabel->setText(QString("X Position value:") + QString::number(0.0f));
    ui->openGLWidget->setModelYPosition(0.0f);
    ui->yPositionLabel->setText(QString("X Position value:") + QString::number(0.0f));
    ui->openGLWidget->setModelZPosition(0.0f);
    ui->zPositionLabel->setText(QString("X Position value:") + QString::number(0.0f));

    ui->openGLWidget->setXRotation(0.0f);
    ui->xLabel->setText(QString("X Rotation value: %1").arg( QString::number(0.0f)));
    ui->openGLWidget->setYRotation(0.0f);
    ui->yLabel->setText(QString("Y Rotation value: %1").arg( QString::number(0.0f)));
    ui->openGLWidget->setZRotation(0.0f);
    ui->zLabel->setText(QString("Z Rotation value: %1").arg( QString::number(0.0f)));

    ui->openGLWidget->setScale(10);
    ui->scaleLabel->setText(QString("Scale: ") + QString::number(10));
}

void MainWindow::updateTabContent() {
    qDebug()<< Q_FUNC_INFO;
    if ( ui->tabWidget->tabBar()->currentIndex() == 0 ) {
        ui->xAngleSlider->setValue(ui->openGLWidget->modelXRotation());
        ui->yAngleSlider->setValue(ui->openGLWidget->modelYRotation());
        ui->zAngleSlider->setValue(ui->openGLWidget->modelZRotation());
        ui->scaleSlider->setValue(ui->openGLWidget->scaleFactor());
        ui->xPosSlider->setValue(ui->openGLWidget->modelXPosition());
        ui->yPosSlider->setValue(ui->openGLWidget->modelYPosition());
        ui->zPosSlider->setValue(ui->openGLWidget->modelZPosition());
    } else if ( ui->tabWidget->tabBar()->currentIndex() == 1 ) {

    }
}
