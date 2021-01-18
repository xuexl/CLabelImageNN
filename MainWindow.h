﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<string>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    
    
private:
    Ui::MainWindow *ui;
    
    void getImageList();
    

private slots:
    void showImage(std::string fileName);
    
};
#endif // MAINWINDOW_H
