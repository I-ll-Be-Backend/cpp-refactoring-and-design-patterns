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
    static constexpr int LOYALTY_FREE_DAYS = 7;
    static constexpr int LAST_MINUTE_DAYS = 2;
    static constexpr char NON_REFUNDABLE = 'N';

public:
    double fee(const Booking& b, sys_days today) const {
        long daysBeforeCheckIn = (b.checkIn - today).count();
        if (isFreeCancellation(b, daysBeforeCheckIn)) return 0;
        if (paysInFull(b, daysBeforeCheckIn)) return b.total;
        double halfTotal = b.total * 0.5;
        // partner contracts require a one-night minimum
        return std::max(halfTotal, nightlyPrice(b));
    }

private:
    static bool isFreeCancellation(const Booking& b, long days) {
        if (b.loyal) return days >= LOYALTY_FREE_DAYS;
        return days >= FREE_CANCELLATION_DAYS;
    }

    static bool paysInFull(const Booking& b, long days) {
        return b.rate == NON_REFUNDABLE || days < LAST_MINUTE_DAYS;
    }

    static double nightlyPrice(const Booking& b) {
        return b.total / b.nights;
    }
};
