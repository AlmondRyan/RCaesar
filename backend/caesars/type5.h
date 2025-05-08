#ifndef RCAESAR_TYPE_5_H
#define RCAESAR_TYPE_5_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type5() {
            ShowInstructions::show_help_for_encode_type_5();
            ::std::string res, inpx;

            ::std::cout << ::std::endl
                        << "Enter the text to encode (lowercase letters only): ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);

            ::std::cout << "Enter the keyword (letters only): ";
            ::std::string keyword;
            ::std::cin >> keyword;
            keyword = to_lower(keyword);

            ::std::cout << "Should 'A' start from 1? (1 for 1~26, 0 for 0~25) [Default: 1]: ";
            ::std::string startFromOne;
            getline(::std::cin >> ::std::ws, startFromOne);
            bool isStartFromOne = startFromOne.empty() || startFromOne == "1";

            if (!std::all_of(keyword.begin(), keyword.end(), ::isalpha)) {
                ::std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT
                            << "Keyword must contain only letters." << ::std::endl;
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::vector<int> shifts;
            for (char c : keyword) {
                shifts.push_back(c - 'a' + (isStartFromOne ? 1 : 0));
            }

            ::std::cout << "\nProcessing encryption with keyword..." << ::std::endl;
            for (size_t i = 0; i < inp.size(); i++) {
                int shift = shifts[i % shifts.size()];
                res += move_alpha_fwd(inp[i], shift);
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif