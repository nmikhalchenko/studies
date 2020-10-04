// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SEASON_COUNT 4

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
    Month_December
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

int equal(const char* s1, const char* s2)
{
    return strcmp(s1, s2) == 0 ? 1 : 0;
}

const char* translateMonthEnum(Month value)
{
    switch (value)
    {
        case Month_January:
            return "Январь";

        case Month_February:
            return "Февраль";

        case Month_March:
            return "Март";
        
        case Month_April:
            return "Апрель";

        case Month_May:
            return "Май";

        case Month_June:
            return "Июнь";

        case Month_July:
            return "Июль";

        case Month_August:
            return "Август";

        case Month_September:
            return "Сентябрь";

        case Month_October:
            return "Октябрь";

        case Month_November:
            return "Ноябрь";

        case Month_December:
            return "Декабрь";
    }
}

Season parseSeason(const char* seasonName)
{
    
    if ((equal(seasonName, "зима")) ||
        (equal(seasonName, "Зима")) ||
        (equal(seasonName, "winter")) ||
        (equal(seasonName, "Winter")))
        return Season_Winter;

    if ((equal(seasonName, "весна")) ||
        (equal(seasonName, "Весна")) ||
        (equal(seasonName, "spring")) ||
        (equal(seasonName, "Spring")))
        return Season_Spring;

    if ((equal(seasonName, "лето")) ||
        (equal(seasonName, "Лето")) ||
        (equal(seasonName, "summer")) ||
        (equal(seasonName, "Summer")))
        return Season_Summer;

    if ((equal(seasonName, "осень")) ||
        (equal(seasonName, "Осень")) ||
        (equal(seasonName, "autumn")) ||
        (equal(seasonName, "Autumn")))
        return Season_Autumn;

    return Season_Unknown;
}

int main(void)
{
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

    char buffer[64];
    
    puts("Введите название времени года:");
    scanf("%s", buffer);

    Season season = parseSeason(buffer);
    if (season == Season_Unknown)
    {
        puts("Неизвестное время года.");
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