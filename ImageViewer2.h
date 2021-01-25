#ifndef IMAGEVIEWER2_H
#define IMAGEVIEWER2_H

#include <QWidget>
#include <QGraphicsView>

#include<string>

#include<opencv2/core/mat.hpp>



class ImageViewer2: public QGraphicsView
{
    Q_OBJECT
public:
    ImageViewer2(QWidget *parent=nullptr);
    ~ImageViewer2();
    
    void showImage(std::string fileName);
    
private:
    QGraphicsScene *scene;
    QPixmap pixmap;
    QGraphicsPixmapItem *pixmapItem;
    
    std::string fileName;
    cv::Mat image; 
    
    void showImage();
    
};

#endif // IMAGEVIEWER2_H
