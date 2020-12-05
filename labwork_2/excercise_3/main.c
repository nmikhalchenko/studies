// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shared_code/shared_code.h"

typedef enum
{
    Month_January,
    Month_February,
    Month_March,
    Month_April,
    Month_May,
    Month_June,
    Month_July,
    Month_August,
    Month_September,
    Month_October,
    Month_November,
    Month_December,
    Month_Unknown
}
Month;

typedef enum
{
    Season_Winter,
    Season_Spring,
    Season_Summer,
    Season_Autumn,
    Season_Unknown
}
Season;

typedef struct
{
    Season season;
    Month month1;
    Month month2;
    Month month3;
}
MonthsOfSeason;

int strEqual(const char* s1, const char* s2)
{
    return strcmp(s1, s2) == 0 ? 1 : 0;
}

const char* translateMonthEnum(Month value)
{
    switch (value)
    {
        case Month_January:
            return "January";

        case Month_February:
            return "February";

        case Month_March:
            return "March";

        case Month_April:
            return "April";

        case Month_May:
            return "May";

        case Month_June:
            return "June";

        case Month_July:
            return "July";

        case Month_August:
            return "August";

        case Month_September:
            return "September";

        case Month_October:
            return "October";

        case Month_November:
            return "November";

        case Month_December:
            return "December";

	    case Month_Unknown:
	        return "Unknown month";
    }

    return "Unknown month";
}

Season parseSeason(const char* seasonName)
{
    if (strEqual(seasonName, "winter") ||
        strEqual(seasonName, "Winter"))
        return Season_Winter;

    if (strEqual(seasonName, "spring") ||
        strEqual(seasonName, "Spring"))
        return Season_Spring;

    if (strEqual(seasonName, "summer") ||
        strEqual(seasonName, "Summer"))
        return Season_Summer;

    if (strEqual(seasonName, "autumn") ||
        strEqual(seasonName, "Autumn"))
        return Season_Autumn;

    return Season_Unknown;
}

int main(void)
{
    #define SEASON_COUNT (4)

    MonthsOfSeason months[SEASON_COUNT] =
    {
        {
            Season_Winter, 
            Month_December,
            Month_January, 
            Month_February
        },
        {
            Season_Spring,
            Month_March,
            Month_April,
            Month_May
        },
        {
            Season_Summer,
            Month_June,
            Month_July,
            Month_August
        },
        {
            Season_Autumn,
            Month_September,
            Month_October,
            Month_November
        }
    };

    #define BUFFER_SIZE (64)
    char buffer[BUFFER_SIZE] = {0};
    requestString(BUFFER_SIZE, buffer, "Enter the season's name: ");

    Season season = parseSeason(buffer);
    if (season == Season_Unknown)
    {
        puts("Unknown season.");
        return -1;
    }

    for (int i = 0; i < SEASON_COUNT; i++)
    {
        if (season == months[i].season)
        {
            printf("%s\n%s\n%s\n",
                translateMonthEnum(months[i].month1),
                translateMonthEnum(months[i].month2),
                translateMonthEnum(months[i].month3));
            break;
        }
    }

    return 0;
}
