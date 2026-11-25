#include <exchange_sim/lob_csv.hpp>
#include <print>

int main() {
    auto result = read_csv("data/test-data-1.csv");
    for (const auto &record : result.records) {
        std::println("{},{}", record.timestamp, record.price);
    }
}
