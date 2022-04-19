#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLoadModel, &QPushButton::released, this, &MainWindow::onBtnLoadModelClicked);
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
    QString filePath = "";
    if( QFile(filePath).exists() == true ) {
        ui->openGLWidget->paintModelFromFile(filePath);
    }
}
