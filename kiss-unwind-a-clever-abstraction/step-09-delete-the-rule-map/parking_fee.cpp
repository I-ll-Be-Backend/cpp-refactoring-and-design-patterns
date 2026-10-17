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
        double f = 0;
        f = t.hours() * 3.0;
        f = std::min(f, 20.0);
        f = t.minutes <= 15 ? 0 : f;
        return f;
    }

    double charge(const Ticket& t) const {
        return fee(t);
    }
};
