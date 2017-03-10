#include <iostream>
#include <time.h>
#include "juldate.h"


JulDate::JulDate(int a,int b,int c,int d,int e,int f):year(a),month(b),date(c),hour(d),minute(e),second(f){}

int JulDate::getweek(){
    JulDate base(1900,1,1,0,0,0);
    int days=JulDate::minus(*this,base);
    int week = days%7;
    switch (week){
        case 0 : { return 1;
                  break;}
        case 1 : { return 2;
                  break;}
        case 2 : { return 3;
                  break;}
        case 3 : { return 4;
                  break;}
        case 4 : { return 5;
                  break;}
        case 5 : { return 6;
                  break;}
        case 6 : { return 7;
                  break;}
   }
}

bool JulDate::test_year(int a){
    if (( a%100==0 && ((a/100)%4)==0) || ( a%100!=0 && a%4==0))
        return true;
    else return false;
}

int JulDate::dayofmonth(int year1,int month1){
    if (month1==2 && JulDate::test_year(year1))
        return 29;
    else if(month1==2)
        return 28;
    else if(month1==1||month1==3||month1==5||month1==7||month1==8||month1==10||month1==12)
        return 31;
    else if (month1==4||month1==6||month1==9||month1==11)
        return 30;
}

JulDate JulDate::auto_promotion(){
    JulDate a(this->year,this->month,this->date,this->hour,this->minute,this->second);
    int test=0;
    int month_test=0;
    if (a.second>=60){
        a.minute++;
        a.second=a.second-60;
        test=1;
    }
    if (a.minute>=60){
        a.hour++;
        a.minute=a.minute-60;
        test=1;
    }
    if (a.hour>=24){
        a.date++;
        a.hour=a.hour-24;
        test=1;
    }
    month_test= JulDate::dayofmonth(a.year,a.month);
    if (a.date>month_test){
        a.month++;
        a.date=a.date-month_test;
        test=1;
    }

    if(a.month>12){
        a.year++;
        a.month=a.month-12;
        test=1;
    }
    if(test>=1)
        return a.auto_promotion();
    else
        return a;
}

int JulDate::minus(JulDate c,JulDate d){
    JulDate a=c.auto_promotion();
    JulDate b=d.auto_promotion();
    int test=0;
    if (b.year>a.year){
        b=c.auto_promotion();
        a=d.auto_promotion();
        test++;
    }
    else if (b.year==a.year && b.month>a.month){
        b=c.auto_promotion();
        a=d.auto_promotion();
        test++;
    }
    else if (b.year==a.year && b.month==a.month && b.date>a.date){
        b=c.auto_promotion();
        a=d.auto_promotion();
        test++;
    }

    int year_day=0;
    for (int i=a.year-1;i>b.year;i--){
        if(JulDate::test_year(i))
            year_day=year_day+366;
        else
            year_day=year_day+365;
    }
    int month_day=0;
    if (a.year==b.year){
        for (int i=a.month-1;i>b.month;i--){
            month_day = month_day +JulDate::dayofmonth(a.year,i);
        }
    }
    else if(a.year!=b.year){
        for (int i=a.month-1;i>=1;i--){
            month_day = month_day + JulDate::dayofmonth(a.year,i);
        }
        for (int i=b.month+1;i<=12;i++){
            month_day = month_day + JulDate::dayofmonth(b.year,i);
        }
    }
    int date_day=0;
    if (a.year==b.year && a.month==b.month)
        date_day = a.date-b.date;
    else
        date_day = JulDate::dayofmonth(b.year,b.month) - b.date + a.date;
    if (test>=1)
        return -(year_day+month_day+date_day);
    else return year_day+month_day+date_day;
}

void JulDate::setYear(int a)
{
    this->year=a;
}

void JulDate::setMonth(int a)
{
    this->month=a;
}

int JulDate::getYear(){
    JulDate c=this->auto_promotion();
    return c.year;
}

int JulDate::getMonth(){
    JulDate c=this->auto_promotion();
    return c.month;
}

int JulDate::getDay(){
    JulDate c=this->auto_promotion();
    return c.date;
}

JulDate JulDate::now(){
    time_t timenow=time(NULL);
    tm* Jtime;
    Jtime=localtime(&timenow);
    JulDate a(Jtime->tm_year+1900,Jtime->tm_mon+1,Jtime->tm_mday,Jtime->tm_hour,Jtime->tm_min,Jtime->tm_sec);
    return a;

}

double JulDate::getJuldate(){
    JulDate a(this->year,this->month,this->date,this->hour,this->minute,this->second);
    JulDate c(2000,1,1,0,0,0);
    double totalsec=60*60*24;
    return minus(a,c)+(((double)this->hour * 60 * 60 + (double)this->minute*60 + (double)this->second)/totalsec);
}

