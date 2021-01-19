#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QObject>
#include<QWidget>
#include<QLabel>
#include<QPaintEvent>
#include<QMouseEvent>

#include<opencv2/core/mat.hpp>

#include<vector>
#include<string>


class ImageViewer: public QLabel
{
    Q_OBJECT
public:
    ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();
    
    void showImage(std::string fileName);
    void setCtrlKeyPressing(bool pressing);
    
private:
    //鼠标按下
    void mousePressEvent(QMouseEvent *e) override;
    //鼠标抬起
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    std::string fileName;
    cv::Mat image; 
    bool isCtrlKeyPressing = false;
    //define rect
    struct IV_Point
    {        
        int x = 0;
        int y = 0;
    };
    struct IV_Rect
    {
        IV_Point p1;
        IV_Point p2;
    };
    //rects
    std::vector<IV_Rect> rects;    
    IV_Point startPoint;
    IV_Point endPoint;
    //
    void showImage();
    void clear();
    void save();
    
};

#endif // IMAGEVIEWER_H
