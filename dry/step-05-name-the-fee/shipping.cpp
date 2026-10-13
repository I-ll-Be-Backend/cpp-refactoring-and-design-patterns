#include <format>
#include <string>

struct Cart {
    double subtotal;
    bool member;
};
class ShippingPolicy {
public:
    static constexpr double FREE_FROM = 50.0;
    static constexpr double FEE = 4.99;
};

struct Checkout {
    double shippingFee(const Cart& cart) const {
        if (cart.subtotal >= ShippingPolicy::FREE_FROM) {
            return 0.0;
        }
        return ShippingPolicy::FEE;
    }
};

struct CartBanner {
    std::string message(const Cart& cart) const {
        if (cart.subtotal < ShippingPolicy::FREE_FROM) {
            double missing = ShippingPolicy::FREE_FROM - cart.subtotal;
            return std::format("Add ${:.2f} to ship free", missing);
        }
        return "Your order ships free";
    }
};

struct OrderEmail {
    std::string shippingLine(const Cart& cart) const {
        bool free = cart.subtotal >= ShippingPolicy::FREE_FROM;
        if (free) return "Shipping: free";
        return std::format("Shipping: ${:.2f}", ShippingPolicy::FEE);
    }
};
