#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>

struct Ticket {
    int minutes;
    bool electric;
    int hours() const { return (minutes + 59) / 60; }
};
struct ParkingFee {
    static constexpr double HOURLY_RATE = 3.0;
    static constexpr double DAILY_CAP = 20.0;
    static constexpr int GRACE_MINUTES = 15;
    static constexpr int EV_FREE_HOURS = 2;

    double charge(const Ticket& t) const {
        if (t.minutes <= GRACE_MINUTES) return 0;
        int hours = t.hours();
        if (t.electric) hours = std::max(0, hours - EV_FREE_HOURS);
        return std::min(hours * HOURLY_RATE, DAILY_CAP);
    }
};
