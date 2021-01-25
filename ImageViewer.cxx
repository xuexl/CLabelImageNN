#include "ImageViewer.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include<fstream>

#include<QPainter>

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
    this->rects.clear();
    startPoint.x = 0;
    startPoint.y = 0;
    endPoint.x = 0;
    endPoint.y = 0;
    
    std::string tmp;            
    this->fileName = fileName;
    this->image = cv::imread(tmp.assign(Config::imageDirectory).append("\\").append(fileName));
    cv::cvtColor(this->image, this->image, cv::COLOR_BGR2RGB);

    this->imageCopy = this->image.clone();
    
    showImage();    
}

//void ImageViewer::paintEvent(QPaintEvent *e)
//{
////   if(this->isCtrlKeyPressing)
////   {
////        QPainter painter(this);
       
////        QPen pen;
////        pen.setWidth(1);
////        pen.setColor(Qt::red);
////        painter.setPen(pen);
        
////        painter.drawLine(0, startPoint.y, width(), startPoint.y);        
////        painter.drawLine(startPoint.x, 0, startPoint.x, height());
        
////        painter.drawLine(0, currentPos.y, width(), currentPos.y);        
////        painter.drawLine(currentPos.x, 0, currentPos.x, height());       
////   }
//    update();
//}

void ImageViewer::mousePressEvent(QMouseEvent *e)
{
    if(this->isCtrlKeyPressing)
    {    
        startPoint.x = e->pos().x();
        startPoint.y = e->pos().y();
        update();
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

void ImageViewer::mouseMoveEvent(QMouseEvent *e)
{
    this->currentPos.x = e->pos().x();
    this->currentPos.y = e->pos().y();
    update();
}

void ImageViewer::showImage()
{
    QImage qImg = QImage(static_cast<const uchar*>(this->image.data), 
                         this->image.cols, this->image.rows, 
                         this->image.cols * this->image.channels(), 
                         QImage::Format_RGB888);
    
    this->setPixmap(QPixmap::fromImage(qImg));
}

void ImageViewer::clearRects()
{   
    this->imageCopy.clone().copyTo(this->image);
    this->showImage();
    
    this->rects.clear();
}

void ImageViewer::saveRects()
{
    std::string tmp;
    std::ofstream f(
                tmp.assign(Config::labelDirectory)
                .append("\\")
                .append(this->fileName.substr(0, this->fileName.find_last_of(".")))
                .append(".txt"));

    int w = this->image.cols;
    int h = this->image.rows;
    int tag = 0;
    for(auto& rect: this->rects)
    {
        auto p1 = rect.p1;
        auto p2 = rect.p2;
        
        auto classId = 0;
        auto xCenter = (p2.x + p1.x)/(2.0*w);
        auto yCenter = (p2.y + p1.y)/(2.0*h);
        auto xWidth = (p2.x - p1.x)/(1.0*w);
        auto yHeight = (p2.y - p1.y)/(1.0*h);       
        
        f<<(tag++?"\n":"")<<classId<<" "<<xCenter<<" "<<yCenter<<" "<<xWidth<<" "<<yHeight;        
    }
    f.close();
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
