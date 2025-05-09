#ifndef RC_UTILS_H
#define RC_UTILS_H

#include "Base64Decoder.h"
#include "Exceptions.h"
#include "Feature.h"
#include "defs.h"

#include <algorithm>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace RCaesar {
    bool is_unique_or_complete(const ::std::string &enc_sheet) {
        ::std::unordered_set<char> unique_chars(enc_sheet.begin(), enc_sheet.end());
        if (Features::getInstance().if_feature_enabled(2)) {
            return ::std::all_of(unique_chars.begin(), unique_chars.end(), ::isalpha) && enc_sheet.size() == 26;
        }
        return unique_chars.size() == 26 && ::std::all_of(unique_chars.begin(), unique_chars.end(), ::isalpha);
    }

    bool check_encrypt_sheet_valid(::std::string enc_sheet) {
        bool secret_feature_enabled = Features::getInstance().if_feature_enabled(3);

        if (Features::getInstance().if_feature_enabled(1)) {
            for (auto &i : enc_sheet) {
                if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')) {
                    continue;
                } else {
                    throw Exceptions::UnsupportedCharacter("Unsupported Character catched in encode sheet.");
                    return false;
                }
            }
        }

        if (Features::getInstance().if_feature_enabled(2)) {
            if (enc_sheet.size() != 26) {
                throw Exceptions::NotValidLength("Encode sheet length isn't 26. If you make sure this is 'intentional', please disable feature Id 2");
                return false;
            }
        }

        if (!is_unique_or_complete(enc_sheet)) {
            throw Exceptions::SheetIsNotUnique("Encode sheet is not unique, please make sure all characters in the encode sheet are unique.");
            return false;
        }

        if (enc_sheet == default_alphabet) {
            ::std::string err_desc = "Encode sheet is the same as default default_alphabet. Please use a different encode sheet.";
            if (secret_feature_enabled) {
                ::std::vector<uint8_t> res = Base64::Base64Decoder::decode("IElmIHlvdSBlbnRlciBhIHNhbWUgc2hlZXQsIHdoeSB5b3UgdXNlIHRoaXM/IEZvciByZWFsIGJyby4=");
                err_desc += ::std::string(res.begin(), res.end());
            }
            throw Exceptions::SheetIsNotUnique(err_desc.c_str());
            return false;
        }

        return true;
    }

    ::std::string to_lower(::std::string obj) {
        ::std::string k;
        for (char i : obj) {
            k += tolower(i);
        }
        return k;
    }

    namespace ShowInstructions {
        void show_help_for_encode_type_1() {
            system("cls");
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "[Type 1]: Increasing." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "Increasing Cipher means you got a ::std::string need to encode, and a basic step you want to move." << ::std::endl;
            ::std::cout << "The first character in the ::std::string will be shifted for the step you give, " << ::std::endl;
            ::std::cout << "The second character in the ::std::string will be shifted (step + 1) steps. And so on." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << ::std::endl;
        }

        void show_help_for_encode_type_0() {
            system("cls");
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "[Type 0]: Basic." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "Basic Cipher, move character(s) in given steps." << ::std::endl;
            ::std::cout << "Positive numbers means move forward, negative numbers means move backward." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
        }

        void show_help_for_encode_type_2() {
            system("cls");
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "[Type 2]: Group." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "Group Cipher, split the characters into groups, and shift each groups instead all of them." << ::std::endl;
            ::std::cout << "For example, if you enter 5 characters but you want to divided them by 2 characters a group," << ::std::endl;
            ::std::cout << "the less characters will be splited into another group." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
        }

        void show_help_for_encode_type_3() {
            system("cls");
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "[Type 3]: Multi Encode Sheet." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "Multi Encode Cipher, means the characters in given ::std::string will be shifted according" << ::std::endl;
            ::std::cout << "different sheet. Default sheet is basic English Alphabet, but you can enter custom" << ::std::endl;
            ::std::cout << "encode sheet." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
        }

        void show_help_for_encode_type_4() {
            system("cls");
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "[Type 4]: Multi Encode Sheet with Grouped Input." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "Multi Encode Cipher, means the characters in given ::std::string will be shifted according" << ::std::endl;
            ::std::cout << "different sheet. Default sheet is basic English Alphabet, but you can enter custom" << ::std::endl;
            ::std::cout << "encode sheet." << ::std::endl;
            ::std::cout << "As the difference between type 3 and type 4, type 3 is the basic caesar encode, but type 4" << ::std::endl;
            ::std::cout << "combined type 2." << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
        }

        void show_help_for_encode_type_5() {
            system("cls");
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "[Type 5]: Encrypt Word - Use word as the sheet" << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
            ::std::cout << "This encryption method uses a keyword to determine the shift steps for each character." << ::std::endl;
            ::std::cout << "For example:" << ::std::endl;
            ::std::cout << "  Input text: Hello" << ::std::endl;
            ::std::cout << "  Keyword: Key" << ::std::endl;
            ::std::cout << "  Process:" << ::std::endl;
            ::std::cout << "    - K = 11 (position in default_alphabet) shifts H -> S" << ::std::endl;
            ::std::cout << "    - E = 5  (position in default_alphabet) shifts E -> J" << ::std::endl;
            ::std::cout << "    - Y = 25 (position in default_alphabet) shifts L -> K" << ::std::endl;
            ::std::cout << "    - K = 11 (back to first letter) shifts L -> W" << ::std::endl;
            ::std::cout << "    - E = 5  (second letter) shifts O -> T" << ::std::endl;
            ::std::cout << "  Result: SJKWT" << ::std::endl;
            ::std::cout << "=============================================================================================" << ::std::endl;
        }
    } // namespace ShowInstructions

    char move_alpha_fwd(char objx, int step, ::std::string enc_sheet = default_alphabet) {
        bool res = true;
        if (enc_sheet != default_alphabet) {
            try {
                res = check_encrypt_sheet_valid(enc_sheet);
            } catch (::std::exception &e) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << e.what() << ::std::endl;
            }
        }

        int x = objx - 97;
        x %= enc_sheet.size();

        for (int i = 0; i < step; i++) {
            x++;
            if (x >= enc_sheet.size()) {
                x %= enc_sheet.size();
            }
        }

        return enc_sheet[x];
    }

    char move_alpha_bwd(char objx, int step, ::std::string enc_sheet = default_alphabet) {
        bool res = true;
        if (enc_sheet != default_alphabet) {
            try {
                res = check_encrypt_sheet_valid(enc_sheet);
            } catch (::std::exception &e) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << e.what() << ::std::endl;
            }
        }

        int x = objx - 97;
        x %= enc_sheet.size();

        for (int i = 0; i < step; i++) {
            x--;
            if (x < 0) {
                x = enc_sheet.size() - 1;
            }
        }

        return enc_sheet[x];
    }

    ::std::vector<::std::string> split_size(int size, ::std::string obj) {
        ::std::vector<::std::string> final;
        ::std::string cur;
        int flg = 0;
        for (char i : obj) {
            flg++;
            cur += i;

            if (flg == size) {
                final.push_back(cur);
                cur.clear();
                flg = 0;
            }
        }

        if (flg == 1) {
            final.push_back(::std::string(1, obj.at(obj.size() - 1)));
        }
        return final;
    }
} // namespace RCaesar

#endif