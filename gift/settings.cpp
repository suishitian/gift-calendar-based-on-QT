#include "settings.h"
#include "ui_settings.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    set_check();
}

settings::~settings()
{
    delete ui;
}

void settings::set_check()
{
    QFile file(location+"/memo/settings.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString content=read.readLine();
        if(content[0]=='0'){
            popup_flag=0;
            ui->checkBox_popup->setChecked(false);
        }
        else if(content[0]=='1'){
            popup_flag=1;
            ui->checkBox_popup->setChecked(true);
        }
        QString content2=read.readLine();
        if(content2[0]=='0'){
            music_flag=0;
            ui->checkBox_music->setChecked(false);
        }
        else if(content2[0]=='1'){
            music_flag=1;
            ui->checkBox_music->setChecked(true);
        }
        file.close();
    }
}

void settings::on_buttonBox_accepted()
{
    if(popup_flag==0 && !ui->checkBox_popup->isChecked()){
        this->close();
    }
    else if(popup_flag==1 && ui->checkBox_popup->isChecked()){
        this->close();
    }
    else if(popup_flag==1 && !ui->checkBox_popup->isChecked()){
        QFile file(QDir::currentPath()+"/memo/settings.txt");
        QString whole;
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream read(&file);
            whole=read.readAll();
            file.close();
        }
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file);
            whole.replace(QString("1 popup"),QString("0 popup"));
            write<<whole;
            file.close();
        }
        this->close();
    }
    else if(popup_flag==0 && ui->checkBox_popup->isChecked()){
        QFile file(QDir::currentPath()+"/memo/settings.txt");
        QString whole;
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream read(&file);
            whole=read.readAll();
            file.close();
        }
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file);
            whole.replace(QString("0 popup"),QString("1 popup"));
            write<<whole;
            file.close();
        }
        this->close();
    }

    if(music_flag==0 && !ui->checkBox_music->isChecked()){
        this->close();
    }
    else if(music_flag==1 && ui->checkBox_music->isChecked()){
        this->close();
    }
    else if(music_flag==1 && !ui->checkBox_music->isChecked()){
        QFile file(QDir::currentPath()+"/memo/settings.txt");
        QString whole;
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream read(&file);
            whole=read.readAll();
            file.close();
        }
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file);
            whole.replace(QString("1 music"),QString("0 music"));
            write<<whole;
            file.close();
        }
        this->close();
    }
    else if(music_flag==0 && ui->checkBox_music->isChecked()){
        QFile file(QDir::currentPath()+"/memo/settings.txt");
        QString whole;
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream read(&file);
            whole=read.readAll();
            file.close();
        }
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file);
            whole.replace(QString("0 music"),QString("1 music"));
            write<<whole;
            file.close();
        }
        this->close();
    }
}
