#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <Windows.h>
#include <QLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void modifyMilliseconds();
    void videoStatus();


    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_sliderReleased();

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    QMediaPlayer *videoPlayer;
    QVideoWidget *videoWidget;
    QVBoxLayout *layout;
};


#endif // MAINWINDOW_H
