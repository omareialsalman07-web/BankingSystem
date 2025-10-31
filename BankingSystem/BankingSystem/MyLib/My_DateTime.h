#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace DateTime
{
    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    struct stDate
    {
        short Day, Month, Year;
    };

    struct stPeriod
    {
        stDate StartDate;
        stDate EndDate;
    };

    stDate ReadDate();
    stPeriod ReadPeriod();

    bool IsValidDate(const stDate& date);

    void SwapDates(stDate& date1, stDate& date2);

    short NumberOfDaysInMonth(short mounth, short year);
    short DayOfWeekOrder(stDate birthDay);
    short NumberOfDaysFromTheBeginingOfTheYear(stDate Date);

    bool IsLeapYear(short year);
    bool IsLastDayInMonth(stDate date);
    bool IsLastMonthInYear(stDate date);

    std::string MounthShortName(short mounth);
    std::string DayShortName(short DayOfWeekOrder);

    stDate GetDateFromDayOrderInYear(short dayOrderInYear, short year);
    stDate MaxDate(const stDate& Date1, const stDate& Date2);

    bool IsDatesAreEquals(stDate date1, stDate date2);
    bool IsDate1_After_Date2(stDate date1, stDate date2);
    bool IsDate1_Before_Date2(stDate date1, stDate date2);

    enDateCompare GetComparingDatesResult(stDate date1, stDate date2);
    stDate MinDate(const stDate& date1, const stDate& date2);

    void AddDaysToDate(stDate& date, int amountToAdd = 1);
    void DecreaseDaysFromDate(stDate& date, int amountToDecrease);

    short IsEndOfWeek(stDate Date);
    bool IsWeekEnd(stDate Date);
    bool IsBusinessDay(stDate Date);

    short DaysUntilTheEndOfWeek(stDate Date);
    int GetDifferenceInDays(stDate date1, stDate date2, bool IncludeLastDay = false);
    int GetPeriodLength(stPeriod Perdiod, bool IncludeLastDay = false);
    short DaysUntilTheEndOfMonth(stDate Date1);
    short DaysUntilTheEndOfYear(stDate Date1);
    int GetVacationDays(stDate vacationStartDate, stDate vacationEndDate);

    stDate GetVacationEndDate(stDate vacationStardDate, int vacationDays);

    bool IsPerdiodsOverlaps(const stPeriod& Period1, const stPeriod& Period2);
    bool IsDateWithInPeriod(const stPeriod& period, const stDate& date);
    int GetPeriodsOverlapingDays(stPeriod Period1, stPeriod Period2);

    std::string DateToString(const stDate& date);
    stDate StringToDate(const std::string& DateLine);

    void PrintDate(const stDate& Date, std::string format = "dd/mm/yyyy");
    void PrintMounthCalender(short mounth, short year);
    void PrintYearCalender(short year);
}