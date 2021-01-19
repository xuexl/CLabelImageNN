#include "ImageViewer.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


#include"Config.h"

#include"Cout.h"

ImageViewer::ImageViewer(QWidget *parent)
    :QLabel(parent)
{
    
}

ImageViewer::~ImageViewer()
{
    
}

void ImageViewer::showImage(std::string fileName)
{
    std::string tmp;        
    
    this->fileName = fileName;
    this->image = cv::imread(tmp.assign(Config::imageDirectory).append("\\").append(fileName));
    cv::cvtColor(this->image, this->image, cv::COLOR_BGR2RGB);

    showImage();
}

void ImageViewer::mousePressEvent(QMouseEvent *e)
{
    if(this->isCtrlKeyPressing)
    {    
        startPoint.x = e->pos().x();
        startPoint.y = e->pos().y();
    }
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->isCtrlKeyPressing)
    {    
        endPoint.x = e->pos().x();
        endPoint.y = e->pos().y();
        
        cv::rectangle(this->image, 
                      cv::Point(this->startPoint.x, this->startPoint.y), 
                      cv::Point(this->endPoint.x, this->endPoint.y), 
                      cv::Scalar(0, 0, 255), 2);
        
        this->showImage();
        
        IV_Rect rect;
        rect.p1 = this->startPoint;
        rect.p2 = this->endPoint;
        this->rects.emplace_back(rect);
    }
}

void ImageViewer::showImage()
{
    QImage qImg = QImage(static_cast<const uchar*>(this->image.data), 
                         this->image.cols, this->image.rows, 
                         this->image.cols * this->image.channels(), 
                         QImage::Format_RGB888);
    
    this->setPixmap(QPixmap::fromImage(qImg));
}

void ImageViewer::clear()
{
    
}

void ImageViewer::save()
{
    //save
    
    //next
}

void ImageViewer::setCtrlKeyPressing(bool pressing)
{
    this->isCtrlKeyPressing = pressing;
    
    if(!this->isCtrlKeyPressing)
    {
        startPoint.x = 0;
        startPoint.y = 0;
        endPoint.x = 0;
        endPoint.y = 0;
    }
}
