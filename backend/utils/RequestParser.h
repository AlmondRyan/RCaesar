#pragma once
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "caesars/type0.h"
#include "caesars/type1.h"
#include "caesars/type2.h"
#include "caesars/type3.h"
#include "caesars/type4.h"
#include "caesars/type5.h"
#include "caesars/type6.h"
#include "caesars/type7.h"

using json = nlohmann::json;
using server = websocketpp::server<websocketpp::config::asio>;
using connection_hdl = websocketpp::connection_hdl;

namespace RCaesar {
    class RequestParser {
    public:
        static json handleRequest(const json &req) {
            if (!req.contains("request") ||
                !req.contains("method") ||
                !req.contains("params")) {
                throw std::invalid_argument("Missing fields in request.");
            }

            std::string requestType = req["request"], method = req["method"];
            json        params = req["params"];

            if (requestType == "encrypt") {
                if (method == "type0") {
                    std::string targetString = params["string"];
                    int         moveSteps = params["move-steps"];

                    auto type0Status = Caesars::type0(targetString, moveSteps);
                    if (type0Status.status != Status::SUCCESS) {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", "failed"}};
                    } else {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", type0Status.res}};
                    }
                } else if (method == "type1") {
                    std::string targetString = params["string"];
                    int         defaultMoveSteps = params["move-steps"];
                    auto        type1Status = Caesars::type1(targetString, defaultMoveSteps);
                    if (type1Status.status != Status::SUCCESS) {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", "failed"}};
                    } else {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", type1Status.res}};
                    }
                } else if (method == "type2") {
                    std::string      targetString = params["string"];
                    int              groupSize = params["group-size"];
                    std::vector<int> moveSteps = params["moveSteps"].get<std::vector<int>>();

                    auto type2Status = RCaesar::Caesars::type2(groupSize, targetString, moveSteps);

                    if (type2Status.status != RCaesar::Status::SUCCESS) {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", "failed"},
                            {"reason", type2Status.what} // 可选：返回错误信息
                        };
                    } else {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", type2Status.res}};
                    }
                } else if (method == "type3") {
                    std::string customAlphabet = params["customAlphabet"];
                    std::string input = params["input"];
                    int         shiftSteps = params["shiftSteps"];

                    auto type3Status = RCaesar::Caesars::type3(customAlphabet, input, shiftSteps);

                    if (type3Status.status != RCaesar::Status::SUCCESS) {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", "failed"},
                            {"reason", type3Status.what}
                        };
                    } else {
                        return json{
                            {"request", "send-by-backend"},
                            {"result", type3Status.res}};
                    }
                } else if (method == "type4") {
                    int groupSize = params["group-size"];
                    std::string input = params["input"];
                    std::vector<int> moveSteps = params["moveSteps"].get<std::vector<int>>();

                    auto type4Status = RCaesar::Caesars::type4(groupSize, input, moveSteps);

                    if (type4Status.status != RCaesar::Status::SUCCESS) {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", "failed"},
                            {"reason", type4Status.what}
                        };
                    } else {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", type4Status.res}
                        };
                    }
                } else if (method == "type5") {
                    std::string text = params["text"];
                    std::string keyword = params["keyword"];
                    bool startFromOne = params["startFromOne"];

                    auto type5Status = RCaesar::Caesars::type5(text, keyword, startFromOne);

                    if (type5Status.status != RCaesar::Status::SUCCESS) {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", "failed"},
                            {"reason", type5Status.what}
                        };
                    } else {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", type5Status.res}
                        };
                    }
                }
            } else if (requestType == "decrypt") {
                if (method == "type6") {
                    std::string text = params["text"];
                    int steps = params["steps"];

                    auto type6Status = RCaesar::Caesars::type6(text, steps);

                    if (type6Status.status != RCaesar::Status::SUCCESS) {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", "failed"},
                            {"reason", type6Status.what}
                        };
                    } else {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", type6Status.res}
                        };
                    }
                } else if (method == "type7") {
                    std::string text = params["text"];
                    int initial_steps = params["initial_steps"];

                    auto type7Status = RCaesar::Caesars::type7(text, initial_steps);

                    if (type7Status.status != RCaesar::Status::SUCCESS) {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", "failed"},
                            {"reason", type7Status.what}
                        };
                    } else {
                        return json{{
                            "request", "send-by-backend"},
                            {"result", type7Status.res}
                        };
                    }
                }
            } else {
                throw std::invalid_argument("Unknown Request.");
            }
            return json{{"request", "send-by-backend"}, {"result", "failed"}};
        }
    };
} // namespace RCaesar