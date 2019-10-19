#include <stdio.h>
#include <string.h>

//On leap years Months[1] is changed to 29 --> monthDayCount
const int Months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef struct {
    int year;
    int month;
    int day;
} Date;

int isLeapYear(int);
int monthDayCount(int, int);
int tryFormatDate(Date *, const char []);
int isDateCorrect(Date *, const char [], int);
void askDate(Date *);
void askDate(Date *);
int whichIsEarlier(Date *, Date *);
int calculateDayDifference(Date *, Date *);
void differenceBetweenDates(void);

int main(void){
    differenceBetweenDates();
    return(0);
}

int isLeapYear(int year){
    int is = 0;
    if (year % 400 == 0) is = 1;
    else if (year % 100 == 0) is = 0;
    else if (year % 4 == 0) is = 1;
    return is;
}

int monthDayCount(int year, int month){
    int days;
    if (month == 2){
        if (isLeapYear(year)) days = 29;
        else days = 28;
    }
    else days = Months[month-1];
    return days;
}

int tryFormatDate(Date *date, const char arr[]){
    char cD[2], cM[2], cY[4];
    int days, formatted = 0;
    memcpy(cD, arr, sizeof(cD));
    memcpy(cM, arr+3, sizeof(cM));
    memcpy(cY, arr+6, sizeof(cY));
    sscanf(cD, "%2d", &date->day);
    sscanf(cM, "%2d", &date->month);
    sscanf(cY, "%4d", &date->year);
    if (date->month > 0 && date->month <= 12){
        days = monthDayCount(date->year, date->month);
        if (date->day > 0 && date->day <= days) formatted = 1;
        else printf("Invalid day : %d | %d/%d --> 1-%d days\n",
            date->day, date->month, date->year, monthDayCount(date->year, date->month));
    }
    else printf("Invalid month : %d | Month --> 1-12\n", date->month);
    return formatted;
}

int isDateCorrect(Date *date, const char arr[], int size){
    int y, m, d, separator = 0, valid = 0, index[2] = {0};
    for (int i = 0; i < size; i++){
        if (arr[i] == '/') {
            if (separator > 1) break;
            index[separator] = i;
            separator++;
        }
        else if (arr[i] < '0' || arr[i] > '9') {
            break;
        }
    }
    if (index[0] == 2 && index[1] == 5){
        valid = tryFormatDate(date, arr);
    }
    return valid;
}

void askDate(Date *ymd){
    int max = 11;
    char arr[max];
    while(1){
        printf("Enter date (format: DD/MM/YYYY) > ");
        fgets(arr, max, stdin);
        if (isDateCorrect(ymd, arr, max-1)) break;
        else printf("Invalid date.\n");
    }
    while(fgetc(stdin) != '\n');
}

int whichIsEarlier(Date *d1, Date *d2){
    int d1IsEarlier = 1;
    if (d1->year == d2->year){
        if (d1->month == d2->month){
            d1IsEarlier = (d1->day < d2->day) ? 1 : 0;
        }
        else d1IsEarlier = (d1->month < d2->month) ? 1 : 0;
    }
    else d1IsEarlier = (d1->year < d2->year) ? 1 : 0;

    return d1IsEarlier;
}

int calculateDayDifference(Date *start, Date *end){
    int days = 0;
    for (int y = start->year; y < end ->year; y++){
        if (isLeapYear(y)) days +=366;
        else days += 365;
    }
    for (int m = start->month + 1; m < end->month; m++){
        if (m == 2) days += monthDayCount(end->year, m);
        else days += Months[m-1];
    }
    if (start->month != end->month){
        days += monthDayCount(start->year, start->month) - start->day;
        days += end->day;
    }
    else{
        days += end->day - start->day;
    }
    return days;
}

void differenceBetweenDates(void){
    int days, startingErlier = 1;
    Date starting;
    Date ending;
    printf("Starting Date\n");
    askDate(&starting);
    printf("Ending Date\n");
    askDate(&ending);
    startingErlier = whichIsEarlier(&starting, &ending);
    if (startingErlier){
        days = calculateDayDifference(&starting, &ending);
        printf("Difference : %d days", days);
    }
    else{
        days = calculateDayDifference(&ending, &starting);
        printf("Difference : -%d days", days);
    }
}