#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0A00

#include <boost/asio.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <json.hpp>
#include <websocketpp/server.hpp>

#include "utils/ColorTextManager.h"
#include "utils/Exceptions.h"
#include "utils/Feature.h"
#include "utils/InteractiveTerminal.h"
#include "utils/WroteRegistry.h"
#include "utils/defs.h"
#include "utils/utils.h"
#include "utils/wait.h"

#include "caesars/type0.h"
#include "caesars/type1.h"
#include "caesars/type2.h"
#include "caesars/type3.h"
#include "caesars/type4.h"
#include "caesars/type5.h"
#include "caesars/type6.h"
#include "caesars/type7.h"

using namespace RCaesar;
using json = nlohmann::json;
using server = websocketpp::server<websocketpp::config::asio>;
using connection_hdl = websocketpp::connection_hdl;

int main() {
    Features::getInstance().enable_feature(FEAT_CHECK_UNSUPPORTED_CHARACTER); // NOLINT
    //    Features::getInstance().enable_feature(FEAT_CHECK_LENGTH_NOT_26);
    //    Features::getInstance().enable_feature(FEAT_SECRET);

    if (!Registry::ReadRegistryFlag()) {
        ::std::cout << CONSOLE_COLOR_RED << "WARNING: " << ::std::endl
                    << CONSOLE_COLOR_DEFAULT << "This program uses system hook to block systemic F11 Function (Full Screen)." << ::std::endl
                    << "It redirects F11 function to \'Use last method to continue cipher\'." << ::std::endl
                    << "If you mind this, please" << CONSOLE_COLOR_RED << " DO NOT " << CONSOLE_COLOR_DEFAULT
                    << "use this application." << ::std::endl
                    << ::std::endl
                    << "This information will be displayed once, after 15 seconds, it will be never showed again." << ::std::endl;

        Wait::wait_then_clear(15000);
        Registry::WriteRegistryFlag(true);
    }

    if (Features::getInstance().if_feature_enabled(FEAT_SECRET)) { // NOLINT
        ::std::vector<uint8_t> res = Base64::Base64Decoder::decode("SnVzdCwgZG9uJ3QsIHN0b3AsIHBsZWFzZS4=");
        ::std::cout << ::std::string(res.begin(), res.end()) << ::std::endl;
        ::std::cout << ::std::endl;
    } else {
        ::std::cout << R"(Basic Caesar Cipher Encoder & Decoder.)" << ::std::endl;
        ::std::cout << ::std::endl;
    }

    long long                    type = 0;
    ::std::string                inpx;
    bool                         validInput = false;
    ::std::vector<::std::string> customSheets;
    const unsigned long long     max_of_long_long = 9223372036854775807ull;

    while (true) {
        ::std::vector<::std::string> options = {
            "[0]  Basic - Simple character shift with fixed steps",
            "[1]  Increasing - Progressive shift with increasing steps",
            "[2]  Group - Split and encrypt by groups",
            "[3]  Multi Encrypt Sheet - Custom alphabet encryption",
            "[4]  Multi Encrypt Sheet with Grouped - Combined group and custom alphabet",
            "[5]  Encrypt Word - Use word as the sheet",
            "[6]  [Decode] Basic - Decrypt basic Caesar cipher",
            "[7]  [Decode] Increasing - Decrypt progressive shift cipher",
            "[8]  Exit"};

        ::std::cout << "\nSelect encryption/decryption method (Use arrow keys and Enter to select):" << ::std::endl;
        type = InteractiveTerminal::showMenu(options);

        if (type == 8) {
            return 0;
        } else if (type >= 0 && type <= 7) {
            validInput = true;
        } else {
            ::std::cout << CONSOLE_COLOR_RED << "[Error]" << CONSOLE_COLOR_DEFAULT
                        << ": Invalid Selection." << ::std::endl;
            continue;
        }

        bool encryptionSuccess = false;
        switch (type) {
        case 0: {
            CaesarStatus type0status = Caesars::type0();
            if (type0status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type0status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type0status.res << ::std::endl;
            }
            break;
        }
        case 1: {
            CaesarStatus type1status = Caesars::type1();
            if (type1status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type1status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type1status.res << ::std::endl;
            }
            break;
        }
        case 2: {
            CaesarStatus type2status = Caesars::type2();
            if (type2status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type2status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type2status.res << ::std::endl;
            }
            break;
        }
        case 3: {
            CaesarStatus type3status = Caesars::type3();
            if (type3status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type3status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type3status.res << ::std::endl;
            }
            break;
        }
        case 4: {
            CaesarStatus type4status = Caesars::type4(customSheets);
            if (type4status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type4status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type4status.res << ::std::endl;
            }
            break;
        }
        case 5: {
            CaesarStatus type5status = Caesars::type5();
            if (type5status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type5status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type5status.res << ::std::endl;
            }
            break;
        }
        case 6: {
            CaesarStatus type6status = Caesars::type6();
            if (type6status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type6status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type6status.res << ::std::endl;
            }
            break;
        }
        case 7: {
            CaesarStatus type7status = Caesars::type7();
            if (type7status.status == RCaesar::Status::FAILED) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << "Encryption Failed. Error " << type7status.what << ::std::endl;
            } else {
                ::std::cout << CONSOLE_COLOR_GREEN << "[Result]:" << CONSOLE_COLOR_DEFAULT << type7status.res << ::std::endl;
            }
            break;
        }
        default:
            break;
        }
    }
}