#include <sstream>
#include <iomanip>
#include "Timestamp.h"

using namespace std;

/**
 * Construct a new Timestamp object
 * @param timestamp A string representing a timestamp
 */
Timestamp::Timestamp(const string &timestamp)
{
    parseTimestamp(timestamp);
}

void Timestamp::parseTimestamp(const string &timestamp)
{
    istringstream ss(timestamp);
    ss >> get_time(&timeStruct, "%Y/%m/%d %H:%M:%S");
}

string Timestamp::formatTimestamp() const
{
    ostringstream ss;
    ss << put_time(&timeStruct, "%Y/%m/%d %H:%M:%S");

    return ss.str();
}

string Timestamp::getMinTimestamp() const
{
    tm minTime = timeStruct;
    minTime.tm_hour = 0;
    minTime.tm_min = 0;
    minTime.tm_sec = 0;
    ostringstream ss;
    ss << put_time(&minTime, "%Y/%m/%d %H:%M:%S");

    return ss.str();
}

string Timestamp::getMaxTimestamp() const
{
    tm maxTime = timeStruct;
    maxTime.tm_hour = 23;
    maxTime.tm_min = 59;
    maxTime.tm_sec = 59;
    ostringstream ss;
    ss << put_time(&maxTime, "%Y/%m/%d %H:%M:%S");

    return ss.str();
}
