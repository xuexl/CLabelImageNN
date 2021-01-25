#include "ImageViewer2.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <QGraphicsPixmapItem>
#include <QDebug>

#include"Config.h"


ImageViewer2::ImageViewer2(QWidget *parent)
    :QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    pixmapItem=new QGraphicsPixmapItem(pixmap);
    scene->addItem(pixmapItem);
    setScene(scene);
    scene->installEventFilter(this);
}

ImageViewer2::~ImageViewer2()
{
    
}

void ImageViewer2::showImage(std::string fileName)
{
//    this->rects.clear();
//    startPoint.x = 0;
//    startPoint.y = 0;
//    endPoint.x = 0;
//    endPoint.y = 0;
    
    std::string tmp;            
    this->fileName = fileName;
    this->image = cv::imread(tmp.assign(Config::imageDirectory).append("\\").append(fileName));
    cv::cvtColor(this->image, this->image, cv::COLOR_BGR2RGB);

    showImage();    
}

void ImageViewer2::showImage()
{
    QImage qImg = QImage(static_cast<const uchar*>(this->image.data), 
                         this->image.cols, this->image.rows, 
                         this->image.cols * this->image.channels(), 
                         QImage::Format_RGB888);
    
    pixmap = QPixmap::fromImage(qImg);
    pixmapItem->setPixmap(pixmap);
}
