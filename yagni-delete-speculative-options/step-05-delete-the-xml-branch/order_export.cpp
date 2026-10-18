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
  "export": {
    "format": "csv",
    "delimiter": ",",
    "header": true
  }
}
*/
struct ExportConfig {
    std::string format;
    std::string delimiter;
    bool header;
};

class OrderExport {
public:
    explicit OrderExport(const ExportConfig& cfg)
        : format(cfg.format),
          delimiter(cfg.delimiter),
          header(cfg.header) {}

    std::string exportOrders(const std::vector<Order>& orders) const {
        std::string out;
        if (header && format == "csv") {
            out += "id" + delimiter + "total\n";
        }
        for (const Order& o : orders) {
            if (format == "csv") {
                out += std::format("{}{}{}\n", o.id, delimiter, o.total);
            } else if (format == "json") {
                out += std::format("{{\"id\":\"{}\",\"total\":{}}}\n",
                                   o.id, o.total);
            } else {
                throw std::invalid_argument(format);
            }
        }
        return out;
    }

private:
    std::string format;
    std::string delimiter;
    bool header;
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
