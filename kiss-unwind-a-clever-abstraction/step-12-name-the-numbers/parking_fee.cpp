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

    double charge(const Ticket& t) const {
        if (t.minutes <= GRACE_MINUTES) return 0;
        return std::min(t.hours() * HOURLY_RATE, DAILY_CAP);
    }
};
