#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>

struct Friend {
    std::string name = "";
    std::tm date{ 0 };
};


int getTimeToHb(std::vector<Friend>::iterator it) {
    std::time_t t = std::time(nullptr);
    std::tm now{ 0 };
   // localtime_s(&now, &t);
    int lastYear = it->date.tm_year;
    it->date.tm_year = now.tm_year;
    std::time_t time_hb = std::mktime(&it->date);
    it->date.tm_year = lastYear;

    double diff = std::difftime(t, time_hb);
    return (int)diff;
}

bool isBirthdayNow(std::tm& date) {
    std::time_t t = std::time(nullptr);
    std::tm now{ 0 };
    localtime_s(&now, &t);

    return (now.tm_mon == date.tm_mon && now.tm_mday == date.tm_mday);
}

int main()
{
    std::vector<Friend> hb; // Name, date
    std::string bufName;

    while (true) {
        std::cout << "Enter name and date: ";
        std::cin >> bufName;
        if (bufName == "end") {
            break;
        }
        Friend fr;
        std::time_t t = std::time(nullptr);
        std::tm date{ 0 };
        localtime_s(&date, &t);
        std::cin >> std::get_time(&date, "%Y/%m/%d");;

        fr.name = bufName;
        fr.date = date;

        hb.push_back(fr);
        std::cout << "Added " << fr.name << std::endl;
    }
    if (hb.empty()) {
        std::cout << "No friends" << std::endl;
        return 0;
    }
    std::vector<Friend>::iterator closest = hb.begin();
    int diff = getTimeToHb(closest);

    for (auto it = hb.begin(); it != hb.end(); ++it) {
        int lDiff = getTimeToHb(it);
        if (lDiff > diff && lDiff <= 0) {
            diff = lDiff;
            closest = it;
        }
        if (isBirthdayNow(it->date)) {
            std::cout << "Happy birthday " << it->name << "!!!!! Today!!!" << std::endl;
        }
    }

    std::cout << "Closest birthday: " << closest->name << " [" << std::put_time(&closest->date, "%Y/%m/%d") << "]" << std::endl;
}