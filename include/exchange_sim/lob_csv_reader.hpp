#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct Record {
    std::int64_t timestamp; // unix seconds
    double price;
};

struct ReadResult {
    std::vector<Record> records;
    std::string error;

    explicit operator bool() const { return error.empty(); }
};

ReadResult read_csv(const std::string &file_name);
