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
class ShippingService {
public:
    explicit ShippingService(const RateTable& rates) : rates(rates) {}

    Quote quote(const std::string& fromPostal,
                const std::string& fromCountry,
                const std::string& toPostal,
                const std::string& toCountry, double weightKg,
                double lengthCm, double widthCm, double heightCm,
                bool express, bool fragile) const {
        double total = price(fromCountry, toCountry, weightKg,
                             lengthCm, widthCm, heightCm, express, fragile);
        return Quote{fromPostal, toPostal, total};
    }

private:
    double price(const std::string& fromCountry,
                 const std::string& toCountry,
                 double weightKg, double lengthCm, double widthCm,
                 double heightCm, bool express, bool fragile) const {
        double volumetricKg = lengthCm * widthCm * heightCm / 5000;
        double cost = rates.perKg(fromCountry, toCountry)
                      * std::max(weightKg, volumetricKg);
        if (fragile) cost *= 1.2;
        return express ? cost * 1.5 : cost;
    }

    const RateTable& rates;
};

struct Checkout {
    static inline const std::string WAREHOUSE_POSTAL = "10115";
    static inline const std::string WAREHOUSE_COUNTRY = "DE";

    const ShippingService& shipping;

    Quote shippingFor(const Cart& cart, const Customer& customer) const {
        return shipping.quote(WAREHOUSE_POSTAL, WAREHOUSE_COUNTRY,
                              customer.postalCode(), customer.country(),
                              cart.weightKg(), cart.lengthCm(),
                              cart.widthCm(), cart.heightCm(),
                              cart.express(), cart.fragile());
    }
};
