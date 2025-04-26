#ifndef CALENDAR_H
#define CALENDAR_H

#include "datetime.h"
#include <vector>
#include <string>
#include <map>

enum class EventType {
    MEETING,
    BIRTHDAY,
    HOLIDAY,
    OTHER
};

enum class EventPriority {
    LOW,
    MEDIUM,
    HIGH
};

class Event {
private:
    Date date;
    Time time;
    bool hasTime;
    EventType type;
    EventPriority priority;
    std::string title;
    std::string description;

public:
    Event(const Date& date, const std::string& title,
        EventType type = EventType::OTHER,
        EventPriority priority = EventPriority::MEDIUM,
        const std::string& description = "");

    Event(const Date& date, const Time& time, const std::string& title,
        EventType type = EventType::OTHER,
        EventPriority priority = EventPriority::MEDIUM,
        const std::string& description = "");

    Date getDate() const { return date; }
    Time getTime() const { return time; }
    bool getHasTime() const { return hasTime; }
    EventType getType() const { return type; }
    EventPriority getPriority() const { return priority; }
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }

    void setDate(const Date& date) { this->date = date; }
    void setTime(const Time& time) { this->time = time; this->hasTime = true; }
    void setType(EventType type) { this->type = type; }
    void setPriority(EventPriority priority) { this->priority = priority; }
    void setTitle(const std::string& title) { this->title = title; }
    void setDescription(const std::string& description) { this->description = description; }
    void removeTime() { hasTime = false; }

    bool operator<(const Event& other) const;
    bool operator>(const Event& other) const;
    bool operator==(const Event& other) const;
    bool operator!=(const Event& other) const;

    void display() const;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Event& event);

    static std::string eventTypeToString(EventType type);
    static std::string eventPriorityToString(EventPriority priority);
};

class Calendar {
private:
    std::vector<Event> events;
    Date currentViewDate;

    void displayMonthHeader(int month, int year) const;
    void displayMonthCalendar(int month, int year) const;
    bool hasEvents(const Date& date) const;
    bool hasImportantEvents(const Date& date) const;
    std::vector<Event> getEventsOnDate(const Date& date) const;

public:
    Calendar();
    Calendar(const Date& initialViewDate);

    void addEvent(const Event& event);
    bool removeEvent(const Event& event);
    void clearEvents();

    void nextMonth();
    void previousMonth();
    void goToMonth(int month, int year);
    void goToToday();

    void displayCurrentMonth() const;
    void displayMonth(int month, int year) const;
    void displayYear(int year) const;

    std::vector<Event> getAllEvents() const;
    std::vector<Event> getEventsByType(EventType type) const;
    std::vector<Event> getEventsByPriority(EventPriority priority) const;
    std::vector<Event> getEventsByDateRange(const Date& startDate, const Date& endDate) const;
    std::vector<Event> getEventsByMonth(int month, int year) const;

    static Date calculateSemesterEndDate(const Date& startDate, int weeks);

    void displayEvents(const std::vector<Event>& eventList) const;

    static void displayBirthdayInfo(const Date& birthDate);
};

#endif // CALENDAR_H