#include "memo_c.h"
#include "ui_memo_c.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QDir>

QString memo_c::s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string memo_c::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

void memo_c::set_check()
{
    QString path_popup=QDir::currentPath()+"/memo/popup.txt";
    QFile file(path_popup);
    int count=0;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        for(int i=0;!file.atEnd();i++){
            QString str=file.readLine();
            count++;
        }
        file.close();
    }
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        for(int i=0;i<count;i++){
            QString content=read.readLine();
            int date_t=0;
            int time_t=0;
            get_num(date_t,time_t,q2s(content));
            if(date_t==date_num && time_t==memo_num){
                ui->checkBox->setChecked(true);
                popup_flag=1;
                file.close();
                return;
            }
        }
        file.close();
        popup_flag=0;
    }
}

void memo_c::get_num(int &a, int &b, std::string content)
{
    int date_flag=0;
    int time_flag=0;
    std::string date_ss="";
    std::string time_ss="";
    int receving=0;
    for(int i=0;content[i]!='\0';i++){
        if(receving==0 && content[i]==' '){
            continue;
        }
        if(date_flag==0 && content[i]>='0' && content[i]<='9'){
            date_ss=date_ss+content[i];
            receving=1;
            continue;
        }
        if(date_flag==0 && content[i]==' ' && receving==1){
            date_ss=date_ss+'\0';
            a=atoi(date_ss.c_str());
            date_flag=1;
            receving=0;
            continue;
        }

        if(date_flag==1 && time_flag==0 && content[i]>='0' && content[i]<='9'){
            time_ss=time_ss+content[i];
            receving=1;
            continue;
        }
    }
    time_ss=time_ss+'\0';
    b=atoi(time_ss.c_str());
}

memo_c::memo_c(QWidget *parent , int memo_num , int type ,QString memo_info,QString memo_path,QString path,int date) :
    QDialog(parent),
    ui(new Ui::memo_c),
    memo_num(memo_num),
    type(type),
    memo_info(memo_info),
    memo_path(memo_path),
    location(path),
    date_num(date)
{

    ui->setupUi(this);
    ui->checkBox->setChecked(false);
    set_check();
    ui->textBrowser_info->setText(memo_info);
    int hour=memo_num/100;
    int minute=memo_num-hour*100;
    QString time = s2q(std::to_string(hour)+":"+std::to_string(minute));
    ui->textBrowser_time->setText(time);
    QFile file(memo_path);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        ui->textBrowser->setText(read.readAll());
    }

    if(type==0) ui->textBrowser_type->setText(tr("日常"));
    if(type==1) ui->textBrowser_type->setText(tr("学习"));
    if(type==2) ui->textBrowser_type->setText(tr("娱乐"));
    if(type==3) ui->textBrowser_type->setText(tr("其他"));
}

memo_c::~memo_c()
{
    delete ui;
}

void memo_c::on_pushButton_clicked()
{
    QString out=s2q(std::to_string(date_num)+" "+std::to_string(memo_num)+"\n");
    if(popup_flag==1 && ui->checkBox->isChecked())
        this->close();
    if(popup_flag==0 && !ui->checkBox->isChecked())
        this->close();
    if(popup_flag==0 && ui->checkBox->isChecked()){
        QFile file(QDir::currentPath()+"/memo/popup.txt");
        if(file.open(QIODevice::Append|QIODevice::Text)){
            QTextStream write(&file);
            write<<out;
            file.close();
        }
        this->close();
    }
    if(popup_flag==1 && !ui->checkBox->isChecked()){
        QFile file(QDir::currentPath()+"/memo/popup.txt");
        QString whole;
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream read(&file);
            whole=read.readAll();
            file.close();
        }
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file);
            whole.replace(out,QString(""));
            write<<whole;
            file.close();
        }
        this->close();
    }
}

void memo_c::on_pushButton_2_clicked()
{
    int ans=QMessageBox::question(this,"warning",tr("确定要删除此记录吗\0"),QMessageBox::Yes,QMessageBox::No);
    if(ans==QMessageBox::Yes){
        QString content;
        QFile file(location);

        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream read(&file);
            content=read.readAll();
            file.close();
        }

        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file);
            int hour=memo_num/100;
            int minute=memo_num-hour*100;
            QString info = s2q(std::to_string(hour)+" "+std::to_string(minute)+" "+std::to_string(type)+"\n"
                           +q2s(memo_info)+"\n"+q2s(memo_path)+"\n");

            content.replace(info,QString(""));
            write<<content;
            file.close();
        }

        QFile file1(QDir::currentPath()+"/memo/popup.txt");
        QString out=s2q(std::to_string(date_num)+" "+std::to_string(memo_num)+"\n");
        QString whole;
        if(file1.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream read(&file1);
            whole=read.readAll();
            file1.close();
        }
        if(file1.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file1);
            whole.replace(out,QString(""));
            write<<whole;
            file1.close();
        }
        this->close();
    }
    else if(ans==QMessageBox::No){
        return;
    }
}
