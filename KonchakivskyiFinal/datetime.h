#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    bool isValidDate(int d, int m, int y) const;
    int daysInMonth(int m, int y) const;
    bool isLeapYear(int y) const;

public:
    Date();
    Date(int d, int m, int y);
    Date(const Date& other);

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getDaysInMonth(int m,int y) const {
        return daysInMonth(m, y);
    }

    bool setDay(int d);
    bool setMonth(int m);
    bool setYear(int y);
    bool setDate(int d, int m, int y);

    std::string getDayOfWeek() const;
    int getDayOfWeekNumber() const;

    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    Date& operator+=(int days);
    Date& operator-=(int days);
    Date operator+(int days) const;
    Date operator-(int days) const;
    int operator-(const Date& other) const;

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;

    void display() const;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

class Time {
private:
    int hour;
    int minute;
    int second;

    bool isValidTime(int h, int m, int s) const;

public:
    Time();
    Time(int h, int m, int s);
    Time(const Time& other);

    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    bool setHour(int h);
    bool setMinute(int m);
    bool setSecond(int s);
    bool setTime(int h, int m, int s);

    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);

    Time& operator+=(int seconds);
    Time& operator-=(int seconds);
    Time operator+(int seconds) const;
    Time operator-(int seconds) const;
    int operator-(const Time& other) const;

    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;

    void display() const;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif