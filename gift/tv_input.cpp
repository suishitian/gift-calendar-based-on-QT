#include "tv_input.h"
#include "ui_tv_input.h"

#include <QFile>
#include <QTextStream>

QString tv_input::s2q(const std::string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

std::string tv_input::q2s(const QString &s)
{
    return std::string((const char *)s.toLocal8Bit());
}

tv_input::tv_input(QWidget *parent, QString location_tv) :
    QDialog(parent),
    location_tv(location_tv),
    ui(new Ui::tv_input)
{
    ui->setupUi(this);
    ui->spinBox_chapter->setRange(1,10000);
    ui->spinBox_season->setRange(1,10000);
    ui->spinBox_chapter->setValue(1);
    ui->spinBox_season->setValue(1);
    ui->lineEdit->setText("请输入~");
}

tv_input::~tv_input()
{
    delete ui;
}

void tv_input::on_buttonBox_accepted()
{
    season=ui->spinBox_season->value();
    chapter=ui->spinBox_chapter->value();
    tv_name=ui->lineEdit->text();

    QFile file(location_tv);
    if(file.open(QIODevice::Append|QIODevice::Text)){
        QTextStream write(&file);
        QString content = s2q(std::to_string(season)+" "+std::to_string(chapter)+"\r\n"+q2s(tv_name)+"\r\n");
        write<<content;
        file.close();
    }
    this->close();
}
