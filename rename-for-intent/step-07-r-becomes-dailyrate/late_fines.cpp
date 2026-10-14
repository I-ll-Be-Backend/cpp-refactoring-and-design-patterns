#include <algorithm>
#include <format>
#include <string>
struct Loan {
    int daysOut;
    bool student;
};

struct Fees {
    double calc(const Loan& l) const {
        int daysLate = l.daysOut - 14;
        if (daysLate <= 0) {
            return 0.0;
        }
        double dailyRate = l.student ? 0.10 : 0.25;
        return std::min(daysLate * dailyRate, 10.0);
    }
};

struct ReturnDesk {
    Fees fees;

    std::string receipt(const Loan& l) const {
        return std::format("Fine: ${:.2f}", fees.calc(l));
    }
};
