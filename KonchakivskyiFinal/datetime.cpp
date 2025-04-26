#include "datetime.h"
#include <ctime>
#include <iomanip>
#include <sstream>


Date::Date() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    year = 1900 + ltm.tm_year;
    month = 1 + ltm.tm_mon;
    day = ltm.tm_mday;
}

Date::Date(int d, int m, int y) {
    if (!setDate(d, m, y)) {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        year = 1900 + ltm.tm_year;
        month = 1 + ltm.tm_mon;
        day = ltm.tm_mday;
    }
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int m, int y) const {
    if (m < 1 || m > 12) return 0;

    static const int daysPerMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isLeapYear(y))
        return 29;
    return daysPerMonth[m];
}

bool Date::isValidDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m > 12 || d < 1)
        return false;

    return d <= daysInMonth(m, y);
}

bool Date::setDay(int d) {
    if (isValidDate(d, month, year)) {
        day = d;
        return true;
    }
    return false;
}

bool Date::setMonth(int m) {
    if (m >= 1 && m <= 12) {
        int maxDay = daysInMonth(m, year);
        if (day > maxDay) {
            day = maxDay;
        }
        month = m;
        return true;
    }
    return false;
}

bool Date::setYear(int y) {
    if (y >= 1) {
        year = y;

        if (month == 2 && day == 29 && !isLeapYear(y)) {
            day = 28;
        }
        return true;
    }
    return false;
}

bool Date::setDate(int d, int m, int y) {
    if (isValidDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
        return true;
    }
    return false;
}

// Zeller's Congruence
int Date::getDayOfWeekNumber() const {
    int q = day;
    int m = month;
    int y = year;

    if (m == 1 || m == 2) {
        m += 12;
        y--;
    }

    int h = (q + 13 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;

    return (h + 6) % 7;
}

std::string Date::getDayOfWeek() const {
    static const std::string dayNames[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    return dayNames[getDayOfWeekNumber()];
}

Date& Date::operator++() {
    *this += 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp(*this);
    ++(*this);
    return temp;
}

Date& Date::operator--() {
    *this -= 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp(*this);
    --(*this);
    return temp;
}

Date& Date::operator+=(int days) {
    if (days < 0) {
        return *this -= -days;
    }

    while (days > 0) {
        int daysInCurrentMonth = daysInMonth(month, year);
        if (day + days <= daysInCurrentMonth) {
            day += days;
            days = 0;
        }
        else {
            days -= (daysInCurrentMonth - day + 1);
            day = 1;
            if (month == 12) {
                month = 1;
                year++;
            }
            else {
                month++;
            }
        }
    }

    return *this;
}

Date& Date::operator-=(int days) {
    if (days < 0) {
        return *this += -days;
    }

    while (days > 0) {
        if (day > days) {
            day -= days;
            days = 0;
        }
        else {
            days -= day;
            if (month == 1) {
                month = 12;
                year--;
            }
            else {
                month--;
            }
            day = daysInMonth(month, year);
        }
    }

    return *this;
}

Date Date::operator+(int days) const {
    Date result(*this);
    result += days;
    return result;
}

Date Date::operator-(int days) const {
    Date result(*this);
    result -= days;
    return result;
}

int Date::operator-(const Date& other) const {
    int sign = 1;
    Date start(*this), end(other);

    if (*this < other) {
        sign = -1;
        start = other;
        end = *this;
    }

    int days = 0;
    while (start != end) {
        --start;
        ++days;
    }

    return sign * days;
}

bool Date::operator==(const Date& other) const {
    return (day == other.day && month == other.month && year == other.year);
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator<=(const Date& other) const {
    return !(other < *this);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

void Date::display() const {
    std::cout << *this;
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "/"
        << std::setfill('0') << std::setw(2) << month << "/"
        << year;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << std::setfill('0') << std::setw(2) << date.day << "/"
        << std::setfill('0') << std::setw(2) << date.month << "/"
        << date.year << " (" << date.getDayOfWeek() << ")";
    return os;
}

Time::Time() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    hour = ltm.tm_hour;
    minute = ltm.tm_min;
    second = ltm.tm_sec;
}

Time::Time(int h, int m, int s) {
    if (!setTime(h, m, s)) {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        hour = ltm.tm_hour;
        minute = ltm.tm_min;
        second = ltm.tm_sec;
    }
}
Time::Time(const Time& other) : hour(other.hour), minute(other.minute), second(other.second) {}

bool Time::isValidTime(int h, int m, int s) const {
    return (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60);
}

bool Time::setHour(int h) {
    if (h >= 0 && h < 24) {
        hour = h;
        return true;
    }
    return false;
}

bool Time::setMinute(int m) {
    if (m >= 0 && m < 60) {
        minute = m;
        return true;
    }
    return false;
}

bool Time::setSecond(int s) {
    if (s >= 0 && s < 60) {
        second = s;
        return true;
    }
    return false;
}

bool Time::setTime(int h, int m, int s) {
    if (isValidTime(h, m, s)) {
        hour = h;
        minute = m;
        second = s;
        return true;
    }
    return false;
}

Time& Time::operator++() {
    *this += 1;
    return *this;
}

Time Time::operator++(int) {
    Time temp(*this);
    ++(*this);
    return temp;
}

Time& Time::operator--() {
    *this -= 1;
    return *this;
}

Time Time::operator--(int) {
    Time temp(*this);
    --(*this);
    return temp;
}

Time& Time::operator+=(int seconds) {
    if (seconds < 0) {
        return *this -= -seconds;
    }

    int totalSeconds = hour * 3600 + minute * 60 + second + seconds;
    int days = totalSeconds / (24 * 3600);
    totalSeconds %= (24 * 3600);

    hour = totalSeconds / 3600;
    totalSeconds %= 3600;
    minute = totalSeconds / 60;
    second = totalSeconds % 60;

    return *this;
}

Time& Time::operator-=(int seconds) {
    if (seconds < 0) {
        return *this += -seconds;
    }

    int totalSeconds = hour * 3600 + minute * 60 + second - seconds;

    while (totalSeconds < 0) {
        totalSeconds += 24 * 3600;
    }

    hour = totalSeconds / 3600;
    totalSeconds %= 3600;
    minute = totalSeconds / 60;
    second = totalSeconds % 60;

    return *this;
}

Time Time::operator+(int seconds) const {
    Time result(*this);
    result += seconds;
    return result;
}

Time Time::operator-(int seconds) const {
    Time result(*this);
    result -= seconds;
    return result;
}

int Time::operator-(const Time& other) const {
    int thisTotalSeconds = hour * 3600 + minute * 60 + second;
    int otherTotalSeconds = other.hour * 3600 + other.minute * 60 + other.second;

    return thisTotalSeconds - otherTotalSeconds;
}

bool Time::operator==(const Time& other) const {
    return (hour == other.hour && minute == other.minute && second == other.second);
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<(const Time& other) const {
    if (hour != other.hour) return hour < other.hour;
    if (minute != other.minute) return minute < other.minute;
    return second < other.second;
}

bool Time::operator>(const Time& other) const {
    return other < *this;
}

bool Time::operator<=(const Time& other) const {
    return !(other < *this);
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}

void Time::display() const {
    std::cout << *this;
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setfill('0') << std::setw(2) << minute << ":"
        << std::setfill('0') << std::setw(2) << second;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setfill('0') << std::setw(2) << time.hour << ":"
        << std::setfill('0') << std::setw(2) << time.minute << ":"
        << std::setfill('0') << std::setw(2) << time.second;
    return os;
}