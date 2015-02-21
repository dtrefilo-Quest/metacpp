/****************************************************************************
* Copyright 2014-2015 Trefilov Dmitrij                                      *
*                                                                           *
* Licensed under the Apache License, Version 2.0 (the "License");           *
* you may not use this file except in compliance with the License.          *
* You may obtain a copy of the License at                                   *
*                                                                           *
*    http://www.apache.org/licenses/LICENSE-2.0                             *
*                                                                           *
* Unless required by applicable law or agreed to in writing, software       *
* distributed under the License is distributed on an "AS IS" BASIS,         *
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
* See the License for the specific language governing permissions and       *
* limitations under the License.                                            *
****************************************************************************/
#ifndef METACPP_DATETIME_H
#define METACPP_DATETIME_H
#include <time.h>
#include "String.h"
#include "SharedDataPointer.h"

namespace metacpp {

/** \brief Enumeration represents gregorian calendar months */
enum EMonth
{
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    Novermber,
    December
};

/** \brief Enumeration represents day of week */
enum EDayOfWeek
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Sataday
};

namespace detail
{

    class DateTimeData : public SharedDataBase
    {
    public:
        explicit DateTimeData(time_t stdTime = 0);
        explicit DateTimeData(const struct tm& tm);
        ~DateTimeData();

        bool operator==(const DateTimeData& rhs) const;
        bool operator!=(const DateTimeData& rhs) const;

        int year() const;
        EMonth month() const;
        int day() const;
        EDayOfWeek dayOfWeek() const;

        int hours() const;
        int minutes() const;
        int seconds() const;

        time_t toStdTime() const;
        struct tm toTm() const;
        String toString() const;
        String toString(const char *format) const;

        SharedDataBase *clone() const override;

        void fromString(const char *isoString);
        void fromString(const char *str, const char *format);

    private:
        struct tm m_tm;
    };

} // namespace detail

/** \brief A class representing date and time in Gregorian calendar and providing methods of manipulation */
class DateTime : protected SharedDataPointer<detail::DateTimeData>
{
public:
    /** \brief Constructs new instance of DateTime from given Unix time
     * (number of seconds since 1970-01-01)
    */
    explicit DateTime(time_t stdTime);
    /** \brief Constructs invalid instance of DateTime */
    DateTime();
    ~DateTime();

    /** \brief Checks whether this is a valid DateTime */
    bool valid() const;

    /** \brief Checks DateTimes for equality */
    bool operator==(const DateTime& rhs) const;
    /** \brief Checks DateTimes for inequality */
    bool operator!=(const DateTime& rhs) const;

    /** \brief Gets a year part */
    int year() const;
    /** \brief Gets a month part */
    EMonth month() const;
    /** \brief Gets a day of the month part */
    int day() const;
    /** \brief Gets a day of the week part */
    EDayOfWeek dayOfWeek() const;
    /** \brief Gets an hour part (from 0 to 23) */
    int hours() const;
    /** \brief Gets an minute part (from 0 to 59) */
    int minutes() const;
    /** \brief Gets an second part (from 0 to 59) */
    int seconds() const;

    /** \brief Adds given number of years to the value stored in this instance of DateTime and returns a reference to it */
    DateTime& addYears(int years);
    /** \brief Adds given number of months to the value stored in this instance of DateTime and returns a reference to it */
    DateTime& addMonths(int months);
    /** \brief Adds given number of days to the value stored in this instance of DateTime and returns a reference to it */
    DateTime& addDays(int days);
    /** \brief Adds given number of hours to the value stored in this instance of DateTime and returns a reference to it */
    DateTime& addHours(int hours);
    /** \brief Adds given number of minutes to the value stored in this instance of DateTime and returns a reference to it */
    DateTime& addMinutes(int minutes);
    /** \brief Adds given number of seconds to the value stored in this instance of DateTime and returns a reference to it */
    DateTime& addSeconds(int seconds);

    /** \brief Converts stored date and time value to the Unix time */
    time_t toStdTime() const;
    /** \brief Converts stored date and time to string into ISO format */
    String toString() const;
    /** \brief Converts stored date and time to string in specified format
     *
     * \arg format As specified in strptime(3)
    */
    String toString(const char *format) const;

    /** \brief Returns a new instance of DateTime from the given string in ISO format */
    static DateTime fromString(const char *isoString);
    /** \brief Returns a new instance of DateTime from the given string in specified format
     *
     * \arg format As specified in strftime(3)
    */
    static DateTime fromString(const char *string, const char *format);
    /** \brief Returns a new instance of DateTime from local date and type set in the system */
    static DateTime now();
private:
    detail::DateTimeData *getData() const;
};

/** \brief Serializes DateTime into stream using ISO format
 * \relates metacpp::DateTime
*/
std::ostream& operator<<(std::ostream& stream, const DateTime& dt);

} // namespace metacpp

#endif // METACPP_DATETIME_H
