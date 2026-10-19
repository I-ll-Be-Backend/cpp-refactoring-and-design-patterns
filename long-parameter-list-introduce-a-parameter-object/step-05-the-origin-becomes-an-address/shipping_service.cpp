#include <algorithm>
#include <string>

struct RateTable {
    virtual ~RateTable() = default;
    virtual double perKg(const std::string& fromCountry,
                         const std::string& toCountry) const = 0;
};
struct Quote {
    std::string fromPostal;
    std::string toPostal;
    double price;
};
struct Cart {
    double weightKg() const;
    double lengthCm() const;
    double widthCm() const;
    double heightCm() const;
    bool express() const;
    bool fragile() const;
};
struct Customer {
    const std::string& postalCode() const;
    const std::string& country() const;
};
struct Address {
    std::string postal;
    std::string country;
};

class ShippingService {
public:
    explicit ShippingService(const RateTable& rates) : rates(rates) {}

    Quote quote(const Address& from,
                const std::string& toPostal,
                const std::string& toCountry, double weightKg,
                double lengthCm, double widthCm, double heightCm,
                bool express) const {
        double total = price(from, toCountry, weightKg,
                             lengthCm, widthCm, heightCm, express);
        return Quote{from.postal, toPostal, total};
    }

private:
    double price(const Address& from,
                 const std::string& toCountry,
                 double weightKg, double lengthCm, double widthCm,
                 double heightCm, bool express) const {
        double volumetricKg = lengthCm * widthCm * heightCm / 5000;
        double cost = rates.perKg(from.country, toCountry)
                      * std::max(weightKg, volumetricKg);
        return express ? cost * 1.5 : cost;
    }

    const RateTable& rates;
};

struct Checkout {
    static inline const std::string WAREHOUSE_POSTAL = "10115";
    static inline const std::string WAREHOUSE_COUNTRY = "DE";

    const ShippingService& shipping;

    Quote shippingFor(const Cart& cart, const Customer& customer) const {
        Address from{WAREHOUSE_POSTAL, WAREHOUSE_COUNTRY};
        return shipping.quote(from,
                              customer.postalCode(), customer.country(),
                              cart.weightKg(), cart.lengthCm(),
                              cart.widthCm(), cart.heightCm(),
                              cart.express());
    }
};
