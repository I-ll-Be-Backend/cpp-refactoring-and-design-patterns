#include <algorithm>
#include <chrono>
using std::chrono::sys_days;

struct Booking {
    sys_days checkIn;
    double total;
    int nights;
    char rate;
    bool loyal;
};
class CancellationPolicy {
    static constexpr int FREE_CANCELLATION_DAYS = 14;
    static constexpr int LAST_MINUTE_DAYS = 2;

public:
    double fee(const Booking& b, sys_days today) const {
        long daysBeforeCheckIn = (b.checkIn - today).count();
        // free cancellation 14 days or more before check-in
        if (daysBeforeCheckIn >= FREE_CANCELLATION_DAYS) return 0;
        // non-refundable or under 2 days out: pay in full
        if (b.rate == 'N'
            || daysBeforeCheckIn < LAST_MINUTE_DAYS) return b.total;
        // otherwise half the total
        double f = b.total * 0.5;
        // partner contracts require a one-night minimum
        return std::max(f, b.total / b.nights);
    }
};
