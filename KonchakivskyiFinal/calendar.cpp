#include "calendar.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Event::Event(const Date& date, const std::string& title,
    EventType type, EventPriority priority,
    const std::string& description)
    : date(date), hasTime(false), type(type), priority(priority),
    title(title), description(description) {
    time = Time(0, 0, 0);
}

Event::Event(const Date& date, const Time& time, const std::string& title,
    EventType type, EventPriority priority,
    const std::string& description)
    : date(date), time(time), hasTime(true), type(type), priority(priority),
    title(title), description(description) {
}

bool Event::operator<(const Event& other) const {
    if (date != other.date) {
        return date < other.date;
    }

    if (hasTime && other.hasTime) {
        return time < other.time;
    }

    return hasTime < other.hasTime;
}

bool Event::operator>(const Event& other) const {
    return other < *this;
}

bool Event::operator==(const Event& other) const {
    if (date != other.date) return false;
    if (hasTime != other.hasTime) return false;
    if (hasTime && time != other.time) return false;
    if (title != other.title) return false;
    return true;
}

bool Event::operator!=(const Event& other) const {
    return !(*this == other);
}

std::string Event::eventTypeToString(EventType type) {
    switch (type) {
    case EventType::MEETING: return "Meeting";
    case EventType::BIRTHDAY: return "Birthday";
    case EventType::HOLIDAY: return "Holiday";
    case EventType::OTHER: return "Other";
    default: return "Unknown";
    }
}

std::string Event::eventPriorityToString(EventPriority priority) {
    switch (priority) {
    case EventPriority::LOW: return "Low";
    case EventPriority::MEDIUM: return "Medium";
    case EventPriority::HIGH: return "High";
    default: return "Unknown";
    }
}

void Event::display() const {
    std::cout << *this;
}

std::string Event::toString() const {
    std::string result = date.toString();
    if (hasTime) {
        result += " " + time.toString();
    }
    result += " | " + title + " | " + eventTypeToString(type) +
        " | " + eventPriorityToString(priority);
    if (!description.empty()) {
        result += " | " + description;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << event.date;
    if (event.hasTime) {
        os << " " << event.time;
    }
    else {
        os << " (All day)";
    }

    os << " | " << event.title
        << " | Type: " << Event::eventTypeToString(event.type)
        << " | Priority: " << Event::eventPriorityToString(event.priority);

    if (!event.description.empty()) {
        os << " | Description: " << event.description;
    }

    return os;
}


Calendar::Calendar() : currentViewDate() {
}

Calendar::Calendar(const Date& initialViewDate) : currentViewDate(initialViewDate) {
}

void Calendar::addEvent(const Event& event) {
    events.push_back(event);
    std::sort(events.begin(), events.end());
}

bool Calendar::removeEvent(const Event& event) {
    auto it = std::find(events.begin(), events.end(), event);
    if (it != events.end()) {
        events.erase(it);
        return true;
    }
    return false;
}

void Calendar::clearEvents() {
    events.clear();
}

void Calendar::nextMonth() {
    if (currentViewDate.getMonth() == 12) {
        currentViewDate.setMonth(1);
        currentViewDate.setYear(currentViewDate.getYear() + 1);
    }
    else {
        currentViewDate.setMonth(currentViewDate.getMonth() + 1);
    }
}

void Calendar::previousMonth() {
    if (currentViewDate.getMonth() == 1) {
        currentViewDate.setMonth(12);
        currentViewDate.setYear(currentViewDate.getYear() - 1);
    }
    else {
        currentViewDate.setMonth(currentViewDate.getMonth() - 1);
    }
}

void Calendar::goToMonth(int month, int year) {
    if (month >= 1 && month <= 12 && year >= 1) {
        currentViewDate.setMonth(month);
        currentViewDate.setYear(year);
    }
}

void Calendar::goToToday() {
    currentViewDate = Date();
}

void Calendar::displayMonthHeader(int month, int year) const {
    static const std::string monthNames[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    std::cout << "\n";
    std::cout << std::string(10, ' ') << monthNames[month] << " " << year << std::endl;
    std::cout << "Su Mo Tu We Th Fr Sa" << std::endl;
}

void Calendar::displayMonthCalendar(int month, int year) const {
    displayMonthHeader(month, year);

    Date firstDay(1, month, year);
    int startingDay = firstDay.getDayOfWeekNumber();

    Date today;

    int daysInMonth = firstDay.getDaysInMonth(month, year);

    for (int i = 0; i < startingDay; i++) {
        std::cout << "   ";
    }

    for (int day = 1; day <= daysInMonth; day++) {
        Date currentDate(day, month, year);
        bool isToday = (currentDate == today);
        bool hasEvent = hasEvents(currentDate);
        bool isImportant = hasImportantEvents(currentDate);

        if (isToday) {
            std::cout << "\033[1;32m";
        }
        else if (isImportant) {
            std::cout << "\033[1;31m";
        }
        else if (hasEvent) {
            std::cout << "\033[1;34m";
        }

        std::cout << std::setw(2) << day;

        if (isToday || hasEvent || isImportant) {
            std::cout << "\033[0m";
        }

        std::cout << " ";

        if ((startingDay + day) % 7 == 0) {
            std::cout << std::endl;
        }
    }

    if ((startingDay + daysInMonth) % 7 != 0) {
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

bool Calendar::hasEvents(const Date& date) const {
    for (const Event& event : events) {
        if (event.getDate() == date) {
            return true;
        }
    }
    return false;
}

bool Calendar::hasImportantEvents(const Date& date) const {
    for (const Event& event : events) {
        if (event.getDate() == date &&
            (event.getPriority() == EventPriority::HIGH ||
                event.getPriority() == EventPriority::MEDIUM)) {
            return true;
        }
    }
    return false;
}

std::vector<Event> Calendar::getEventsOnDate(const Date& date) const {
    std::vector<Event> result;
    for (const Event& event : events) {
        if (event.getDate() == date) {
            result.push_back(event);
        }
    }
    return result;
}

void Calendar::displayCurrentMonth() const {
    displayMonth(currentViewDate.getMonth(), currentViewDate.getYear());
}

void Calendar::displayMonth(int month, int year) const {
    displayMonthCalendar(month, year);

    std::vector<Event> monthEvents = getEventsByMonth(month, year);
    if (!monthEvents.empty()) {
        std::cout << "Events this month:" << std::endl;
        displayEvents(monthEvents);
    }
}

void Calendar::displayYear(int year) const {
    std::cout << "\n\n" << std::string(20, '-') << " Calendar for " << year << " " << std::string(20, '-') << "\n\n";

    for (int month = 1; month <= 12; month++) {
        displayMonthCalendar(month, year);
        std::cout << std::endl;
    }
}

std::vector<Event> Calendar::getAllEvents() const {
    return events;
}

std::vector<Event> Calendar::getEventsByType(EventType type) const {
    std::vector<Event> result;
    for (const Event& event : events) {
        if (event.getType() == type) {
            result.push_back(event);
        }
    }
    return result;
}

std::vector<Event> Calendar::getEventsByPriority(EventPriority priority) const {
    std::vector<Event> result;
    for (const Event& event : events) {
        if (event.getPriority() == priority) {
            result.push_back(event);
        }
    }
    return result;
}

std::vector<Event> Calendar::getEventsByDateRange(const Date& startDate, const Date& endDate) const {
    std::vector<Event> result;
    for (const Event& event : events) {
        if (event.getDate() >= startDate && event.getDate() <= endDate) {
            result.push_back(event);
        }
    }
    return result;
}

std::vector<Event> Calendar::getEventsByMonth(int month, int year) const {
    std::vector<Event> result;
    for (const Event& event : events) {
        if (event.getDate().getMonth() == month && event.getDate().getYear() == year) {
            result.push_back(event);
        }
    }
    return result;
}

Date Calendar::calculateSemesterEndDate(const Date& startDate, int weeks) {
    return startDate + (weeks * 7);
}

void Calendar::displayEvents(const std::vector<Event>& eventList) const {
    if (eventList.empty()) {
        std::cout << "No events found." << std::endl;
        return;
    }

    for (size_t i = 0; i < eventList.size(); i++) {
        std::cout << (i + 1) << ". " << eventList[i] << std::endl;
    }
}

void Calendar::displayBirthdayInfo(const Date& birthDate) {
    std::cout << "Birthday: " << birthDate << std::endl;
    std::cout << "Day of the week: " << birthDate.getDayOfWeek() << std::endl;

    Date today;
    int age = today.getYear() - birthDate.getYear();

    if (today.getMonth() < birthDate.getMonth() ||
        (today.getMonth() == birthDate.getMonth() && today.getDay() < birthDate.getDay())) {
        age--;
    }

    std::cout << "Age: " << age << " years" << std::endl;

    Date nextBirthday(birthDate.getDay(), birthDate.getMonth(), today.getYear());
    if (nextBirthday < today) {
        nextBirthday.setYear(today.getYear() + 1);
    }

    std::cout << "Next birthday: " << nextBirthday << std::endl;
    std::cout << "Days until next birthday: " << (nextBirthday - today) << std::endl;
}