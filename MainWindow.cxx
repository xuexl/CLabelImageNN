#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include<QString>
#include<QLabel>

#include<io.h>
#include<vector>

#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

#include"Config.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)    
{
    ui->setupUi(this);
    
    connect(ui->lw_images, &QListWidget::itemClicked, [this](auto item){
        this->showImage(item->text().toStdString());
    });
    
    this->getImageList();
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getImageList()
{    
    intptr_t handle = 0;
    struct _finddata_t fileinfo;
    std::string path = Config::imageDirectory;
    std::string tmp;    
    std::vector<std::string> files;
    
    if((handle = _findfirst(tmp.assign(path).append("\\*.jpg").c_str(), &fileinfo)) != -1)
    {        
        do
        {
            if(fileinfo.attrib & _A_ARCH)
            {
                files.emplace_back(fileinfo.name);                      
            }
        }while(_findnext(handle, &fileinfo) == 0);
        _findclose(handle);
        //        
        for(auto &f: files)
        {        
            this->ui->lw_images->addItem(new QListWidgetItem(f.c_str()));
        }       
    }
    
}

void MainWindow::showImage(std::string fileName)
{
    std::string tmp;    
    
    auto img = cv::imread(tmp.assign(Config::imageDirectory).append("\\").append(fileName));
    cv::cvtColor(img, img, CV_BGR2RGB);
    QImage qImg = QImage(static_cast<const uchar*>(img.data), img.cols, img.rows, img.cols * img.channels(), QImage::Format_RGB888);
    
    ui->lb_view->setPixmap(QPixmap::fromImage(qImg));
}
