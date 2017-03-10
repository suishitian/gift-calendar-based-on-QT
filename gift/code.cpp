#include "code.h"
#include "ui_code.h"

#include <QFile>
#include <QTextStream>

code::code(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::code)
{
    ui->setupUi(this);
    code::on_pushButton_Hcal_clicked();
}

code::~code()
{
    delete ui;
}

void code::on_pushButton_Hcal_clicked()
{
    QFile file(location+"/code/Hcal.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Hcode_clicked()
{
    QFile file(location+"/code/Hcode.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Hjul_clicked()
{
    QFile file(location+"/code/Hjul.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Hmain_clicked()
{
    QFile file(location+"/code/Hmain.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Hmemo_c_clicked()
{
    QFile file(location+"/code/Hmemoc.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Hmemo_s_clicked()
{
    QFile file(location+"/code/Hmemos.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Hpopup_clicked()
{
    QFile file(location+"/code/Hpopup.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Hset_clicked()
{
    QFile file(location+"/code/Hset.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Htv_clicked()
{
    QFile file(location+"/code/Htv.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Htvin_clicked()
{
    QFile file(location+"/code/Htvin.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Ccal_clicked()
{
    QFile file(location+"/code/Ccal.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Ccode_clicked()
{
    QFile file(location+"/code/Ccode.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Cjul_clicked()
{
    QFile file(location+"/code/Cjul.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Cmain_clicked()
{
    QFile file(location+"/code/Cmain.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Cmemo_c_clicked()
{
    QFile file(location+"/code/Cmemoc.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Cmemo_s_clicked()
{
    QFile file(location+"/code/Cmemos.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Cpopup_clicked()
{
    QFile file(location+"/code/Cpopup.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Cset_clicked()
{
    QFile file(location+"/code/Cset.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Ctv_clicked()
{
    QFile file(location+"/code/Ctv.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}

void code::on_pushButton_Ctvin_clicked()
{
    QFile file(location+"/code/Ctvin.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString text=read.readAll();
        ui->textBrowser->setText(text);
    }
}
