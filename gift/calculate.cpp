#include "calculate.h"
#include "ui_calculate.h"
#include <math.h>
#include <QDebug>

calculate::calculate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calculate)
{
    ui->setupUi(this);
    this->setWindowTitle("计算器\0");
    ui->lineEdit_up->setAlignment(Qt::AlignRight);
    ui->lineEdit_up->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_down->setAlignment(Qt::AlignRight);
    ui->lineEdit_down->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_up->setText("0");
    ui->lineEdit_down->setText("0");
}

QString calculate::s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string calculate::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

calculate::~calculate()
{
    delete ui;
}

void calculate::refresh_lineedit()
{
    ui->lineEdit_up->setText(s2q(last_string));
    ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
}


void calculate::on_pushButton_AC_clicked()
{
    last_string="";
    last_value=0;
    store_value=0;
    flag=0;
    point=0;
    ui->lineEdit_up->setText("0");
    ui->lineEdit_down->setText("0");

}

void calculate::on_pushButton_num1_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*1;
    }
    else if(point==0){
        store_value=store_value*10+1;
    }
    last_string=last_string+"1";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num2_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*2;
    }
    else if(point==0){
        store_value=store_value*10+2;
    }
    last_string=last_string+"2";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num3_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*3;
    }
    else if(point==0){
        store_value=store_value*10+3;
    }
    last_string=last_string+"3";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num4_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*4;
    }
    else if(point==0){
        store_value=store_value*10+4;
    }
    last_string=last_string+"4";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num5_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*5;
    }
    else if(point==0){
        store_value=store_value*10+5;
    }
    last_string=last_string+"5";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num6_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*6;
    }
    else if(point==0){
        store_value=store_value*10+6;
    }
    last_string=last_string+"6";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num7_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*7;
    }
    else if(point==0){
        store_value=store_value*10+7;
    }
    last_string=last_string+"7";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num8_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*8;
    }
    else if(point==0){
        store_value=store_value*10+8;
    }
    last_string=last_string+"8";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num9_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*9;
    }
    else if(point==0){
        store_value=store_value*10+9;
    }
    last_string=last_string+"9";

    refresh_lineedit();
    qDebug()<<store_value;
}

void calculate::on_pushButton_num0_clicked()
{
    if(end==1){
        calculate::on_pushButton_AC_clicked();
        end=0;
    }
    if(point==1){
        click_time++;
        store_value=store_value+pow(10,-click_time)*0;
    }
    else if(point==0){
        store_value=store_value*10+0;
    }
    last_string=last_string+"0";

    refresh_lineedit();
    qDebug()<<store_value;
}


void calculate::on_pushButton_plus_clicked()
{
    end=0;
    if(flag!=0){
        if(flag==1){
            last_value=last_value+store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==2){
            last_value=last_value-store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==3){
            last_value=last_value*store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==4){
            last_value=last_value/store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==5){

        }
    }
    else if(flag==0 && last_value==0 && store_value==0){
        return;
    }
    else if(last_value==0 && store_value!=0 && flag==0){
        last_value=store_value;
        store_value=0;
    }
    last_string=last_string+"+";
    flag=1;
    point=0;
    click_time=0;
    refresh_lineedit();
}

void calculate::on_pushButton_minus_clicked()
{
    end=0;
    if(flag!=0){
        if(flag==1){
            last_value=last_value+store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==2){
            last_value=last_value-store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==3){
            last_value=last_value*store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==4){
            last_value=last_value/store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==5){

        }
    }
    else if(flag==0 && last_value==0 && store_value==0){
        return;
    }
    else if(last_value==0 && store_value!=0 && flag==0){
        last_value=store_value;
        store_value=0;
    }
    last_string=last_string+"-";
    flag=2;
    point=0;
    click_time=0;
    refresh_lineedit();
}

void calculate::on_pushButton_time_clicked()
{
    end=0;
    if(flag!=0){
        if(flag==1){
            last_value=last_value+store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==2){
            last_value=last_value-store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==3){
            last_value=last_value*store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==4){
            last_value=last_value/store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==5){

        }
    }
    else if(flag==0 && last_value==0 && store_value==0){
        return;
    }
    else if(last_value==0 && store_value!=0 && flag==0){
        last_value=store_value;
        store_value=0;
    }
    last_string="("+last_string+")"+"*";
    flag=3;
    point=0;
    click_time=0;
    refresh_lineedit();
}

void calculate::on_pushButton_devide_clicked()
{
    end=0;
    if(flag!=0){
        if(flag==1){
            last_value=last_value+store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==2){
            last_value=last_value-store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==3){
            last_value=last_value*store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==4){
            last_value=last_value/store_value;
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==5){

        }
    }
    else if(flag==0 && last_value==0 && store_value==0){
        return;
    }
    else if(last_value==0 && store_value!=0 && flag==0){
        last_value=store_value;
        store_value=0;
    }
    last_string="("+last_string+")"+"/";
    flag=4;
    point=0;
    click_time=0;
    refresh_lineedit();
}


void calculate::on_pushButton_equal_clicked()
{
    if(flag!=0){
        if(flag==1){
            last_value=last_value+store_value;
            last_string=std::to_string(last_value);
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==2){
            last_value=last_value-store_value;
            last_string=std::to_string(last_value);
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==3){
            last_value=last_value*store_value;
            last_string=std::to_string(last_value);
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
        else if(flag==4){
            last_value=last_value/store_value;
            last_string=std::to_string(last_value);
            ui->lineEdit_down->setText(s2q(std::to_string(last_value)));
            store_value=0;
        }
    }
    else if(flag==0 && last_value==0 && store_value==0){
        return;
    }
    else if(last_value==0 && store_value!=0 && flag==0){
        last_value=store_value;
        store_value=0;
    }

    point=0;
    click_time=0;
    end=1;
    flag=5;
    refresh_lineedit();
}

void calculate::on_pushButton_point_clicked()
{
    if(point==0){
        point=1;
        last_string=last_string+".";
    }
    refresh_lineedit();
}
