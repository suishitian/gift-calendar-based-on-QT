#include "tv.h"
#include "ui_tv.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

QString tv::s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string tv::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

tv::tv(QWidget *parent, QString tv_name, int season, int chapter, QString location_tv) :
    QDialog(parent),
    tv_name(tv_name),
    season(season),
    chapter(chapter),
    location_tv(location_tv),
    season_new(season),
    chapter_new(chapter),
    ui(new Ui::tv)
{
    ui->setupUi(this);
    browser_show();
    QFile file(location_tv);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        content=read.readAll();
        file.close();
    }
}

tv::~tv()
{
    delete ui;
}

void tv::browser_show()
{
    QString season_t="";
    QString chapter_t="";
    if(chapter_new<0){
        season_t="完结";
        chapter_t="完结";
    }
    else{
        season_t=s2q(std::to_string(season_new));
        chapter_t=s2q(std::to_string(chapter_new));
    }
    ui->textBrowser_name->setText(tv_name);
    ui->textBrowser_season->setText(season_t);
    ui->textBrowser_chapter->setText(chapter_t);
}
void tv::on_pushButton_season_minus_clicked()
{
    season_new--;
    if(season_new<0){
        season_new=0;
    }
    browser_show();
}

void tv::on_pushButton_season_add_clicked()
{
    season_new++;
    browser_show();
}

void tv::on_pushButton_chapter_minus_clicked()
{
    chapter_new--;
    if(chapter_new<0){
        chapter_new=0;
    }
    browser_show();
}

void tv::on_pushButton_chapter_add_clicked()
{
    chapter_new++;
    browser_show();
}

void tv::on_pushButton_over_clicked()
{
    chapter_new=-1;
    season_new=0;
    browser_show();
}


void tv::on_pushButton_save_clicked()
{
    QFile file(location_tv);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream write(&file);
        QString info=s2q(std::to_string(season)+" "+std::to_string(chapter)+"\n"
                +q2s(tv_name));
        QString info_new=s2q(std::to_string(season_new)+" "+std::to_string(chapter_new)+"\r\n"
                             +q2s(tv_name));
        content.replace(info,info_new);
        season=season_new;
        chapter=chapter_new;
        write<<content;
        file.close();
    }
    browser_show();
    this->close();
}

void tv::on_pushButton_delete_clicked()
{
    int ok=QMessageBox::question(this,tr("删除记录\0"),tr("确认删除当前记录？\0"),QMessageBox::Yes,QMessageBox::No);
    if (ok==QMessageBox::Yes){
        QFile file(location_tv);
        if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream write(&file);
            QString info=s2q(std::to_string(season)+" "+std::to_string(chapter)+"\n"
                    +q2s(tv_name)+"\n");
            content.replace(info,QString(""));
            season=season_new;
            chapter=chapter_new;
            write<<content;
            file.close();
        }
        browser_show();
        this->close();
    }
}

void tv::on_pushButton_cancel_clicked()
{
    this->close();
}
