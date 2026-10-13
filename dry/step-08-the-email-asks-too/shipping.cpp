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

    static bool shipsFree(const Cart& cart) {
        return cart.subtotal >= FREE_FROM;
    }
};

struct Checkout {
    double shippingFee(const Cart& cart) const {
        if (ShippingPolicy::shipsFree(cart)) {
            return 0.0;
        }
        return ShippingPolicy::FEE;
    }
};

struct CartBanner {
    std::string message(const Cart& cart) const {
        if (!ShippingPolicy::shipsFree(cart)) {
            double missing = ShippingPolicy::FREE_FROM - cart.subtotal;
            return std::format("Add ${:.2f} to ship free", missing);
        }
        return "Your order ships free";
    }
};

struct OrderEmail {
    std::string shippingLine(const Cart& cart) const {
        bool free = ShippingPolicy::shipsFree(cart);
        if (free) return "Shipping: free";
        return std::format("Shipping: ${:.2f}", ShippingPolicy::FEE);
    }
};
