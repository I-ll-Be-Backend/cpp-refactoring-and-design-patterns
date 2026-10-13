#include <format>
#include <string>

struct Cart {
    double subtotal;
    bool member;
};
struct Checkout {
    double shippingFee(const Cart& cart) const {
        if (cart.subtotal >= 50.0) {
            return 0.0;
        }
        return 4.99;
    }
};

struct CartBanner {
    std::string message(const Cart& cart) const {
        if (cart.subtotal < 50.0) {
            double missing = 50.0 - cart.subtotal;
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
