#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "screenlock.h"

int mouseState = 0;
int videoState = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//Initializes QMediaPlayer and QVideWidget
    ui->setupUi(this);
    videoPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget;
//Plays video on the same application window instead of opening a new one.
    layout = new QVBoxLayout();
    layout -> addWidget(videoWidget);
    ui->groupBox->setLayout(layout);
//Sets the video output widget and plays it.
    videoPlayer->setVideoOutput(videoWidget);
    videoWidget->show();
    ui->pushButton_2->setIcon(QIcon("C:/Users/norou/Desktop/pauseButton.png"));

}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//Gets file path of the video from the user and adds it to the video player.
    QString filePath = QFileDialog::getOpenFileName();
    videoPlayer->setSource(QUrl::fromLocalFile(filePath));
    videoPlayer->play();
//Updates video progress slider as video is playing.
    connect(videoPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::modifyMilliseconds);
    connect(videoPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::videoStatus);
}

void MainWindow::modifyMilliseconds()
{
 //Converts milliseconds to slider position. Slider also does not update along with the video if the mouse is pressed down on it.
    if(mouseState == 0)
    {
    ui-> horizontalSlider ->setValue((videoPlayer->position())*100/(videoPlayer->duration()));
    }
//Disables screenlock on iOS while the video is playing
#if defined(Q_OS_IOS)
    ScreenLock::setDisabled(true);
#endif
}

void MainWindow::videoStatus()
{
    //Enables screenlock if the video status changes (video paused, ended, etc)
    #if defined(Q_OS_IOS)
        ScreenLock::setDisabled(false);
    #endif
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
//Restarts the video if it is over
    if(videoPlayer -> hasVideo())
    {
    if(videoPlayer -> position() == videoPlayer -> duration())
    {
    videoPlayer->play();
    }
//Changes video position if user moves the slider
    double num = (double)position / 100;
    videoPlayer -> pause();
    videoPlayer-> setPosition((videoPlayer->duration())*num);
    }
}



void MainWindow::on_horizontalSlider_sliderPressed()
{
    //Checks if mouse is down on slider. The video will pause and set position according to slider's relative position.
    mouseState = 1;
}


void MainWindow::on_horizontalSlider_sliderReleased()
{
//The video will resume playing when the slider is released if it is not paused.
    mouseState = 0;
    if(videoPlayer -> position() != videoPlayer -> duration())
    {
    if(videoState == 0)
    {
    videoPlayer->play();
    }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
 //Controls for pausing the video and changing icons.
    if(videoPlayer -> hasVideo())
    {
    if(videoState == 0)
    {
        videoPlayer->pause();
        videoState = 1;
        ui->pushButton_2->setIcon(QIcon("C:/Users/norou/Desktop/playButton.png"));
    }
    else
    {
        videoPlayer->play();
        videoState = 0;
        ui->pushButton_2->setIcon(QIcon("C:/Users/norou/Desktop/pauseButton.png"));
    }
    }

}

