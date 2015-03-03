#include "hebdate.h"

HDate::HDate(QObject *parent) :
    QObject(parent)
{
    init =0;
}

HDate::~HDate() {

}

hdate_struct HDate::weekStart(hdate_struct h)
{
    hdate_set_hdate (&h, 1, h.hd_mon, h.hd_year);
    int jd_current_month = h.hd_jd - h.hd_dw + 1;
    hdate_struct h1;
    hdate_set_jd (&h1, jd_current_month);
    return h1;
}

int HDate::daysInMonth(hdate_struct h)
{
    switch (h.hd_mon) {
    case 1:
        return 30;
        break;
    case 2:
        if(h.hd_size_of_year==355||h.hd_size_of_year==385){
            return 30;
        }else{
            return 29;
        }
        break;
    case 3:
        if(h.hd_size_of_year==353||h.hd_size_of_year==383){
            return 29;
        }else{
            return 30;
        }
        break;
    case 4:
        return 29;
        break;
    case 5:
        return 30;
        break;
    case 6:
        return 29;
        break;
    case 7:
        return 30;
        break;
    case 8:
        return 29;
        break;
    case 9:
        return 30;
        break;
    case 10:
        return 29;
        break;
    case 11:
        return 30;
        break;
    case 12:
        return 29;
        break;
    case 13:
        return 30;
        break;
    case 14:
        return 29;
        break;
    default:
        break;
    }
}

QString HDate::intToHebStr(int n)
{
    return (hdate_get_int_string(n));

}

hdate_struct HDate::nextMonth()
{
    int m =current_h.hd_mon;
    int y=current_h.hd_year;
    hdate_struct h_t;
    if(m==12){
        y=y+1;
        m=1;
    }else if(is_leap_year(y)&&m==5){
        m=13;
    }else if(m==13){
        m=14;
    }else if(m==14){
        m=7;
    }else{
        m=m+1;
    }
    hdate_set_hdate(&h_t,1,m,y);
    current_h=h_t;

    emit currentMonthStrChanged();
    return(h_t);
}

hdate_struct HDate::previousMonth()
{
   int  m =current_h.hd_mon;
   int  y=current_h.hd_year;
    hdate_struct h_t;
    if(m==1){
        y=y-1;
        m=12;
    }else if(is_leap_year(y)&&m==7){
        m=14;
    }else if(m==13){
        m=5;
    }else if(m==14){
        m=13;
    }else{
        m=m-1;
    }
    hdate_set_hdate(&h_t,1,m,y);
    current_h=h_t;

    emit currentMonthStrChanged();
    return(h_t);
}

QString HDate::currentMonthStr()
{
    if(!init){
        today();
        init=1;
    }

    QString m =hdate_get_hebrew_month_string(current_h.hd_mon,0);
    QString y =hdate_get_int_string(current_h.hd_year);

    return m + " "+y;
}

hdate_struct HDate::today()
{
    hdate_set_gdate (&today_h, 0, 0, 0);
    current_h=today_h;
    init =1;
    return today_h;
}

hdate_struct HDate::currentDate()
{
    return current_h;
}
int HDate::is_leap_year(int year){
    int length_of_year;
    int days_from_3744;

    days_from_3744 = hdate_days_from_3744 (year);
    length_of_year = hdate_days_from_3744 (year + 1) - days_from_3744;
    if (length_of_year>365){
        return 1;
    }
    return 0;
}
