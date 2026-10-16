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
    static constexpr char NON_REFUNDABLE = 'N';

public:
    double fee(const Booking& b, sys_days today) const {
        long daysBeforeCheckIn = (b.checkIn - today).count();
        if (isFreeCancellation(daysBeforeCheckIn)) return 0;
        if (paysInFull(b, daysBeforeCheckIn)) return b.total;
        double halfTotal = b.total * 0.5;
        // partner contracts require a one-night minimum
        return std::max(halfTotal, b.total / b.nights);
    }

private:
    static bool isFreeCancellation(long days) {
        return days >= FREE_CANCELLATION_DAYS;
    }

    static bool paysInFull(const Booking& b, long days) {
        return b.rate == NON_REFUNDABLE || days < LAST_MINUTE_DAYS;
    }
};
