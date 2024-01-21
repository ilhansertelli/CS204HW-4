// Ilhan Sertelli

#include <iostream>
#include "schedule.h"
using namespace std;

// Default Constructor
Schedule::Schedule() {
    time_slots = 0;
    data = new string*[7];

    for (int i = 0; i < 7; i++) {
        data[i] = NULL;
    }
}

// Constructor with a given column number
Schedule::Schedule(int columns) {
    time_slots = columns;
    data = new string*[7];

    // Setting the every slot as "free"
    for (int i = 0; i < 7; i++) {
        data[i] = new string[time_slots];
        for (int j = 0; j < columns; j++) {
            data[i][j] = "free";
        }
    }
}

// Deep Copy Constructor
Schedule::Schedule(const Schedule & obj) {
    time_slots = obj.time_slots; // Equalising the column to the column of the template schedule
    string slot;
    // Allocation of a new pointer array
    data = new string*[7];

    // Allocating new row arrays and filling the slots with the rhs's slots
    for (int i = 0; i < 7; i++) {
        data[i] = new string[time_slots];
        for (int j = 0; j < time_slots; j++) {
            slot = obj.data[i][j];
            data[i][j] = slot;
        }
    }
}

// Destructor
Schedule::~Schedule() {
    // Deallocating rows one by one
    for (int i = 0; i < 7; i++) {
        if (data[i] != NULL) {
            delete[] data[i];
            data[i] = NULL;
        }
    }
    // Deallocating the main pointer array
    delete[] data;
    data = NULL;
}

// Accessor function that returns the column number
int Schedule::colNum() const {
    return time_slots;
}

// Accessor function that returns the content of the schedule
string* Schedule::getData(const int & idx1) const{
    return data[idx1];
}


ostream & operator <<(ostream & lhs, const Schedule & rhs) { // Sus
    string rowStr;


    for (int i = 0; i < 7; i++) {
        if (i == 0) {
            rowStr = "Mo: ";
        }
        else if (i == 1) {
            rowStr = "Tu: ";
        }
        else if (i == 2) {
            rowStr = "We: ";
        }
        else if (i == 3) {
            rowStr = "Th: ";
        }
        else if (i == 4) {
            rowStr = "Fr: ";
        }
        else if (i == 5) {
            rowStr = "Sa: ";
        }
        else if (i == 6) {
            rowStr = "Su: ";
        }

        lhs << rowStr;
        // Printing the content one by one
        if (rhs.getData(i) != NULL) {
            for (int j = 0; j < rhs.colNum(); j++) {
                // Add space character to the end of the slot as long as it is not the last element of the row
                if (j != rhs.colNum() - 1) {
                    lhs << rhs.getData(i)[j] << " ";
                } else {
                    lhs << rhs.getData(i)[j] << endl;
                }
            }
        }
        else {
            lhs << endl;
        }
    }

    return lhs;
}

string* Schedule::operator [](const Days & rhs) const{
    return data[rhs];
}

Schedule operator +(const Schedule & obj, const Days & rhs) {
    Schedule copy(obj); // Creating a deep copy of obj

    // Examining the right-hand side day by day
    if (rhs == Monday) {
        // Change the content
        for (int i = 0; i < copy.colNum(); i++) {
            copy.getData(0)[i] = "busy";
        }
    }
    else if (rhs == Tuesday) {
        // Change the content
        for (int i = 0; i < copy.colNum(); i++) {
            copy.getData(1)[i] = "busy";
        }
    }
    else if (rhs == Wednesday) {
        // Change the content
        for (int i = 0; i < copy.colNum(); i++) {
            copy.getData(2)[i] = "busy";
        }
    }
    else if (rhs == Thursday) {
        // Change the content
        for (int i = 0; i < copy.colNum(); i++) {
            copy.getData(3)[i] = "busy";
        }
    }
    else if (rhs == Friday) {
        // Change the content
        for (int i = 0; i < copy.colNum(); i++) {
            copy.getData(4)[i] = "busy";
        }
    }
    else if (rhs == Saturday) {
        // Change the content
        for (int i = 0; i < copy.colNum(); i++) {
            copy.getData(5)[i] = "busy";
        }
    }
    else if (rhs == Sunday) {
        // Change the content
        for (int i = 0; i < copy.colNum(); i++) {
            copy.getData(6)[i] = "busy";
        }
    }

    return copy;
}

Schedule operator +(const Schedule & obj, const int & rhs) {
    Schedule copy(obj);

    // Examining the content slot by slot
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < copy.colNum(); i++) {
            // Change the slot to "busy" if we have reached to the given index
            if (i == rhs) {
                copy.getData(j)[i] = "busy";
            }
        }
    }

    return copy;
}

Schedule operator +(const Schedule & lhs, const Schedule & rhs) {
    Schedule copy(lhs); // Created a deep copy of obj

    // Examining the schedule slot by slot
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < lhs.colNum(); j++) {
            // Check if both slot of the right-hand side and left-hand side are "free"
            if ((lhs.getData(i)[j] == "free") && (rhs.getData(i)[j] == "free")) {
                copy.getData(i)[j] = "free";
            }
            else {
                copy.getData(i)[j] = "busy";
            }
        }
    }

    return copy;
}

Schedule operator *(const Schedule & lhs, const Schedule & rhs) {
    Schedule copy(lhs);

    // Examining the schedule slot by slot
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < lhs.colNum(); j++) {
            // Check if both slot of the right-hand side and left-hand side are "busy"
            if ((lhs.getData(i)[j] == "busy") && (rhs.getData(i)[j] == "busy")) {
                copy.getData(i)[j] = "busy";
            }
            else {
                copy.getData(i)[j] = "free";
            }
        }
    }

    return copy;
}

bool Schedule::operator <(const Schedule & rhs) const{
    int countLhs = 0, countRhs = 0;

    // Examining the left-hand side schedule slot by slot
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < time_slots; j++) {
            // Increment the count of the busy slots by one if the given slot is "busy"
            if (data[i][j] == "busy") {
                countLhs++;
            }
        }
    }
    // Examining the right-hand side schedule slot by slot
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < rhs.colNum(); j++) {
            // Increment the count of the busy slots by one if the given slot is "busy"
            if (rhs.getData(i)[j] == "busy") {
                countRhs++;
            }
        }
    }
    // Checking whether the "busy" slots of lhs is less than rhs
    if (countLhs < countRhs) {
        return true;
    }
    else {
        return false;
    }
}

ostream & operator <<(ostream & lhs, const Days & rhs) {
    // Checking the given day separately and printing it
    if (rhs == Monday) {
        lhs << "Monday";
    }
    else if (rhs == Tuesday) {
        lhs << "Tuesday";
    }
    else if (rhs == Wednesday) {
        lhs << "Wednesday";
    }
    else if (rhs == Thursday) {
        lhs << "Thursday";
    }
    else if (rhs == Friday) {
        lhs << "Friday";
    }
    else if (rhs == Saturday) {
        lhs << "Saturday";
    }
    else if (rhs == Sunday) {
        lhs << "Sunday";
    }

    return lhs;
}

const Schedule & Schedule::operator =(const Schedule & rhs) {
    string slot;
    bool check = true;

    // Comparing the slots of the lhs and rhs schedules
    for (int k = 0; k < 7; k++) {
        // If there are exist at least one different slot, start deallocating and allocating process
        if (this->data[k] != rhs.getData(k)) {
            check = false;
        }
    }
    // Means that if there are different slots
    if (check == false) {
        // Deallocating the string arrays first
        for (int i = 0; i < 7; i++) {
            if (data[i] != NULL) {
                delete[] data[i];
                data[i] = NULL;
            }
        }
        // Deallocating the pointer array
        delete[] data;
        data = NULL;

        // Allocating new pointer array
        data = new string *[7];
        time_slots = rhs.colNum();

        // Equalising the new lhs schedule to the rhs schedule
        for (int i = 0; i < 7; i++) {
            // Allocating row arrays
            data[i] = new string[time_slots];
            // Setting the content one by one
            for (int j = 0; j < time_slots; j++) {
                slot = rhs.getData(i)[j];
                data[i][j] = slot;
            }
        }
    }
    return *this;
}