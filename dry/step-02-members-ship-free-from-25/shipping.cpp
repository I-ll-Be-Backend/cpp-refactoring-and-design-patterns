#include <format>
#include <string>

struct Cart {
    double subtotal;
    bool member;
};
struct Checkout {
    double shippingFee(const Cart& cart) const {
        double freeFrom = cart.member ? 25.0 : 50.0;
        if (cart.subtotal >= freeFrom) {
            return 0.0;
        }
        return 4.99;
    }
};

struct CartBanner {
    std::string message(const Cart& cart) const {
        double limit = cart.member ? 25.0 : 50.0;
        if (cart.subtotal < limit) {
            double missing = limit - cart.subtotal;
            return std::format("Add ${:.2f} to ship free", missing);
        }
        return "Your order ships free";
    }
};

struct OrderEmail {
    std::string shippingLine(const Cart& cart) const {
        bool free = cart.subtotal >= 50.0;
        if (free) return "Shipping: free";
        return "Shipping: $4.99";
    }
};
