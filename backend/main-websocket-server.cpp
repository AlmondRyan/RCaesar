#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0A00

#include "utils/RequestParser.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using json = nlohmann::json;
using server = websocketpp::server<websocketpp::config::asio>;
using connection_hdl = websocketpp::connection_hdl;

class WebSocketServer : public RCaesar::RequestParser {
public:
    WebSocketServer() : m_server(), m_port(1145) {
        m_server.init_asio();
        m_server.set_message_handler(bind(&WebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
        m_server.set_access_channels(websocketpp::log::alevel::none);
        m_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
    }

    void run() {
        while (true) {
            try {
                m_server.listen(m_port);
                m_server.start_accept();
                std::cout << "WebSocket server listening on port " << m_port << std::endl;
                m_server.run();
                break;
            } catch (const websocketpp::exception &e) {
                if (e.code() == websocketpp::error::make_error_code(websocketpp::error::async_accept_not_listening)) {
                    std::cout << "Port " << m_port << " is in use, trying port " << m_port + 1 << std::endl;
                    m_port++;
                    m_server.stop_listening();
                    continue;
                }
                std::cerr << "Server error: " << e.what() << std::endl;
                break;
            } catch (const std::exception &e) {
                std::cerr << "Standard error: " << e.what() << std::endl;
                break;
            }
        }
    }

private:
    void on_message(connection_hdl hdl, server::message_ptr msg) {
        try {
            json request = json::parse(msg->get_payload());
            json response = handleRequest(request);
            m_server.send(hdl, response.dump(), msg->get_opcode());
        } catch (const std::exception &e) {
            json error_response = {
                {"request", "send-by-backend"},
                {"result", "failed"},
                {"reason", e.what()}};
            m_server.send(hdl, error_response.dump(), msg->get_opcode());
        }
    }

    server   m_server;
    uint16_t m_port;
};

int main() {
    try {
        WebSocketServer server;
        server.run();
    } catch (const std::exception &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
