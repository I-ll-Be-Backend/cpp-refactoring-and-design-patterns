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
    double fee(const Ticket& t) const {
        if (t.minutes <= 15) return 0;
        return std::min(t.hours() * 3.0, 20.0);
    }

    double charge(const Ticket& t) const {
        return fee(t);
    }
};
