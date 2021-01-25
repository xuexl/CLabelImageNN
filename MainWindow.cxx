#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include<io.h>
#include<vector>

#include"Config.h"

#include"Cout.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)    
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    
    connect(ui->lw_images, &QListWidget::itemClicked, [this](auto item){        
        this->ui->gp_view->showImage(item->text().toStdString());
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

void MainWindow::keyPressEvent(QKeyEvent *e)
{
//    if(e->modifiers() == Qt::ControlModifier)
//    {
//        if(e->key() == Qt::Key_C)
//        {
//            this->ui->lb_view->clearRects();
//        }        
//        else if(e->key() == Qt::Key_S)
//        {
//            this->ui->lb_view->saveRects();
//        }
//        else
//            this->ui->lb_view->setCtrlKeyPressing(true);
//    }    
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{        
//    if(e->key() == Qt::Key_Control)
//    {
//        this->ui->lb_view->setCtrlKeyPressing(false);
//    }
}
