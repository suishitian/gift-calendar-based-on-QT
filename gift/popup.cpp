#include "popup.h"
#include "ui_popup.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <time.h>
#include <QDebug>
#include <algorithm>
#include <QTableWidget>

popup::popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_popup->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(popup_doubleclicked(int,int)));
    reset_popup();
    reset_tv();
    set_check();
    time_t timenow=time(NULL);
    tm* Jtime;
    Jtime=localtime(&timenow);
    int year=Jtime->tm_year+1900;
    int month=Jtime->tm_mon+1;
    int day=Jtime->tm_mday;
    now_num=year*10000+month*100+day;

    read_file();
    sort_popup();
    popup_show();
    tv_show_p();
}

popup::~popup()
{
    delete ui;
}

QString popup::s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string popup::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

void popup::sort_popup()
{
    for (int j=0;j<size-1;j++){
        for (int i=0;i<size-1-j;i++){
            long int n=date_time[i][0]*100000000+date_time[i][1]*1000000+date_time[i][2]*10000
                    +date_time[i][3]*100+date_time[i][4];
            long int m=date_time[i+1][0]*100000000+date_time[i+1][1]*1000000+date_time[i+1][2]*10000
                    +date_time[i+1][3]*100+date_time[i+1][4];
            if (n>m){
                sort(date_time[i][0],date_time[i+1][0]);
                sort(date_time[i][1],date_time[i+1][1]);
                sort(date_time[i][2],date_time[i+1][2]);
                sort(date_time[i][3],date_time[i+1][3]);
                sort(date_time[i][4],date_time[i+1][4]);
                sort(date_time[i][5],date_time[i+1][5]);

                swap(popup_qs[i][0],popup_qs[i+1][0]);
                swap(popup_qs[i][1],popup_qs[i+1][1]);
            }
        }
    }
}

void popup::sort(int &a, int &b)
{
    int temp=0;
    temp=a;
    a=b;
    b=temp;
}

void popup::popup_show()
{
    ui->tableWidget->setRowCount(size);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->verticalHeader()->setVisible(false);
    QStringList horizontitle;
    horizontitle << "日期" << "时间" << "类型" << "信息";
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHorizontalHeaderLabels(horizontitle);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    ui->tableWidget->setColumnWidth(0,90);
    ui->tableWidget->setColumnWidth(1,55);
    ui->tableWidget->setColumnWidth(2,55);
    ui->tableWidget->setColumnWidth(3,200);
    for(int i=0;i<size;i++){
        ui->tableWidget->setRowHeight(i,22);
    }

    for(int i=0;i<size;i++){
        QString date=s2q(std::to_string(date_time[i][0])+"."+std::to_string(date_time[i][1])
                +"."+std::to_string(date_time[i][2]));
        QString time=s2q(std::to_string(date_time[i][3])+":"+std::to_string(date_time[i][4]));
        QString type_q="";
        if(date_time[i][5]==0) type_q="日常";
        if(date_time[i][5]==1) type_q="学习";
        if(date_time[i][5]==2) type_q="娱乐";
        if(date_time[i][5]==3) type_q="其他";

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(date));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(time));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(type_q));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(popup_qs[i][0]));
    }
}

void popup::tv_show_p()
{
    int count=0;
    QFile file(location+"/tv/tv.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        for(int i=0;!file.atEnd();i++){
            QString str=file.readLine();
            count++;
        }
        file.close();
    }
    tv_size=count/2;

    int index=0;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        for(int i=0;i<count;i++){
            int chapter=0;
            int season=0;
            QString content=read.readLine();
            QString name=read.readLine();
            analyze_tv(season,chapter,q2s(content));
            if(chapter>=0){
                tv_num[index][0]=season;
                tv_num[index][1]=chapter;
                tv_name[index]=name;
                index++;
            }
            else if(chapter<0){
                tv_size--;
            }
        }
        file.close();
    }

    ui->tv_popup->setRowCount(tv_size);
    ui->tv_popup->setColumnCount(3);
    ui->tv_popup->verticalHeader()->setVisible(false);
    QStringList horizontitle;
    horizontitle << "剧名" << "应看季数" << "应看集数" ;
    ui->tv_popup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv_popup->setHorizontalHeaderLabels(horizontitle);
    ui->tv_popup->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    ui->tv_popup->setColumnWidth(0,77);
    ui->tv_popup->setColumnWidth(1,70);
    ui->tv_popup->setColumnWidth(2,70);
    for(int i=0;i<tv_size;i++){
        ui->tv_popup->setRowHeight(i,22);
    }
    for(int i=0;i<tv_size;i++){
        ui->tv_popup->setItem(i,0,new QTableWidgetItem(tv_name[i]));
        ui->tv_popup->setItem(i,1,new QTableWidgetItem(s2q(std::to_string(tv_num[i][0]))));
        ui->tv_popup->setItem(i,2,new QTableWidgetItem(s2q(std::to_string(tv_num[i][1]+1))));
    }
}

void popup::reset_tv()
{
    for(int i=0;i<200;i++){
        tv_name[i]="";
        tv_num[i][0]=0;
        tv_num[i][1]=0;
    }
    tv_size=0;
}

void popup::analyze_tv(int &season, int &chapter, std::string content)
{
    int season_flag=0;
    int chapter_flag=0;
    int receving=0;
    std::string season_s="";
    std::string chapter_s="";
    for(int i=0;content[i]!='\0';i++){
        if(receving==0 && content[i]==' '){
            continue;
        }
        if(season_flag==0 && content[i]>='0' && content[i]<='9'){
            season_s=season_s+content[i];
            receving=1;
            continue;
        }
        if(season_flag==0 && content[i]==' ' && receving==1){
            season_s=season_s+'\0';
            season=atoi(season_s.c_str());
            season_flag=1;
            receving=0;
            continue;
        }

        if(season_flag==1 && chapter_flag==0 && content[i]>='0' && content[i]<='9'){
            chapter_s=chapter_s+content[i];
            receving=1;
            continue;
        }
        if(season_flag==1 && chapter_flag==0 && content[i]=='-'){
            chapter=-1;
            return;
        }
    }
    chapter_s=chapter_s+'\0';
    chapter=atoi(chapter_s.c_str());
}

void popup::set_check()
{
    QFile file(location+"/memo/settings.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString content=read.readLine();
        if(q2s(content)[0]=='0'){
            ui->checkBox->setChecked(false);
            check_flag=0;
        }
        else if(q2s(content)[0]=='1'){
            ui->checkBox->setChecked(true);
            check_flag=1;
        }
        file.close();
    }
}

void popup::popup_doubleclicked(int row, int col)
{
    int memo_num_c=date_time[row][3]*100+date_time[row][4];
    int type_cc=date_time[row][5];
    QString location_memo_c=location+"/memo/"+s2q(std::to_string(date_time[row][0])+"."+std::to_string(date_time[row][1])+"."
                                                  +std::to_string(date_time[row][2])+".memo")+".txt";
    int num=date_time[row][0]*10000+date_time[row][1]*100+date_time[row][2];
    memo_c a(this,memo_num_c,type_cc,popup_qs[row][0],popup_qs[row][1],location_memo_c,num);
    a.exec();
    reset_popup();
    read_file();
    sort_popup();
    popup_show();
}

void popup::reset_popup()
{
    for(int i=0;i<200;i++){
        for(int j=0;j<6;j++){
            date_time[i][j]=0;
        }
        for(int o=0;o<2;o++){
            popup_qs[i][o]="";
        }
    }
}

void popup::read_file()
{
    QFile file(location+"/memo/popup.txt");
    int count=0;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        for(int i=0;!file.atEnd();i++){
            QString str=file.readLine();
            count++;
        }
        file.close();
        size=count;
    }
    int index=0;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        for(int i=0;i<count;i++){
            QString content=read.readLine();
            qDebug()<<content;
            if(analyze_file(date_time[index][0],date_time[index][1],date_time[index][2],date_time[index][3],date_time[index][4],q2s(content))){
                index++;
            }
            else size--;
        }
        file.close();
    }
    for(int i=0;i<size;i++){
        QString open = s2q(q2s(location)+"/memo/"+std::to_string(date_time[i][0])+"."+std::to_string(date_time[i][1])+"."+std::to_string(date_time[i][2])+"."+
                "memo.txt");
        QFile file(open);
        int type_t=0;
        int count=0;
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            for(int i=0;!file.atEnd();i++){
                QString str=file.readLine();
                count++;
            }
            file.close();
        }
        if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
            int num=date_time[i][3]*100+date_time[i][4];
            QTextStream read(&file);
            for(int j=0;j<count/3;j++){
                QString content=read.readLine();
                QString content2=read.readLine();
                QString content3=read.readLine();

                if(analyze_popup(num,type_t,q2s(content))){
                    date_time[i][5]=type_t;
                    popup_qs[i][0]=content2;
                    popup_qs[i][1]=content3;
                    break;
                }
                else{
                    continue;
                }
            }
            file.close();
        }
    }
}

bool popup::analyze_file(int &year, int &month, int &day, int &hour, int &minute, std::string content)
{
    int date_flag=0;
    int time_flag=0;
    std::string date_ss="";
    std::string time_ss="";
    int receving=0;
    int a;
    int b;
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

    if(a>=now_num){
        year=a/10000;
        month=(a-year*10000)/100;
        day=a-year*10000-month*100;

        hour=b/100;
        minute=b-hour*100;
        return true;
    }
    else if(a<now_num){
        return false;
    }
}

bool popup::analyze_popup(int num,int &type, std::string content)
{
    int hour_flag=0;
    int minute_flag=0;
    int receving=0;
    int type_flag=0;
    std::string hour_s="";
    std::string minute_s="";
    std::string type_s="";
    int hour=0;
    int minute=0;

    for(int i=0;content[i]!='\0';i++){
        if(receving==0 && content[i]==' '){
            continue;
        }

        if(hour_flag==0 && (content[i]>='0' && content[i]<='9')){
            hour_s=hour_s+content[i];
            receving=1;
            continue;
        }
        if(hour_flag==0 && content[i]==' ' && receving==1){
            hour_s=hour_s+'\0';
            hour=atoi(hour_s.c_str());
            receving=0;
            hour_flag=1;
            continue;
        }

        if(hour_flag==1 && minute_flag==0 && (content[i]>='0' && content[i]<='9')){
            minute_s=minute_s+content[i];
            receving=1;
            continue;
        }
        if(hour_flag==1 && minute_flag==0 && content[i]==' ' && receving==1){
            minute_s=minute_s+'\0';
            minute=atoi(minute_s.c_str());
            receving=0;
            minute_flag=1;
            continue;
        }

        if(hour_flag==1 && minute_flag==1 && type_flag==0 && content[i]>='0' && content[i]<='3' && receving==0){
            type_s = type_s + content[i] +'\0';
            type=atoi(type_s.c_str());
            type_flag=1;
        }
    }

    if((hour*100+minute)==num){
        return true;
    }
    else if((hour*100+minute)!=num){
        return false;
    }
}

void popup::on_pushButton_close_clicked()
{
    if(check_flag==1 && ui->checkBox->isChecked())
        this->close();
    if(check_flag==0 && !ui->checkBox->isChecked())
        this->close();
    if(check_flag==0 && ui->checkBox->isChecked()){
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
    if(check_flag==1 && !ui->checkBox->isChecked()){
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
}
