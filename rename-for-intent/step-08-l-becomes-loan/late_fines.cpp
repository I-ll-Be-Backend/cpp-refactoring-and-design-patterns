#include <algorithm>
#include <format>
#include <string>
struct Loan {
    int daysOut;
    bool student;
};

struct Fees {
    double calc(const Loan& loan) const {
        int daysLate = loan.daysOut - 14;
        if (daysLate <= 0) {
            return 0.0;
        }
        double dailyRate = loan.student ? 0.10 : 0.25;
        return std::min(daysLate * dailyRate, 10.0);
    }
};

struct ReturnDesk {
    Fees fees;

    std::string receipt(const Loan& loan) const {
        return std::format("Fine: ${:.2f}", fees.calc(loan));
    }
};
