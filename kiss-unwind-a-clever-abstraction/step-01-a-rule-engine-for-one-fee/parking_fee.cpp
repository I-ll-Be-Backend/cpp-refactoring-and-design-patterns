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
    using Rule = std::function<double(const Ticket&, double)>;
    inline static const std::map<std::string, Rule> RULES = {
        {"base", [](auto& t, double f) { return t.hours() * 3.0; }},
        {"cap", [](auto& t, double f) { return std::min(f, 20.0); }},
        {"grace", [](auto& t, double f) { return t.minutes <= 15 ? 0 : f; }},
    };

    double fee(const Ticket& t, const std::vector<std::string>& plan) const {
        double f = 0;
        for (const auto& name : plan) f = RULES.at(name)(t, f);
        return f;
    }

    double charge(const Ticket& t) const {
        return fee(t, {"base", "cap", "grace"});
    }
};
