#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QObject>
#include<QLabel>

#include<opencv2/core/core.hpp>


class ImageViewer: public QLabel
{
    Q_OBJECT
public:
    ImageViewer();
    ~ImageViewer();
    
    void showImage(std::string fileName);
    
protected:
    //重写绘制事件
    void paintEvent(QPaintEvent *e) override;
    //鼠标按下
    void mousePressEvent(QMouseEvent *e) override;
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *e) override;
    //鼠标抬起
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
//    cv::Mat* image = nullptr; 
        
};

#endif // IMAGEVIEWER_H
