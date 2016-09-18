#include <stdio.h>
#include <string.h>
void get_month_name (int month, char *month_name) {
    if (month == 1) strcpy(month_name, "January");
    if (month == 2) strcpy(month_name, "February");
    if (month == 3) strcpy(month_name, "March");
    if (month == 4) strcpy(month_name, "April");
    if (month == 5) strcpy(month_name, "May");
    if (month == 6) strcpy(month_name, "June");
    if (month == 7) strcpy(month_name, "July");
    if (month == 8) strcpy(month_name, "August");
    if (month == 9) strcpy(month_name, "September");
    if (month == 10) strcpy(month_name, "October");
    if (month == 11) strcpy(month_name, "November");
    if (month == 12) strcpy(month_name, "December");
}

int main(void) {
    int day, month, year, input;
    char month_name[10];
    printf("Enter date(ddmmyy): ");
    scanf("%d", &input);
    day = (input / 10000) % 100;
    month = (input / 100) % 100;
    year = input % 100;
    if (year < 50) year = 2000 + year;
    else year = 2000 - year;
    get_month_name(month, month_name);
    printf("%s %d, %d\n", month_name, day, year);
    return 0;
}