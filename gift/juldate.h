#ifndef JULDATE_H
#define JULDATE_H


class JulDate{
private:
    int year;
    int month;
    int date;
    int hour;
    int minute;
    int second;

public:
    JulDate(int a=1993, int b=12, int c=28, int d=0, int e=0, int f=0);
    JulDate auto_promotion();


    int getYear();
    int getMonth();
    int getDay();
    int getweek();

    static JulDate now();
    static bool test_year(int a);
    static int dayofmonth(int year1, int month1);
    double getJuldate();
    int minus(JulDate c, JulDate d);

    void setYear(int);
    void setMonth(int);
};


#endif // JULDATE_H
