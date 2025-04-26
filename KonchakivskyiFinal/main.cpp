#include "datetime.h"
#include "calendar.h"
#include "screen.h"
#include "dictionary.h"
#include "deque.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


void testDateTimeClass() {
	std::cout << "\n=============== 1: Date and Time Classes ===============\n";

	std::cout << "\n--------------- Date ---------------\n";

	Date today;
	std::cout << "Today's date: " << today << std::endl;

	Date specificDate(3, 7, 2023);
	std::cout << "Specific date: " << specificDate << std::endl;

	Date invalidDate(31, 2, 2023);
	std::cout << "Creating invalid date: " << invalidDate << std::endl;

	specificDate.setDay(20);
	specificDate.setMonth(10);
	specificDate.setYear(2024);
	std::cout << "After setters: " << specificDate << std::endl;

	std::cout << "Day: " << specificDate.getDay()
		<< ", Month: " << specificDate.getMonth()
		<< ", Year: " << specificDate.getYear() << std::endl;

	Date tomorrow = today;
	++tomorrow;
	std::cout << "Tomorrow: " << tomorrow << std::endl;

	Date yesterday = today;
	--yesterday;
	std::cout << "Yesterday: " << yesterday << std::endl;

	Date nextWeek = today + 7;
	std::cout << "Next week: " << nextWeek << std::endl;

	Date lastWeek = today - 7;
	std::cout << "Last week: " << lastWeek << std::endl;

	int daysDiff = nextWeek - today;
	std::cout << "Days difference: " << daysDiff << std::endl;

	std::cout << "today == today: " << (today == today) << std::endl;
	std::cout << "today != tomorrow: " << (today != tomorrow) << std::endl;
	std::cout << "today < tomorrow: " << (today < tomorrow) << std::endl;
	std::cout << "today > tomorrow: " << (today > tomorrow) << std::endl;

	std::cout << "\n--------------- Time ---------------\n";

	Time now;
	std::cout << "Current time: " << now << std::endl;

	Time specificTime(15, 0, 0);
	std::cout << "Specific time: " << specificTime << std::endl;

	Time invalidTime(25, 70, 90);
	std::cout << "Creating invalid time: " << invalidTime << std::endl;

	specificTime.setHour(18);
	specificTime.setMinute(45);
	specificTime.setSecond(30);
	std::cout << "After setters: " << specificTime << std::endl;

	std::cout << "Hour: " << specificTime.getHour()
		<< ", Minute: " << specificTime.getMinute()
		<< ", Second: " << specificTime.getSecond() << std::endl;

	Time oneSecondLater = now;
	++oneSecondLater;
	std::cout << "One second later: " << oneSecondLater << std::endl;

	Time oneSecondEarlier = now;
	--oneSecondEarlier;
	std::cout << "One second earlier: " << oneSecondEarlier << std::endl;

	Time oneHourLater = now + 3600;
	std::cout << "One hour later: " << oneHourLater << std::endl;

	Time oneHourEarlier = now - 3600;
	std::cout << "One hour earlier: " << oneHourEarlier << std::endl;

	int secondsDiff = oneHourLater - now;
	std::cout << "Seconds difference: " << secondsDiff << std::endl;

	std::cout << "now == now: " << (now == now) << std::endl;
	std::cout << "now != oneSecondLater: " << (now != oneSecondLater) << std::endl;
	std::cout << "now < oneSecondLater: " << (now < oneSecondLater) << std::endl;
	std::cout << "now > oneSecondLater: " << (now > oneSecondLater) << std::endl;
}

void testEventClass() {
	std::cout << "\n=============== 2: Event Class ===============\n";

	Date birthday(3, 7, 2025);
	Date today;
	Time now;

	Event allDayEvent(birthday, "Birthday", EventType::BIRTHDAY, EventPriority::MEDIUM, "My Birthday");
	std::cout << "All day event: " << allDayEvent << std::endl;

	Event timedEvent(today, now, "Important meeting", EventType::MEETING, EventPriority::HIGH, "Scheduled meeting");
	std::cout << "Timed event: " << timedEvent << std::endl;

	std::cout << "\nMeeting details:\n";
	std::cout << "Date: " << timedEvent.getDate() << std::endl;
	std::cout << "Time: " << timedEvent.getTime() << std::endl;
	std::cout << "Has time: " << timedEvent.getHasTime() << std::endl;
	std::cout << "Title: " << timedEvent.getTitle() << std::endl;
	std::cout << "Type: " << Event::eventTypeToString(timedEvent.getType()) << std::endl;
	std::cout << "Priority: " << Event::eventPriorityToString(timedEvent.getPriority()) << std::endl;
	std::cout << "Description: " << timedEvent.getDescription() << std::endl;

	timedEvent.setTitle("Updated Meeting");
	timedEvent.setPriority(EventPriority::HIGH);
	timedEvent.setDescription("Updated description");
	std::cout << "\nAfter: " << timedEvent << std::endl;

	std::cout << "\nComparison:\n";
	Event laterEvent(today + 1, "Tomorrow's Event");
	std::cout << "tomorrow's event < today's event: " << (laterEvent < timedEvent) << std::endl;
	std::cout << "tomorrow's event > today's event: " << (laterEvent > timedEvent) << std::endl;

	Event sameTimeEvent(today, now, "Same Time Event");
	std::cout << "timedEvent == sameTimeEvent: " << (timedEvent == sameTimeEvent) << std::endl;
	std::cout << "timedEvent != sameTimeEvent: " << (timedEvent != sameTimeEvent) << std::endl;
}

void testCalendarClass() {
    std::cout << "\n=============== 3: Calendar Class ===============\n";

    Calendar calendar;

    std::cout << "\nCurrent month:\n";
    calendar.displayCurrentMonth();

    Date today;
    Time now;

    Event meeting(today, now, "Team Meeting", EventType::MEETING, EventPriority::HIGH);
    Event birthdayParty(today + 5, "Birthday Party", EventType::BIRTHDAY, EventPriority::MEDIUM);
    Event doctor(today + 10, Time(14, 30, 0), "Doctor", EventType::MEETING, EventPriority::HIGH);
    Event christmas(Date(25, 12, today.getYear()), "Christmas", EventType::HOLIDAY, EventPriority::MEDIUM);
	Event birthday(Date(3, 7, today.getYear()), "My birthday", EventType::BIRTHDAY, EventPriority::MEDIUM);
	Event newYear(Date(1, 1, today.getYear()+1), "New Year", EventType::BIRTHDAY, EventPriority::MEDIUM);

    calendar.addEvent(meeting);
    calendar.addEvent(birthdayParty);
    calendar.addEvent(doctor);
    calendar.addEvent(christmas);
	calendar.addEvent(birthday);
	calendar.addEvent(newYear);

    std::cout << "\nCalendar after adding events:\n";
    calendar.displayCurrentMonth();

    std::cout << "\nAll events:\n";
    calendar.displayEvents(calendar.getAllEvents());

    std::cout << "\nHigh priority events:\n";
    calendar.displayEvents(calendar.getEventsByPriority(EventPriority::HIGH));

    std::cout << "\nEvents this month:\n";
    calendar.displayEvents(calendar.getEventsByMonth(today.getMonth(), today.getYear()));

    std::cout << "\nEvents in the next 7 days:\n";
    calendar.displayEvents(calendar.getEventsByDateRange(today, today + 7));

    std::cout << "\nNext month:\n";
    calendar.nextMonth();
    calendar.displayCurrentMonth();

    std::cout << "\nPrevious month:\n";
    calendar.previousMonth();
    calendar.previousMonth();
    calendar.displayCurrentMonth();

    std::cout << "\nSpecific month:\n";
    calendar.goToMonth(12, today.getYear());
    calendar.displayCurrentMonth();

    std::cout << "\nToday:\n";
    calendar.goToToday();
    calendar.displayCurrentMonth();
}

void testSemesterCalculation() {
    std::cout << "\n=============== 4: Semester End Date Calculation ===============\n";

    Date semesterStart(10, 2, 2025);
    int semesterWeeks = 12;

    Date semesterEnd = Calendar::calculateSemesterEndDate(semesterStart, semesterWeeks);

    std::cout << "Semester start date: " << semesterStart << std::endl;
    std::cout << "Semester duration: " << semesterWeeks << " weeks" << std::endl;
    std::cout << "Semester end date: " << semesterEnd << std::endl;
    std::cout << "Total days: " << (semesterEnd - semesterStart) << std::endl;
}

void displayBirthdayInfo() {
    std::cout << "\n=============== 5: Birthdays info ===============\n";

    Date myBirthday(3, 7, 2006);
    std::cout << "\nMy Birthday:\n";
    Calendar::displayBirthdayInfo(myBirthday);

    Date einsteinBirthday(14, 3, 1879);
    std::cout << "\nAlbert Einstein's:\n";
    Calendar::displayBirthdayInfo(einsteinBirthday);

    Date turingBirthday(23, 6, 1912);
    std::cout << "\nAlan Turing's:\n";
    Calendar::displayBirthdayInfo(turingBirthday);

    Date cristianoRonaldoBirthday(5, 2, 1985);
    std::cout << "\nCristiano Ronaldo's:\n";
    Calendar::displayBirthdayInfo(cristianoRonaldoBirthday);

	Date steveJobsBirthday(24, 2, 1955);
	std::cout << "\nSteve Jobs':\n";
	Calendar::displayBirthdayInfo(steveJobsBirthday);
}

void testScreenClass() {
    std::cout << "\n=============== 6-7: Screen Class ===============\n" << std::endl;


    try {
        Screen screen("lorem.txt");
        screen.display();

        std::cout << "Scrolling forward" << std::endl;
        screen.scrollForward();
        screen.display();

        std::cout << "Scrolling backward" << std::endl;
        screen.scrollBackward();
        screen.display();

        std::cout << "Modifying line" << std::endl;
        screen.modifyLine("This is a modified paragraph.");
        screen.display();

        std::cout << "Inserting line" << std::endl;
        screen.insertLine("This is a new paragraph.");
        screen.display();

        std::cout << "Deleting line" << std::endl;
        screen.deleteLine();
        screen.display();

        Screen screenCopy(screen);
        screenCopy.display();

        Screen screenMove(std::move(screenCopy));
        screenMove.display();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void testDictionaryClass() {
    std::cout << "\n=============== 8: Dictionary Class ===============\n" << std::endl;

    try {
        Dictionary dict("lorem.txt");

        dict.display(false);

        dict.display(true);

        dict.setWordStatus("lorem", WordStatus::New);
        dict.setWordStatus("ipsum", WordStatus::Learning);
        dict.setWordStatus("dolor", WordStatus::Learned);
        dict.setWordStatus("sit", WordStatus::Ignored);

        std::cout << "Dictionary after setting statuses:" << std::endl;
        dict.display(false);

        Dictionary dict2("lorem_2.txt");
        dict2.setWordStatus("lorem", WordStatus::Learned);
        dict2.setWordStatus("amet", WordStatus::New);

        std::cout << "Second dictionary:" << std::endl;
        dict2.display(false);

        Dictionary unionDict = dict + dict2;
        std::cout << "Union of dictionaries:" << std::endl;
        unionDict.display(false);

        Dictionary intersectionDict = dict.intersection(dict2);
        std::cout << "Intersection of dictionaries:" << std::endl;
        intersectionDict.display(false);

        std::vector<std::string> newWords = unionDict.getWordsByStatus(WordStatus::New);
        std::cout << "New words:" << std::endl;
        for (const auto& word : newWords) {
            std::cout << " - " << word << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void testDequeNVI() {
    std::cout << "\n=============== 9: Deque with NVI ===============\n" << std::endl;

    ArrayDeque<int> arrayDeque;
    std::cout << "--------------- ArrayDeque ---------------" << std::endl;

    std::cout << "Pushing elements" << std::endl;
    arrayDeque.pushBack(1);
    arrayDeque.pushBack(2);
    arrayDeque.pushBack(3);
    arrayDeque.pushFront(4);
    arrayDeque.pushFront(5);

    std::cout << "Deque size: " << arrayDeque.size() << std::endl;
    std::cout << "Front element: " << arrayDeque.front() << std::endl;
    std::cout << "Back element: " << arrayDeque.back() << std::endl;

    std::cout << "Popping front: " << arrayDeque.popFront() << std::endl;
    std::cout << "Popping back: " << arrayDeque.popBack() << std::endl;
    std::cout << "Deque size after pops: " << arrayDeque.size() << std::endl;

    ListDeque<int> listDeque;
    std::cout << "\n--------------- ListDeque ---------------" << std::endl;

    std::cout << "Pushing elements" << std::endl;
    listDeque.pushBack(10);
    listDeque.pushBack(20);
    listDeque.pushBack(30);
    listDeque.pushFront(40);
    listDeque.pushFront(50);

    std::cout << "Deque size: " << listDeque.size() << std::endl;
    std::cout << "Front element: " << listDeque.front() << std::endl;
    std::cout << "Back element: " << listDeque.back() << std::endl;

    std::cout << "Popping front: " << listDeque.popFront() << std::endl;
    std::cout << "Popping back: " << listDeque.popBack() << std::endl;
    std::cout << "Deque size after pops: " << listDeque.size() << std::endl;
}

void testDequeComposition() {
    std::cout << "\n=============== 10: Deque with Composition ===============\n" << std::endl;

    ArrayDequeComposition<int> arrayDeque;
    std::cout << "--------------- ArrayDequeComposition ---------------" << std::endl;

    std::cout << "Pushing elements" << std::endl;
    arrayDeque.pushBack(1);
    arrayDeque.pushBack(2);
    arrayDeque.pushBack(3);
    arrayDeque.pushFront(4);
    arrayDeque.pushFront(5);

    std::cout << "Deque size: " << arrayDeque.size() << std::endl;
    std::cout << "Front element: " << arrayDeque.front() << std::endl;
    std::cout << "Back element: " << arrayDeque.back() << std::endl;

    std::cout << "Popping front: " << arrayDeque.popFront() << std::endl;
    std::cout << "Popping back: " << arrayDeque.popBack() << std::endl;
    std::cout << "Deque size after pops: " << arrayDeque.size() << std::endl;

    ListDequeComposition<int> listDeque;
    std::cout << "\n--------------- ListDequeComposition ---------------" << std::endl;

    std::cout << "Pushing elements" << std::endl;
    listDeque.pushBack(10);
    listDeque.pushBack(20);
    listDeque.pushBack(30);
    listDeque.pushFront(40);
    listDeque.pushFront(50);

    std::cout << "Deque size: " << listDeque.size() << std::endl;
    std::cout << "Front element: " << listDeque.front() << std::endl;
    std::cout << "Back element: " << listDeque.back() << std::endl;

    std::cout << "Popping front: " << listDeque.popFront() << std::endl;
    std::cout << "Popping back: " << listDeque.popBack() << std::endl;
    std::cout << "Deque size after pops: " << listDeque.size() << std::endl;

    std::cout << "\n=============== Conclusion ===============" << std::endl;
    std::cout << "Composition is generally preferred over inheritance when the relationship" << std::endl;
    std::cout << "is 'has-a' rather than 'is-a'. In this case, a Deque with an array implementation" << std::endl;
    std::cout << "has an array, rather than is an array. The composition approach provides better" << std::endl;
    std::cout << "flexibility and encapsulation while avoiding many of the pitfalls of inheritance." << std::endl;
}

int main() {
	testDateTimeClass();
	testEventClass();
	testCalendarClass();
	testSemesterCalculation();
	displayBirthdayInfo();
    testScreenClass();
    testDictionaryClass();
    testDequeNVI();
    testDequeComposition();
	return 0;
}