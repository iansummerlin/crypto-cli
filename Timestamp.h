#pragma once

#include <string>
#include <chrono>

using namespace std;

class Timestamp
{
private:
    tm timeStruct; // Renamed member variable

public:
    /**
     * Construct a new Timestamp object
     * @param timestamp A string representing a timestamp
     */
    explicit Timestamp(const string &timestamp);

    // Member function to parse a timestamp string into tm
    void parseTimestamp(const string &timestamp);

    // Member function to format tm as a string
    string formatTimestamp() const;

    // Functions to get min and max timestamp in a 24hr period
    string getMinTimestamp() const;
    string getMaxTimestamp() const;
};
