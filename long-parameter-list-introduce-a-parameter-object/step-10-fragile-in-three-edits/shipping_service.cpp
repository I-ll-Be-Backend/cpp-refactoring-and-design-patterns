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

struct Parcel {
    double weightKg;
    double lengthCm;
    double widthCm;
    double heightCm;
    bool fragile;

    double billableKg() const {
        double volumetricKg = lengthCm * widthCm * heightCm / 5000;
        return std::max(weightKg, volumetricKg);
    }
};

class ShippingService {
public:
    explicit ShippingService(const RateTable& rates) : rates(rates) {}

    Quote quote(const Address& from,
                const Address& to, const Parcel& parcel,
                bool express) const {
        double total = price(from, to, parcel, express);
        return Quote{from.postal, to.postal, total};
    }

private:
    double price(const Address& from, const Address& to,
                 const Parcel& parcel, bool express) const {
        double cost = rates.perKg(from.country, to.country)
                      * parcel.billableKg();
        if (parcel.fragile) cost *= 1.2;
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
        Address to{customer.postalCode(), customer.country()};
        Parcel parcel{cart.weightKg(), cart.lengthCm(),
                      cart.widthCm(), cart.heightCm(), cart.fragile()};
        return shipping.quote(from, to, parcel, cart.express());
    }
};
