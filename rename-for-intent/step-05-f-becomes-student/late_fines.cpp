#include <algorithm>
#include <format>
#include <string>
struct Loan {
    int daysOut;
    bool student;
};

struct Fees {
    double calc(const Loan& l) const {
        int x = l.daysOut - 14;
        if (x <= 0) {
            return 0.0;
        }
        double r = l.student ? 0.10 : 0.25;
        return std::min(x * r, 10.0);
    }
};

struct ReturnDesk {
    Fees fees;

    std::string receipt(const Loan& l) const {
        return std::format("Fine: ${:.2f}", fees.calc(l));
    }
};
