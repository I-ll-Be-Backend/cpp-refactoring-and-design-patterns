#include <algorithm>
#include <format>
#include <string>
struct Loan {
    int daysOut;
    bool student;
};

struct Fees {
    static constexpr int LOAN_DAYS = 14;
    static constexpr double STUDENT_RATE = 0.10;
    static constexpr double STANDARD_RATE = 0.25;
    static constexpr double MAX_FINE = 10.0;

    double calc(const Loan& loan) const {
        int daysLate = loan.daysOut - LOAN_DAYS;
        if (daysLate <= 0) {
            return 0.0;
        }
        double dailyRate = loan.student ? STUDENT_RATE : STANDARD_RATE;
        return std::min(daysLate * dailyRate, MAX_FINE);
    }
};

struct ReturnDesk {
    Fees fees;

    std::string receipt(const Loan& loan) const {
        return std::format("Fine: ${:.2f}", fees.calc(loan));
    }
};
