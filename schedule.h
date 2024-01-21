#include <iostream>
#include <string>
using namespace std;

#ifndef TAKEHOME4_SCHEDULE_H
#define TAKEHOME4_SCHEDULE_H

enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule {
public:
    Schedule();
    Schedule(int columns);
    Schedule(const Schedule & obj);
    ~Schedule();
    int colNum() const;
    string* getData(const int & idx1) const;

    const Schedule & operator =(const Schedule &  rhs) ;
    string* operator [](const Days & rhs) const;
    bool operator <(const Schedule & rhs) const;

    
private:
    int time_slots;
    string** data;
};

ostream & operator <<(ostream & lhs, const Schedule & rhs);
ostream & operator <<(ostream & lhs, const Days & rhs);
Schedule operator +(const Schedule & obj, const Days & rhs);
Schedule operator +(const Schedule & obj, const int & rhs);
Schedule operator +(const Schedule & lhs, const Schedule & rhs);
Schedule operator *(const Schedule & lhs, const Schedule & rhs);

#endif //TAKEHOME4_SCHEDULE_H
