#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <string>
#include <QDebug>
#include <QDialog>
#include <QInputDialog>
#include <time.h>
#include <QFrame>
#include <QFile>
#include <string>
#include <QTextStream>
#include <QDir>
#include <QTableWidget>
#include <QTableView>
#include <QDir>
#include <QMessageBox>
#include <string>
#include <algorithm>
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<0;
    ui->setupUi(this);
    time_t timenow=time(NULL);
    tm* Jtime;
    Jtime=localtime(&timenow);
    year=Jtime->tm_year+1900;
    month=Jtime->tm_mon+1;
    day=Jtime->tm_mday;
    set_checked();
    ui->textEdit->setStyleSheet("background-color:transparent;");
    ui->memo->setShowGrid(false);
    ui->tv->setShowGrid(false);
    ui->memo->setStyleSheet("background-color:transparent;");
    ui->tv->setStyleSheet("background-color:transparent;");
    this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    refresh_allbutton();
    ui->memo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->memo,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(memo_doubleclicked(int,int)));
    connect(ui->tv,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(tv_doubleclicked(int,int)));
    ui->spinBox_year->setRange(1900,2999);
    ui->spinBox_month->setRange(1,12);
    ui->spinBox_year->setValue(year);
    ui->spinBox_month->setValue(month);
    location = QDir::currentPath();
    QDir temp;
    if(!temp.exists(location+"/dialy")){
        temp.mkdir(location+"/dialy");
    }
    if(!temp.exists(location+"/memo")){
        temp.mkdir(location+"/memo");
    }
    if(!temp.exists(location+"/memo_content")){
        temp.mkdir(location+"/memo_content");
    }
    if(!temp.exists(location+"/tv")){
        temp.mkdir(location+"/tv");
    }
    if(!temp.exists(location+"/music")){
        temp.mkdir(location+"/music");
    }
    if(!temp.exists(location+"/code")){
        temp.mkdir(location+"/code");
    }
    memo_size=0;
    reset_memo();
    reset_tv();
    memo_show();
    tv_show();
    textedit_show();
    get_popup();
    if(popup_flag==1){
        popup a;
        a.exec();
    }

    set_wallpaper();
    set_music();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string MainWindow::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

void MainWindow::set_button_show(QPushButton* button,int a,int b){
    int num=0;
    if (date_different==0 && date_finishdate==0 && date_finishrow==0 && date_startdate==0){
        JulDate test(year,month,1);
        int week = test.getweek();

        int days=JulDate::dayofmonth(year,month);
        if(week==7){
            date_different=1;
            date_startdate=0;
        }
        else {
            date_different=1-week;
            date_startdate=week;
        }
        int gap;
        if(week==7){
            gap=0;
        }
        else gap=week;
        if(days%7-1+gap>6){
            date_finishrow=days/7+1;
            date_finishdate=days%7-8+gap;
        }
        else if(days%7-1+gap<=6){
            date_finishrow=days/7;
            date_finishdate=days%7-1+gap;
        }
    }

    if(a>0 && a<date_finishrow){
        num=a*7+b+date_different;
        button->show();
        button->setText(s2q(std::to_string(num)));
    }
    else if(a==0 && b>=date_startdate){
        num=a*7+b+date_different;
        button->setText(s2q(std::to_string(num)));
        button->show();
    }
    else if(a==date_finishrow && b<=date_finishdate){
        num=a*7+b+date_different;
        button->setText(s2q(std::to_string(num)));
        button->show();
    }
    else {
        button->setText(" ");
        button->hide();
    }
    if(day==num){
        button->setChecked(true);
    }
    else button->setChecked(false);

    if(month==5 && num==6){
        button->setStyleSheet("background-color: rgb(255, 166, 125);");
    }
    else if(month==6 && num==14){
        button->setStyleSheet("background-color: rgb(255, 166, 125);");
    }
    else if(month==8 && num==1){
        button->setStyleSheet("background-color: rgb(255, 166, 125);");
    }
    else if(month==5 && num==23){
        button->setStyleSheet("background-color: rgb(255, 166, 125);");
    }
    else if(month==4 && num==24){
        button->setStyleSheet("background-color: rgb(255, 166, 125);");
    }
    else if(month==12 && num==28){
        button->setStyleSheet("background-color: rgb(255, 218, 29);");
    }
    else{
        button->setStyleSheet("background-color:rgb(255, 193, 231);");
    }
}

void MainWindow::refresh_allbutton()
{
    MainWindow::set_button_show(ui->pushButton_0_0,0,0);
    MainWindow::set_button_show(ui->pushButton_0_1,0,1);
    MainWindow::set_button_show(ui->pushButton_0_2,0,2);
    MainWindow::set_button_show(ui->pushButton_0_3,0,3);
    MainWindow::set_button_show(ui->pushButton_0_4,0,4);
    MainWindow::set_button_show(ui->pushButton_0_5,0,5);
    MainWindow::set_button_show(ui->pushButton_0_6,0,6);
    MainWindow::set_button_show(ui->pushButton_1_0,1,0);
    MainWindow::set_button_show(ui->pushButton_1_1,1,1);
    MainWindow::set_button_show(ui->pushButton_1_2,1,2);
    MainWindow::set_button_show(ui->pushButton_1_3,1,3);
    MainWindow::set_button_show(ui->pushButton_1_4,1,4);
    MainWindow::set_button_show(ui->pushButton_1_5,1,5);
    MainWindow::set_button_show(ui->pushButton_1_6,1,6);
    MainWindow::set_button_show(ui->pushButton_2_0,2,0);
    MainWindow::set_button_show(ui->pushButton_2_1,2,1);
    MainWindow::set_button_show(ui->pushButton_2_2,2,2);
    MainWindow::set_button_show(ui->pushButton_2_3,2,3);
    MainWindow::set_button_show(ui->pushButton_2_4,2,4);
    MainWindow::set_button_show(ui->pushButton_2_5,2,5);
    MainWindow::set_button_show(ui->pushButton_2_6,2,6);
    MainWindow::set_button_show(ui->pushButton_3_0,3,0);
    MainWindow::set_button_show(ui->pushButton_3_1,3,1);
    MainWindow::set_button_show(ui->pushButton_3_2,3,2);
    MainWindow::set_button_show(ui->pushButton_3_3,3,3);
    MainWindow::set_button_show(ui->pushButton_3_4,3,4);
    MainWindow::set_button_show(ui->pushButton_3_5,3,5);
    MainWindow::set_button_show(ui->pushButton_3_6,3,6);
    MainWindow::set_button_show(ui->pushButton_4_0,4,0);
    MainWindow::set_button_show(ui->pushButton_4_1,4,1);
    MainWindow::set_button_show(ui->pushButton_4_2,4,2);
    MainWindow::set_button_show(ui->pushButton_4_3,4,3);
    MainWindow::set_button_show(ui->pushButton_4_4,4,4);
    MainWindow::set_button_show(ui->pushButton_4_5,4,5);
    MainWindow::set_button_show(ui->pushButton_4_6,4,6);
    MainWindow::set_button_show(ui->pushButton_5_0,5,0);
    MainWindow::set_button_show(ui->pushButton_5_1,5,1);
    MainWindow::set_button_show(ui->pushButton_5_2,5,2);
    MainWindow::set_button_show(ui->pushButton_5_3,5,3);
    MainWindow::set_button_show(ui->pushButton_5_4,5,4);
    MainWindow::set_button_show(ui->pushButton_5_5,5,5);
    MainWindow::set_button_show(ui->pushButton_5_6,5,6);
    ui->spinBox_year->setValue(year);
    ui->spinBox_month->setValue(month);
}

void MainWindow::on_next_month_clicked()
{
    if(year==2999 && month==12){
        month=12;
    }
    else month++;

    if(month>12){
        year++;
        month=1;
    }

    reset_flag();

    set_wallpaper();
    reset_memo();
    textedit_show();
    memo_show();
    refresh_allbutton();
}

void MainWindow::reset_flag()
{
    date_different=0;
    date_finishdate=0;
    date_finishrow=0;
    date_startdate=0;
}

void MainWindow::on_next_year_clicked()
{
    if(year<2999){
        year++;
    }
    else if(year>=2999){
        year=2999;
    }

    reset_flag();
    refresh_allbutton();
    set_wallpaper();
    reset_memo();
    textedit_show();
    memo_show();
}

void MainWindow::on_last_month_clicked()
{
    if(year==1900 && month==1){
        month=1;
    }
    else month--;

    if(month==0){
        year--;
        month=12;
    }

    reset_flag();
    refresh_allbutton();
    set_wallpaper();
    reset_memo();
    textedit_show();
    memo_show();
}

void MainWindow::on_last_year_clicked()
{
    if(year>1900){
        year--;
    }
    else if(year<=1900){
        year=1900;
    }

    reset_flag();
    refresh_allbutton();
    set_wallpaper();
    reset_memo();
    textedit_show();
    memo_show();
}

void MainWindow::on_spinBox_year_editingFinished()
{
    year = ui->spinBox_year->value();
    reset_flag();
    refresh_allbutton();
    set_wallpaper();
    reset_memo();
    textedit_show();
    memo_show();
}


void MainWindow::on_spinBox_month_editingFinished()
{
    month = ui->spinBox_month->value();
    reset_flag();
    refresh_allbutton();
    set_wallpaper();
    reset_memo();
    textedit_show();
    memo_show();
}


void MainWindow::on_pushButton_now_clicked()
{
    time_t timenow=time(NULL);
    tm* Jtime;
    Jtime=localtime(&timenow);
    year=Jtime->tm_year+1900;
    month=Jtime->tm_mon+1;
    day=Jtime->tm_mday;
    reset_flag();
    refresh_allbutton();
    textedit_show();
    memo_show();
}

void MainWindow::textedit_show()
{
    QDir temp;
    if(!temp.exists(location+"/dialy")){
        QMessageBox::about(this,"warning","找不到目标文件夹");
        return;
    }
    if(day<0){
        return;
    }
    date_gonna_print=day;
    QString filename = s2q(std::to_string(year)+"."+std::to_string(month)+"."
                           +std::to_string(date_gonna_print));
    dialyname=filename+".txt";
    QString start_print=s2q(std::to_string(year)+"."+std::to_string(month)+"."
                            +std::to_string(date_gonna_print))+"\n"+"---------------------------------------\n";
    QFile file(location+"/dialy"+"/"+dialyname);
    QString text="";
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream text_TS(&file);
        text = text_TS.readAll();
    }
    else text = "";
    file.close();
    QString today_print = start_print + text;

    ui->textEdit->setText(today_print);
}

void MainWindow::memo_show()
{
    QDir temp;
    if(!temp.exists(location+"/memo") || !temp.exists(location+"/memo_content")){
        QMessageBox::about(this,"warning","找不到目标文件夹");
        return;
    }
    if(day<0){
        return;
    }

    date_gonna_print=day;
    QString filename = s2q(std::to_string(year)+"."+std::to_string(month)+"."
                           +std::to_string(date_gonna_print)+".memo");
    QString memoname = filename + ".txt";
    QFile file(location+"/memo"+"/"+memoname);
    int count=0;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        for(int i=0;!file.atEnd();i++){
            QString str=file.readLine();
            count++;
        }
    }
    file.close();
    memo_size=count/3;
    ui->memo->setRowCount(count/3);
    ui->memo->setColumnCount(3);
    ui->memo->setColumnWidth(0,48);
    ui->memo->setColumnWidth(1,45);
    ui->memo->setColumnWidth(2,110);
    for(int i=0;i<count;i++){
        ui->memo->setRowHeight(i,22);
    }
    ui->memo->verticalHeader()->setVisible(false);
    QStringList horizontitle;
    horizontitle << "时间" << "类型" << "信息";
    ui->memo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->memo->setHorizontalHeaderLabels(horizontitle);
    ui->memo->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        for(int i=0;i<memo_size;i++){
            QString content=read.readLine();
            int hour=0;
            int minute=0;
            int type=0;
            analyze_memo(hour,minute,type,q2s(content));

            memo_num[i][0]=(hour*100)+minute;
            memo_num[i][1]=type;

            QString info_q = read.readLine();

            QString path=read.readLine();
            memo_qs[i][0]=info_q;
            memo_qs[i][1]=path;
            file.close();
        }
    }
    for(int i=0;i<memo_size;i++){
        qDebug()<<memo_num[i][0]<<"||||"<<memo_num[i][1];
    }
    sort_memo();

    for(int i=0;i<memo_size;i++){
        qDebug()<<memo_num[i][0]<<"||||"<<memo_num[i][1];
    }
    for(int i=0;i<memo_size;i++){
        int hour_n=memo_num[i][0]/100;
        int minute_n=memo_num[i][0]-hour_n*100;
        QString time=s2q(std::to_string(hour_n)+":"+std::to_string(minute_n));
        ui->memo->setItem(i,0,new QTableWidgetItem(time));

        QString type_q="";
        if(memo_num[i][1]==0) type_q="日常";
        if(memo_num[i][1]==1) type_q="学习";
        if(memo_num[i][1]==2) type_q="娱乐";
        if(memo_num[i][1]==3) type_q="其他";

        ui->memo->setItem(i,1,new QTableWidgetItem(type_q));
        ui->memo->setItem(i,2,new QTableWidgetItem(memo_qs[i][0]));
    }
    ui->memo->show();
}

int MainWindow::get_today(int a, int b)
{
    int num;
    if(a>0 && a<date_finishrow){
        return num=a*7+b+date_different;
    }
    else if(a==0 && b>=date_startdate){
        return num=a*7+b+date_different;
    }
    else if(a==date_finishrow && b<=date_finishdate){
        return num=a*7+b+date_different;
    }
    else return -1;
}

void MainWindow::analyze_memo(int& hour , int& minute , int& type,std::string content)
{
    int hour_flag=0;
    int minute_flag=0;
    int receving=0;
    int type_flag=0;
    std::string hour_s="";
    std::string minute_s="";
    std::string type_s="";

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
}

void MainWindow::sort_memo()
{
    for (int j=0;j<memo_size-1;j++){
        for (int i=0;i<memo_size-1-j;i++){
            if (memo_num[i][0]>memo_num[i+1][0]){
                int temp=0;
                temp=memo_num[i][0];
                memo_num[i][0]=memo_num[i+1][0];
                memo_num[i+1][0]=temp;
                temp=memo_num[i][1];
                memo_num[i][1]=memo_num[i+1][1];
                memo_num[i+1][1]=temp;

                swap(memo_qs[i][0],memo_qs[i+1][0]);
                swap(memo_qs[i][1],memo_qs[i+1][1]);
            }
        }
    }
}

void MainWindow::reset_memo()
{
    for(int i=0;i<100;i++){
        for(int j=0;j<2;j++){
            memo_qs[i][j]="";
            memo_num[i][j]=0;
        }
    }
    memo_size=0;
}

void MainWindow::tv_show()
{
    reset_tv();
    QDir temp;
    if(!temp.exists(location+"/tv")){
        QMessageBox::about(this,"warning","找不到目标文件夹");
        return;
    }
    QFile file(location+"/tv"+"/tv.txt");
    int count=0;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        for(int i=0;!file.atEnd();i++){
            QString str = file.readLine();
            count++;
        }
        file.close();
    }
    tv_size=count/2;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        for(int i=0;i<tv_size;i++){
            QString content=read.readLine();
            analyze_tv(tv_num[i][0],tv_num[i][1],q2s(content));
            tv_name[i]=read.readLine();
        }
        file.close();
    }
    ui->tv->setRowCount(tv_size);
    ui->tv->setColumnCount(3);
    ui->tv->verticalHeader()->setVisible(false);
    QStringList horizontitle;
    horizontitle << "剧名" << "季数" << "集数";
    ui->tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv->setHorizontalHeaderLabels(horizontitle);
    ui->tv->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    ui->tv->setColumnWidth(0,110);
    ui->tv->setColumnWidth(1,48);
    ui->tv->setColumnWidth(2,48);
    for(int i=0;i<tv_size;i++){
        ui->tv->setRowHeight(i,22);
    }
    for(int i=0;i<tv_size;i++){
        ui->tv->setItem(i,0,new QTableWidgetItem(tv_name[i]));
        QString season="";
        QString chapter="";
        if(tv_num[i][1]<0){
            season = "完结";
            chapter = "完结";
        }
        else {
            season=s2q(std::to_string(tv_num[i][0]));
            chapter=s2q(std::to_string(tv_num[i][1]));
        };
        ui->tv->setItem(i,1,new QTableWidgetItem(season));
        ui->tv->setItem(i,2,new QTableWidgetItem(chapter));
    }
}

void MainWindow::analyze_tv(int& season, int& chapter, std::string content)
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

void MainWindow::reset_tv()
{
    for(int i=0;i<300;i++){
        tv_name[i]="";
        for(int j=0;j<2;j++){
            tv_num[i][j]=0;
        }
    }
    tv_size=0;
}

void MainWindow::get_popup()
{
    QFile file(location+"/memo/settings.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream read(&file);
        QString content=read.readLine();
        if(content[0]=='0'){
            popup_flag=0;
        }
        else if(content[0]=='1'){
            popup_flag=1;
        }
        QString content2=read.readLine();
        if(content2[0]=='0'){
            music_flag=0;
        }
        else if(content2[0]=='1'){
            music_flag=1;
        }
        file.close();
    }
}

void MainWindow::set_wallpaper()
{
    if(month==12 && day==28){
        this->setStyleSheet("#MainWindow { border-image: url(:/image/image/77.jpg);}#MainWindow * { border-image:url(); };");
    }
    else if(month==5 && day==6){
        this->setStyleSheet("#MainWindow { border-image: url(:/image/image/66.jpg);}#MainWindow * { border-image:url(); };");
    }
    else if(month==6 && day==14){
        this->setStyleSheet("#MainWindow { border-image: url(:/image/image/66.jpg);}#MainWindow * { border-image:url(); };");
    }
    else if(month==8 && day==1){
        this->setStyleSheet("#MainWindow { border-image: url(:/image/image/66.jpg);}#MainWindow * { border-image:url(); };");
    }
    else if(month==5 && day==23){
        this->setStyleSheet("#MainWindow { border-image: url(:/image/image/66.jpg);}#MainWindow * { border-image:url(); };");
    }
    else if(month==4 && day==24){
        this->setStyleSheet("#MainWindow { border-image: url(:/image/image/66.jpg);}#MainWindow * { border-image:url(); };");
    }
    else{
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        int n = qrand()%10;
        if(n==0){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/10.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==1){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/1.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==2){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/2.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==3){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/3.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==4){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/4.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==5){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/5.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==6){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/6.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==7){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/7.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==8){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/8.jpg);}#MainWindow * { border-image:url(); };");
        }
        else if(n==9){
            this->setStyleSheet("#MainWindow { border-image: url(:/image/image/9.jpg);}#MainWindow * { border-image:url(); };");
        }
    }
}

void MainWindow::set_checked()
{
    ui->pushButton_0_0->setCheckable(true);
    ui->pushButton_0_1->setCheckable(true);
    ui->pushButton_0_2->setCheckable(true);
    ui->pushButton_0_3->setCheckable(true);
    ui->pushButton_0_4->setCheckable(true);
    ui->pushButton_0_5->setCheckable(true);
    ui->pushButton_0_6->setCheckable(true);
    ui->pushButton_1_0->setCheckable(true);
    ui->pushButton_1_1->setCheckable(true);
    ui->pushButton_1_2->setCheckable(true);
    ui->pushButton_1_3->setCheckable(true);
    ui->pushButton_1_4->setCheckable(true);
    ui->pushButton_1_5->setCheckable(true);
    ui->pushButton_1_6->setCheckable(true);
    ui->pushButton_2_0->setCheckable(true);
    ui->pushButton_2_1->setCheckable(true);
    ui->pushButton_2_2->setCheckable(true);
    ui->pushButton_2_3->setCheckable(true);
    ui->pushButton_2_4->setCheckable(true);
    ui->pushButton_2_5->setCheckable(true);
    ui->pushButton_2_6->setCheckable(true);
    ui->pushButton_3_0->setCheckable(true);
    ui->pushButton_3_1->setCheckable(true);
    ui->pushButton_3_2->setCheckable(true);
    ui->pushButton_3_3->setCheckable(true);
    ui->pushButton_3_4->setCheckable(true);
    ui->pushButton_3_5->setCheckable(true);
    ui->pushButton_3_6->setCheckable(true);
    ui->pushButton_4_0->setCheckable(true);
    ui->pushButton_4_1->setCheckable(true);
    ui->pushButton_4_2->setCheckable(true);
    ui->pushButton_4_3->setCheckable(true);
    ui->pushButton_4_4->setCheckable(true);
    ui->pushButton_4_5->setCheckable(true);
    ui->pushButton_4_6->setCheckable(true);
    ui->pushButton_5_0->setCheckable(true);
    ui->pushButton_5_1->setCheckable(true);
    ui->pushButton_5_2->setCheckable(true);
    ui->pushButton_5_3->setCheckable(true);
    ui->pushButton_5_4->setCheckable(true);
    ui->pushButton_5_5->setCheckable(true);
    ui->pushButton_5_6->setCheckable(true);
}

void MainWindow::set_music()
{
    player = new QMediaPlayer();
    player->setMedia(QUrl::fromLocalFile(location+"/music/2.mp3"));
    player->setVolume(100);
    if(music_flag==1){
        player->play();
    }
}

void MainWindow::on_action_triggered()
{
    calculate a;
    a.exec();
}

void MainWindow::on_text_save_clicked()
{
    QFile file(location+"/dialy"+"/"+dialyname);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        QString content = ui->textEdit->toPlainText();
        content.replace(QString(s2q(std::to_string(year)+"."+std::to_string(month)+"."
                                +std::to_string(date_gonna_print))+"\n"
                                +"---------------------------------------\n"),QString(""));
        content.replace(QString("\n"), QString("\r\n"));
        out<<content;
    }
    file.close();
}

void MainWindow::on_memo_save_clicked()
{
    memo_save a(this,year,month,day);
    a.exec();
    textedit_show();
    memo_show();
}

void MainWindow::memo_doubleclicked(int row, int col)
{
    QString location_memo_c=location+"/memo/"+s2q(std::to_string(year)+"."+std::to_string(month)+"."
                                         +std::to_string(date_gonna_print)+".memo")+".txt";
    int num=year*10000+month*100+day;
    memo_c a(this,memo_num[row][0],memo_num[row][1],memo_qs[row][0],memo_qs[row][1],location_memo_c,num);
    a.exec();
    memo_show();
}

void MainWindow::tv_doubleclicked(int row, int col)
{
    tv a(this,tv_name[row],tv_num[row][0],tv_num[row][1],location+"/tv/tv.txt");
    a.exec();
    tv_show();
}

void MainWindow::on_TV_save_clicked()
{
    tv_input a(this,location+"/tv/tv.txt");
    a.exec();
    tv_show();
}

void MainWindow::on_actionTixing_triggered()
{
    popup a(this);
    a.exec();
    memo_show();
}

void MainWindow::on_pushButton_0_0_clicked()
{
    reset_memo();
    day=get_today(0,0);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_0_1_clicked()
{
    reset_memo();
    day=get_today(0,1);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_0_2_clicked()
{
    reset_memo();
    day=get_today(0,2);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_0_3_clicked()
{
    reset_memo();
    day=get_today(0,3);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_0_4_clicked()
{
    reset_memo();
    day=get_today(0,4);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_0_5_clicked()
{
    reset_memo();
    day=get_today(0,5);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_0_6_clicked()
{
    reset_memo();
    day=get_today(0,6);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_1_0_clicked()
{
    reset_memo();
    day=get_today(1,0);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_1_1_clicked()
{
    reset_memo();
    day=get_today(1,1);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_1_2_clicked()
{
    reset_memo();
    day=get_today(1,2);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_1_3_clicked()
{
    reset_memo();
    day=get_today(1,3);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_1_4_clicked()
{
    reset_memo();
    day=get_today(1,4);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_1_5_clicked()
{
    reset_memo();
    day=get_today(1,5);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_1_6_clicked()
{
    reset_memo();
    day=get_today(1,6);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_2_0_clicked()
{
    reset_memo();
    day=get_today(2,0);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_2_1_clicked()
{
    reset_memo();
    day=get_today(2,1);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_2_2_clicked()
{
    reset_memo();
    day=get_today(2,2);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_2_3_clicked()
{
    reset_memo();
    day=get_today(2,3);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_2_4_clicked()
{
    reset_memo();
    day=get_today(2,4);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_2_5_clicked()
{
    reset_memo();
    day=get_today(2,5);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_2_6_clicked()
{
    reset_memo();
    day=get_today(2,6);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_3_0_clicked()
{
    reset_memo();
    day=get_today(3,0);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_3_1_clicked()
{
    reset_memo();
    day=get_today(3,1);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_3_2_clicked()
{
    reset_memo();
    day=get_today(3,2);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_3_3_clicked()
{
    reset_memo();
    day=get_today(3,3);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_3_4_clicked()
{
    reset_memo();
    day=get_today(3,4);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_3_5_clicked()
{
    reset_memo();
    day=get_today(3,5);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_3_6_clicked()
{
    reset_memo();
    day=get_today(3,6);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_4_0_clicked()
{
    reset_memo();
    day=get_today(4,0);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_4_1_clicked()
{
    reset_memo();
    day=get_today(4,1);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_4_2_clicked()
{
    reset_memo();
    day=get_today(4,2);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_4_3_clicked()
{
    reset_memo();
    day=get_today(4,3);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_4_4_clicked()
{
    reset_memo();
    day=get_today(4,4);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_4_5_clicked()
{
    reset_memo();
    day=get_today(4,5);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_4_6_clicked()
{
    reset_memo();
    day=get_today(4,6);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_5_0_clicked()
{
    reset_memo();
    day=get_today(5,0);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_5_1_clicked()
{
    reset_memo();
    day=get_today(5,1);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_5_2_clicked()
{
    reset_memo();
    day=get_today(5,2);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_5_3_clicked()
{
    reset_memo();
    day=get_today(5,3);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_5_4_clicked()
{
    reset_memo();
    day=get_today(5,4);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_5_5_clicked()
{
    reset_memo();
    day=get_today(5,5);
    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}

void MainWindow::on_pushButton_5_6_clicked()
{
    day=get_today(5,6);
    reset_memo();

    textedit_show();
    memo_show();
    set_wallpaper();
    refresh_allbutton();
}
void MainWindow::on_pushButton_play_clicked()
{
    player->play();
}

void MainWindow::on_pushButton_pause_clicked()
{
    player->pause();
}

void MainWindow::on_pushButton_stop_clicked()
{
    player->stop();
}

void MainWindow::on_action_2_triggered()
{
    settings a(this);
    a.exec();
}

void MainWindow::on_action_code_triggered()
{
    code a(this);
    a.exec();
}
