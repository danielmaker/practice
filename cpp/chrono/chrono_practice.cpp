#include <iostream>
#include <chrono>
#include <cstdint>

#include "date.h"

// std::chrono
// ----------------------------------------------------------------
// https://en.cppreference.com/w/cpp/chrono/duration
// https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
// https://en.cppreference.com/w/cpp/symbol_index/chrono_literals

void printCurrentTime()
{
    const auto tp = std::chrono::system_clock::now();

    using namespace date;
    std::cout << tp << std::endl;

    // https://stackoverflow.com/questions/15957805/extract-year-month-day-etc-from-stdchronotime-point-in-c

    const auto dp = date::floor<date::days>(tp);
    const auto ymd = date::year_month_day{dp};
    const auto time = date::make_time(std::chrono::duration_cast<std::chrono::milliseconds>(tp-dp));

    std::cout << "year        = " << ymd.year()  << std::endl;
    std::cout << "month       = " << ymd.month() << std::endl;
    std::cout << "day         = " << ymd.day()   << std::endl;
    std::cout << "hour        = " << time.hours().count()   << "h"     << std::endl;
    std::cout << "minute      = " << time.minutes().count() << "min"   << std::endl;
    std::cout << "second      = " << time.seconds().count() << "s"     << std::endl;
    std::cout << "millisecond = " << time.subseconds().count() << "ms" << std::endl;
}

int main(int argc, char const *argv[])
{
    printCurrentTime();

    using namespace std::chrono_literals;
    using FileTimeUnit = std::chrono::duration<std::int64_t, std::ratio<1, 10'000'000>>; // FILETIME is in 100 nanoseconds
    // auto someCalculation = 1s + 5ms + FileTimeUnit(someReceivedFILETIME);
    // FILETIME conversonOfCalculation = FileTimeUnit(someCalculation ).count();

    constexpr auto oneSecond = std::chrono::seconds {1};
    constexpr auto fiveMinutes = std::chrono::minutes {5};

    auto min = std::chrono::minutes {};
    auto sec = std::chrono::seconds {};
    auto msec = std::chrono::milliseconds {};
    auto micro = std::chrono::microseconds {};
    auto ft = FileTimeUnit {};


    std::cout << "A day is "
        << std::chrono::duration_cast<std::chrono::minutes>(24h).count() << " minutes" << ", or "
        << std::chrono::duration_cast<std::chrono::seconds>(24h).count() << " seconds"
        << std::endl;

    msec = 1s;
    micro = 1s;
    ft = 1s;

    std::cout << "minutes: " << min.count() << std::endl;
    std::cout << "milliseconds: " << msec.count() << std::endl;
    std::cout << "microseconds: " << micro.count() << std::endl;
    std::cout << "filetime: " << ft.count() << std::endl;

    return 0;
}
