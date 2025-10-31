#include "My_DateTime.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "My_String.h"

using namespace DateTime;

stDate DateTime::ReadDate()
{
    stDate Date;

    std::cout << "Enter Day : ";
    std::cin >> Date.Day;

    std::cout << "Enter Mouth : ";
    std::cin >> Date.Month;

    std::cout << "Enter Year : ";
    std::cin >> Date.Year;

    return Date;
}

stPeriod DateTime::ReadPeriod()
{
    stPeriod Period;

    std::cout << "\nStart Date : \n";
    Period.StartDate = ReadDate();
    std::cout << "\nEnd Date : \n";
    Period.EndDate = ReadDate();

    return Period;
}

bool DateTime::IsValidDate(const stDate& date)
{
    return !((date.Month < 1 || date.Month > 12) || (date.Day < 1 || date.Day > NumberOfDaysInMonth(date.Month, date.Year))
        || date.Year < 1);
}

void DateTime::SwapDates(stDate& date1, stDate& date2)
{
    stDate tempDate = date1;

    date1 = date2;
    date2 = tempDate;
}

bool DateTime::IsLeapYear(short year)
{
    return ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0));
}

short DateTime::NumberOfDaysInMonth(short mounth, short year)
{
    if (mounth < 1 || mounth > 12)
        return 0;

    int DaysInMounth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (mounth == 2) ? (IsLeapYear(year) ? 29 : 28) : DaysInMounth[mounth - 1];
}

short DateTime::DayOfWeekOrder(stDate birthDay)
{
    int a = (14 - birthDay.Month) / 12;
    int y = birthDay.Year - a;
    int m = birthDay.Month + (12 * a) - 2;

    return (birthDay.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short DateTime::NumberOfDaysFromTheBeginingOfTheYear(stDate Date)
{
    short TotalDays = 0;
    for (int i = 1; i <= Date.Month - 1; i++)
    {
        TotalDays += NumberOfDaysInMonth(i, Date.Year);
    }
    TotalDays += Date.Day;
    return TotalDays;
}

bool DateTime::IsLastDayInMonth(stDate date)
{
    return (date.Day == NumberOfDaysInMonth(date.Month, date.Year));
}

bool DateTime::IsLastMonthInYear(stDate date)
{
    return (date.Month == 12);
}

std::string DateTime::MounthShortName(short mounth)
{
    std::string arr[] = { "", "Jan", "Feb", "Mar", "Eap", "May", "Jon", "Jul", "Ogs", "Sep", "Oct", "Nov", "Dec" };
    return arr[mounth];
}

std::string DateTime::DayShortName(short DayOfWeekOrder)
{
    std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    return arrDayNames[DayOfWeekOrder];
}

stDate DateTime::GetDateFromDayOrderInYear(short dayOrderInYear, short year)
{
    stDate Date;

    Date.Year = year;

    short monthCounter = 1;
    while (dayOrderInYear >= NumberOfDaysInMonth(monthCounter, year))
    {
        dayOrderInYear -= NumberOfDaysInMonth(monthCounter, year);

        if (monthCounter >= 12)
        {
            Date.Year++;
            monthCounter = 0;
        }
        monthCounter++;
    }

    Date.Month = monthCounter;
    Date.Day = dayOrderInYear;

    return Date;
}

stDate DateTime::MaxDate(const stDate& Date1, const stDate& Date2)
{
    if (Date1.Year > Date2.Year)
        return Date1;
    else if (Date1.Year < Date2.Year)
        return Date2;

    if (Date1.Month > Date2.Month)
        return Date1;
    else if (Date1.Month < Date2.Month)
        return Date2;

    if (Date1.Day > Date2.Day)
        return Date1;
    else if (Date1.Day < Date2.Day)
        return Date2;

    // Dates are equal
    return Date1;
}

bool DateTime::IsDatesAreEquals(stDate date1, stDate date2)
{
    return (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day == date2.Day);
}

bool DateTime::IsDate1_After_Date2(stDate date1, stDate date2)
{
    if (IsDatesAreEquals(date1, date2))
        return false;

    stDate maxDate = MaxDate(date1, date2);

    return IsDatesAreEquals(date1, maxDate);
}

bool DateTime::IsDate1_Before_Date2(stDate date1, stDate date2)
{

    return (!IsDate1_After_Date2(date1, date2) && !IsDatesAreEquals(date1, date2));
}

enDateCompare DateTime::GetComparingDatesResult(stDate date1, stDate date2)
{
    if (IsDatesAreEquals(date1, date2))
        return Equal;

    if (IsDate1_After_Date2(date1, date2))
        return After;

    return Before; // date1 before date2
}

stDate DateTime::MinDate(const stDate& date1, const stDate& date2)
{
    return IsDate1_After_Date2(date1, date2) ? date2 : date1;
}

void DateTime::AddDaysToDate(stDate& date, int amountToAdd)
{
    if (amountToAdd <= 0)
        return;

    if (IsLastDayInMonth(date))
    {
        if (IsLastMonthInYear(date))
        {
            date.Year++;
            date.Month = 1;
            date.Day = 1;
        }
        else
        {
            date.Month++;
            date.Day = 1;
        }
        amountToAdd--;
    }
    else
    {
        int daysInMonth = NumberOfDaysInMonth(date.Month, date.Year);

        int remainingDaysInMonth = daysInMonth - date.Day;

        if (amountToAdd > remainingDaysInMonth)
        {
            // Move to end of month, then continue recursively
            date.Day = daysInMonth;
            amountToAdd -= remainingDaysInMonth;
        }
        else
        {
            date.Day += amountToAdd;
            amountToAdd = 0;
        }
    }

    if (amountToAdd > 0)
        AddDaysToDate(date, amountToAdd);
}

void DateTime::DecreaseDaysFromDate(stDate& date, int amountToDecrease)
{
    if (amountToDecrease <= 0)
        return;

    if (date.Day == 1)
    {
        if (date.Month == 1)
        {
            date.Year--;
            date.Month = 12;
            date.Day = 31;
        }
        else
        {
            date.Month--;
            date.Day = NumberOfDaysInMonth(date.Month, date.Year);
        }
        amountToDecrease--;
    }
    else
    {
        if (amountToDecrease >= date.Day)
        {
            // Move to first day of current month, then continue
            amountToDecrease -= (date.Day - 1);
            date.Day = 1;
        }
        else
        {
            date.Day -= amountToDecrease;
            amountToDecrease = 0;
        }
    }

    if (amountToDecrease > 0)
        DecreaseDaysFromDate(date, amountToDecrease);
}

short DateTime::IsEndOfWeek(stDate Date)
{
    return DayOfWeekOrder(Date) == 6;
}

bool DateTime::IsWeekEnd(stDate Date)
{
    //Weekends are Fri and Sat
    short DayIndex = DayOfWeekOrder(Date);
    return  (DayIndex == 5 || DayIndex == 6);
}

bool DateTime::IsBusinessDay(stDate Date)
{
    return !IsWeekEnd(Date);
}

short DateTime::DaysUntilTheEndOfWeek(stDate Date)
{
    return 6 - DayOfWeekOrder(Date);
}

int DateTime::GetDifferenceInDays(stDate date1, stDate date2, bool IncludeLastDay)
{
    int Days = 0;

    if (IsDate1_After_Date2(date1, date2)) // to make sure that date1 befor date 2
        SwapDates(date1, date2);


    while (!IsDatesAreEquals(date1, date2))
    {
        AddDaysToDate(date1, 1);
        Days++;
    }
    return (IncludeLastDay) ? ++Days : Days;
}

int DateTime::GetPeriodLength(stPeriod Perdiod, bool IncludeLastDay)
{
    return GetDifferenceInDays(Perdiod.StartDate, Perdiod.EndDate, IncludeLastDay);
}

short DateTime::DaysUntilTheEndOfMonth(stDate Date1)
{
    stDate EndOfMontDate;

    EndOfMontDate.Day = NumberOfDaysInMonth(Date1.Month, Date1.Year);
    EndOfMontDate.Month = Date1.Month;
    EndOfMontDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfMontDate, true);
}

short DateTime::DaysUntilTheEndOfYear(stDate Date1)
{
    stDate EndOfYearDate;

    EndOfYearDate.Day = 31;
    EndOfYearDate.Month = 12;
    EndOfYearDate.Year = Date1.Year;

    return GetDifferenceInDays(Date1, EndOfYearDate, true);
}

int DateTime::GetVacationDays(stDate vacationStartDate, stDate vacationEndDate)
{
    int VacationDays = 0;

    if (IsDate1_After_Date2(vacationStartDate, vacationEndDate)) // to make sure that vacation start date is before vacation end date
        SwapDates(vacationStartDate, vacationEndDate);

    while (!IsDatesAreEquals(vacationStartDate, vacationEndDate))
    {
        AddDaysToDate(vacationStartDate, 1);

        if (IsBusinessDay(vacationStartDate))
            VacationDays++;
    }

    return VacationDays;
}

stDate DateTime::GetVacationEndDate(stDate vacationStardDate, int vacationDays)
{
    short WeekEndCounter = 0;

    //in case the data  is weekend keep adding one day util you reach business day
    //we get rid of all weekends before the first business day
    while (IsWeekEnd(vacationStardDate))
    {
        AddDaysToDate(vacationStardDate, 1);
    }

    //here we increase the vacation dates to add all weekends to it.

    for (short i = 1; i <= vacationDays + WeekEndCounter; i++)
    {

        if (IsWeekEnd(vacationStardDate))
            WeekEndCounter++;

        AddDaysToDate(vacationStardDate, 1);
    }

    //in case the return date is week end keep adding one day util you reach business day
    while (IsWeekEnd(vacationStardDate))
    {
        AddDaysToDate(vacationStardDate, 1);
    }

    return vacationStardDate;
}

bool DateTime::IsPerdiodsOverlaps(const stPeriod& Period1, const stPeriod& Period2)
{
    if (
        GetComparingDatesResult(Period2.StartDate, Period1.EndDate) == enDateCompare::After
        ||
        GetComparingDatesResult(Period1.StartDate, Period2.EndDate) == enDateCompare::After
        )
    {
        return false;
    }
    else
        return true;
}

bool DateTime::IsDateWithInPeriod(const stPeriod& period, const stDate& date)
{
    return !(GetComparingDatesResult(date, period.StartDate) == enDateCompare::Before
        ||
        GetComparingDatesResult(date, period.EndDate) == enDateCompare::After
        );
}

int DateTime::GetPeriodsOverlapingDays(stPeriod Period1, stPeriod Period2)
{
    if (!IsPerdiodsOverlaps(Period1, Period2))
        return 0;

    int DaysOverlaped = 0;

    int period1Length = GetPeriodLength(Period1);
    int period2Length = GetPeriodLength(Period2);

    if (period1Length < period2Length)
    {
        for (int i = 0; i < period1Length; i++)
        {
            if (IsDateWithInPeriod(Period2, Period1.StartDate))
                DaysOverlaped++;

            AddDaysToDate(Period1.StartDate, 1);
        }
    }
    else
    {
        for (int i = 0; i < period2Length; i++)
        {
            if (IsDateWithInPeriod(Period1, Period2.StartDate))
                DaysOverlaped++;

            AddDaysToDate(Period2.StartDate, 1);
        }
    }
    return DaysOverlaped;
}

std::string DateTime::DateToString(const stDate& date)
{
    return (std::to_string(date.Day) + "/" + std::to_string(date.Month) + "/" + std::to_string(date.Year));
}

stDate DateTime::StringToDate(const std::string& DateLine)
{
    stDate Date;

    std::vector<std::string> vDataLines = String::SliptString("/", DateLine);

    Date.Day = std::stoi(vDataLines[0]);
    Date.Month = std::stoi(vDataLines[1]);
    Date.Year = std::stoi(vDataLines[2]);

    return Date;
}

void DateTime::PrintDate(const stDate& Date, std::string format)
{
    format = String::ReplaceWordInString(format, "dd", std::to_string(Date.Day));
    format = String::ReplaceWordInString(format, "mm", std::to_string(Date.Month));
    format = String::ReplaceWordInString(format, "yyyy", std::to_string(Date.Year));

    std::cout << format;
}

void DateTime::PrintMounthCalender(short mounth, short year)
{
    std::cout << "\n-----------------------" << MounthShortName(mounth) << "------------------------- \n";
    std::cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSut\n";

    stDate Date;
    Date.Year = year;
    Date.Month = mounth;
    Date.Day = 1;
    short dayIndex = DayOfWeekOrder(Date);

    int rawCounter;
    for (rawCounter = 0; rawCounter < dayIndex; rawCounter++)
    {
        std::cout << "\t";
    }

    for (int i = 1; i <= NumberOfDaysInMonth(mounth, year); i++)
    {
        rawCounter++;

        std::cout << i << "\t";

        if (rawCounter >= 7)
        {
            std::cout << std::endl;
            rawCounter = 0;
        }
    }
    std::cout << "\n--------------------------------------------------- \n";
}

void DateTime::PrintYearCalender(short year)
{
    std::cout << "--------------------------------------------------\n\n";
    std::cout << "\t\t Calender - " << year << "\n\n";
    std::cout << "--------------------------------------------------\n\n";

    for (int i = 1; i <= 12; i++)
    {
        PrintMounthCalender(i, year);
        std::cout << std::endl;
    }
}