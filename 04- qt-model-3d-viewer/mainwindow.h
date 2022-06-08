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
    /**
     * @details This method initializes 3D model parameters applying default values.
     */
    void initModelControls();

    /**
     * @details This method initializes scene lights.
     */
    void initLights();

public slots:
    /**
     * @details This method intercept all key events.
     * @param IN::ke Key event to process.
     */
    void keyPressEvent(QKeyEvent *ke);

    /**
     * @details This method handles load new model request.
     */
    void onBtnLoadModelClicked();

private slots:
    /**
     * @details This method handles hide/show GUI control request.
     */
    void hideControls();

    /**
     * @details This method updates tab widget content according to selected tab index.
     */
    void updateTabContent();
};

#endif // MAINWINDOW_H
