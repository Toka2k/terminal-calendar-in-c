#include<time.h>
#include<stdio.h>

#define daysInWeek 7
#define monthsPerYear 12

char days[daysInWeek][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
char months[monthsPerYear][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
int _months[] = {31,28,31,30,31,30,31,31,30,31,30,31};

enum _m{
	Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

enum _d{
	Mon, Tue, Wed, Thu, Fri, Sat, Sun
};

typedef struct {
	int day;
	int month;
	int year;
	char *sday;
	char *smonth;
} DATE;

char *getDay(DATE *date){
    int _day = date->day;

    for (int i = 0; i < date->month - 1; i++){
		 _day += _months[i];
    }

    int i = 0;

    do{
        if ((2024 - i) % 4 == 0){
			_day += 366;
	    } else {_day += 365;}
			i++;
        } while (date->year - i + 1 != 1970);

        _day %= 7;

        return days[_day];
}

DATE getDate(){
    DATE date;

    date.year = 1970;
    date.month = Jan;
    date.day = 1;

    time_t seconds = time(NULL); 

    do {
        if (date.year % 4 == 0){
            seconds -= 366 * 24 * 3600;
            date.year += 1;
            continue;
        }

        seconds -= 365 * 24 * 3600;
        date.year += 1;
    } while (seconds >= 365 * 24 * 3600 || seconds >= 366 * 24 * 3600);

    // get months
    if (date.year % 4 == 0){
		_months[1] = 29;
    }

    int i = 0;

	while (i < sizeof(_months) && seconds / (3600 * 24 * _months[i]) >= 1) {
        seconds -= 3600 * 24 * _months[i];
        date.month += 1;

        i++;
    }

    date.day += seconds / (3600 * 24);

	date.sday = getDay(&date);
	date.smonth = months[date.month - 1];

    //printf("%d %d %d\n%s %s\n", date.year, date.month, date.day, date.sday, date.smonth);

    return date;
}
