#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void initModelControls();
    void initLights();
public slots:
    void keyPressEvent(QKeyEvent *ke);
    void onBtnLoadModelClicked();
private slots:
    void hideControls();
    void updateTabContent();
};

#endif // MAINWINDOW_H
