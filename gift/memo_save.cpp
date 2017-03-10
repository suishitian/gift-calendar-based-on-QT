#include "memo_save.h"
#include "ui_memo_save.h"

#include <QMenu>
#include <QDebug>
#include <time.h>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>

QString memo_save::s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string memo_save::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

memo_save::memo_save(QWidget *parent,int year,int month,int day) :
    QDialog(parent),
    year(year),
    month(month),
    day(day),
    ui(new Ui::memo_save)
{
    ui->setupUi(this);

    ui->buttonBox->setFocusPolicy(Qt::NoFocus);

    QMenu* menu_type = new QMenu();
    location = QDir::currentPath();
    connect(menu_type,SIGNAL(triggered(QAction *)),this,SLOT(onMenu_1_Triggered(QAction *)));

    ui->actiontype_richang = new QAction(menu_type);
    ui->actiontype_xuexi = new QAction(menu_type);
    ui->actiontype_yule = new QAction(menu_type);
    ui->actiontype_qita = new QAction(menu_type);

    menu_type->addAction(ui->actiontype_richang);
    menu_type->addAction(ui->actiontype_xuexi);
    menu_type->addAction(ui->actiontype_yule);
    menu_type->addAction(ui->actiontype_qita);

    menu_type->addAction(ui->actiontype_richang);
    menu_type->addAction(ui->actiontype_xuexi);
    menu_type->addAction(ui->actiontype_yule);
    menu_type->addAction(ui->actiontype_qita);

    ui->actiontype_richang->setText(tr("日常"));
    ui->actiontype_xuexi->setText(tr("学习"));
    ui->actiontype_yule->setText(tr("娱乐"));
    ui->actiontype_qita->setText(tr("其他"));

    ui->pushButton_type->setMenu(menu_type);

    ui->pushButton_type->setText(tr("选择类型"));

    ui->spinBox_year->setRange(1900,2999);
    ui->spinBox_month->setRange(1,12);
    ui->spinBox_year->setValue(year);
    ui->spinBox_month->setValue(month);
    ui->spinBox_date->setRange(1,JulDate::dayofmonth(year,month));
    ui->spinBox_date->setValue(day);
    ui->spinBox_hour->setValue(8);
    ui->spinBox_hour->setRange(1,24);
    ui->spinBox_minute->setRange(0,59);
    ui->lineEdit_info->setText("请输入信息~");
    ui->textEdit_info->setText("请输入信息~");
}

memo_save::~memo_save()
{
    delete ui;
}

void memo_save::onMenu_1_Triggered(QAction * action)
{
    if(action==ui->actiontype_richang){
        ui->pushButton_type->setText(tr("日常"));
        type=0;
    }
    else if(action==ui->actiontype_xuexi){
        ui->pushButton_type->setText(tr("学习"));
        type=1;
    }
    else if(action==ui->actiontype_yule){
        ui->pushButton_type->setText(tr("娱乐"));
        type=2;
    }
    else if(action==ui->actiontype_qita){
        ui->pushButton_type->setText(tr("其他"));
        type=3;
    }
}

void memo_save::get_now_date()
{
    time_t timenow=time(NULL);
    tm* Jtime;
    Jtime=localtime(&timenow);
    year=Jtime->tm_year+1900;
    month=Jtime->tm_mon+1;
    day=Jtime->tm_mday;
}

void memo_save::on_spinBox_year_editingFinished()
{
    year=ui->spinBox_year->value();
    ui->spinBox_date->setRange(1,JulDate::dayofmonth(year,month));
}

void memo_save::on_spinBox_month_editingFinished()
{
    month=ui->spinBox_month->value();
    ui->spinBox_date->setRange(1,JulDate::dayofmonth(year,month));
}

void memo_save::on_spinBox_date_editingFinished()
{
    day=ui->spinBox_date->value();
}

void memo_save::on_spinBox_hour_editingFinished()
{
    hour=ui->spinBox_hour->value();
}

void memo_save::on_spinBox_minute_editingFinished()
{
    minute=ui->spinBox_minute->value();
}

void memo_save::on_buttonBox_accepted()
{
    if(year==0 && month==0 && day==0 && hour==0 && minute==0 && ui->lineEdit_info->text()=="" && ui->textEdit_info->toPlainText()==""){
        QMessageBox::about(this,"warning","信息不完整\0");
        return;
    }
    if(day>JulDate::dayofmonth(year,month)){
        QMessageBox::about(this,"warning","日期输入非法");
        return;
    }
    name = location+"/memo/"+s2q(std::to_string(year))+"."+s2q(std::to_string(month))+"."+
            s2q(std::to_string(day));
    content_name = location +"/memo_content"+"/"+s2q(std::to_string(year))+"."+s2q(std::to_string(month))+"."+
            s2q(std::to_string(day))+"."+s2q(std::to_string(hour))+"."+s2q(std::to_string(minute))+".memo.txt";
    QFile file(name+".memo.txt");
    if(file.open(QIODevice::WriteOnly|QIODevice::Append)){
        QTextStream write(&file);
        QString line1 = s2q(std::to_string(hour))+" "+s2q(std::to_string(minute))+' '+s2q(std::to_string(type))+"\r\n";
        QString line2 = ui->lineEdit_info->text() + "\r\n";
        QString line3 = content_name+"\r\n";
        write<<line1<<line2<<line3;
        file.close();
    }
    QFile file_c(content_name);
    if(file_c.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream write_c(&file_c);
        QString text = ui->textEdit_info->toPlainText();
        text.replace(QString("\n"), QString("\r\n"));
        write_c<<text;
        file_c.close();
    }
    if(ui->checkBox->isChecked()){
        int num1=year*10000+month*100+day;
        int num2=hour*100+minute;
        QFile file(QDir::currentPath()+"/memo/popup.txt");
        QString out=s2q(std::to_string(num1)+" "+std::to_string(num2)+"\r\n");
        if(file.open(QIODevice::Append|QIODevice::Text)){
            QTextStream write(&file);
            write<<out;
            file.close();
        }
    }
}
