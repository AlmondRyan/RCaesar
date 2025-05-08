#pragma once
#include <nlohmann/json.hpp>
#include <boost/asio.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <string>
#include <stdexcept>

using json = nlohmann::json;
using server = websocketpp::server<websocketpp::config::asio>;
using connection_hdl = websocketpp::connection_hdl;

namespace RCaesar {
    class RequestParser {
        static json handleRequest(const json& req) {
            if (!req.contains("request") ||
                !req.contains("method") ||
                !req.contains("params")) {
                throw std::invalid_argument("Missing fields in request.");
            }

            std::string requestType = req["request"], method = req["method"];
            json params = req["params"];

            if (requestType == "encrypt") {
                // TODO: Encrypt
            } else if (requestType == "decrypt") {
                // TODO: Decrypt
            } else {
                throw std::invalid_argument("Unknown Request.");
            }
        }
    };
}