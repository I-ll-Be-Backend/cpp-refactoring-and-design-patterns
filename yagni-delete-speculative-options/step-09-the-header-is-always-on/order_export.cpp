#include <format>
#include <stdexcept>
#include <string>
#include <vector>

struct Order {
    std::string id;
    double total;
    std::string postalCode;
};
struct OrderRepo {
    virtual ~OrderRepo() = default;
    virtual std::vector<Order> today() = 0;
};
struct Warehouse {
    virtual ~Warehouse() = default;
    virtual void uploadCsv(const std::string& csv) = 0;
};
/* config.json
{
  "export": {}
}
*/
struct ExportConfig {};

class OrderExport {
public:
    explicit OrderExport(const ExportConfig& cfg) {}

    std::string exportOrders(const std::vector<Order>& orders) const {
        std::string out;
        out += "id,total\n";
        for (const Order& o : orders) {
            out += std::format("{},{}\n", o.id, o.total);
        }
        return out;
    }
};

struct NightlyJob {
    ExportConfig config;
    OrderRepo& orders;
    Warehouse& warehouse;

    void run() {
        std::string csv = OrderExport(config).exportOrders(orders.today());
        warehouse.uploadCsv(csv);
    }
};
