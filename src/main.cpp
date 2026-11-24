#include <charconv>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <system_error>
#include <vector>

const std::filesystem::path data_path =
    std::filesystem::path(__FILE__).parent_path().parent_path();

struct Record {
    std::int64_t timestamp; // unix seconds
    double price;
};

struct ReadResult {
    std::vector<Record> records;
    std::string error;

    explicit operator bool() const { return error.empty(); }
};

ReadResult read_csv(const std::string &file_name) {
    std::ifstream file(data_path / file_name);
    if (!file) {
        return {{}, "Could not open file: " + file_name};
    }

    ReadResult result;
    std::string line;
    std::size_t line_number = 0;

    while (std::getline(file, line)) {
        ++line_number;

        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); // handle CRLF line endings
        }

        const auto comma = line.find(',');
        if (comma == std::string::npos) {
            return {{}, "Malformed row at line " + std::to_string(line_number)};
        }

        Record record{};
        const auto [timestamp_end, timestamp_error] =
            std::from_chars(line.data(), line.data() + comma, record.timestamp);
        const auto [price_end, price_error] = std::from_chars(
            line.data() + comma + 1, line.data() + line.size(), record.price);

        if (timestamp_error != std::errc{} ||
            timestamp_end != line.data() + comma ||
            price_error != std::errc{} ||
            price_end != line.data() + line.size()) {
            return {{}, "Invalid data at line " + std::to_string(line_number)};
        }

        result.records.push_back(record);
    }

    return result;
}

int main() {
    auto result = read_csv("data/test-data-1.csv");
    for (const auto &record : result.records) {
        std::println("{},{}", record.timestamp, record.price);
    }
}
