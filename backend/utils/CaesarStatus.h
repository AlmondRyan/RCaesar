#ifndef RCAESAR_CAESAR_STATUS_H
#define RCAESAR_CAESAR_STATUS_H

#include <string>
#include <utility>

namespace RCaesar {
    enum Status {
        SUCCESS,
        FAILED
    };

    struct CaesarStatus {
        Status      status;
        std::string res;
        std::string what;

        explicit CaesarStatus(Status status1 = Status::SUCCESS, std::string res1 = "", std::string what1 = "") : status(status1), res(std::move(res1)), what(std::move(what1)) {}
    };
} // namespace RCaesar

#endif