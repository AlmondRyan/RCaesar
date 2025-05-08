#ifndef BASE64DECODER_H
#define BASE64DECODER_H

#include <string>
#include <stdexcept>
#include <vector>

namespace RCaesar {
    namespace Base64 {
        class Base64Decoder {
        private:
            static const ::std::string base64_chars;
            static const char padding_char = '=';

            static bool is_base64(unsigned char c) {
                return (isalnum(c) || (c == '+') || (c == '/'));
            }

            static unsigned char decode_char(unsigned char c) {
                if (c >= 'A' && c <= 'Z') return c - 'A';
                if (c >= 'a' && c <= 'z') return c - 'a' + 26;
                if (c >= '0' && c <= '9') return c - '0' + 52;
                if (c == '+') return 62;
                if (c == '/') return 63;
                throw ::std::invalid_argument("Invalid Base64 character");
            }

        public:
            static ::std::vector<uint8_t> decode(const ::std::string& encoded) {
                std::vector<uint8_t> decoded;
                int i = 0;
                uint32_t buffer = 0;
                int bits_collected = 0;

                for (char c : encoded) {
                    if (c == padding_char) break;

                    if (!is_base64(c)) continue;

                    buffer = (buffer << 6) | decode_char(c);
                    bits_collected += 6;

                    if (bits_collected >= 8) {
                        bits_collected -= 8;
                        decoded.push_back((buffer >> bits_collected) & 0xFF);
                    }
                }

                return decoded;
            }
        };

        const ::std::string Base64Decoder::base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    }
}

#endif