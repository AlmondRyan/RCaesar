#ifndef RCAESAR_TYPE_3_H
#define RCAESAR_TYPE_3_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type3() {
            ::std::string sheet, res, inpx;

            ShowInstructions::show_help_for_encode_type_3();
            ::std::cout << ::std::endl
                        << "Enter your custom encryption alphabet (26 unique letters, no spaces): ";
            ::std::cin >> sheet;

            bool isValid = false;
            try {
                isValid = check_encrypt_sheet_valid(sheet);
                ::std::cout << CONSOLE_COLOR_GREEN << "[Success]: " << CONSOLE_COLOR_DEFAULT
                            << "Custom alphabet validated successfully!" << ::std::endl;
            } catch (std::exception &e) {
                std::cout << CONSOLE_COLOR_RED << "[Error]: " << CONSOLE_COLOR_DEFAULT << e.what() << ::std::endl;
                return CaesarStatus(RCaesar::Status::FAILED, "", "See up.");
            }

            ::std::cout << ::std::endl
                        << "Enter the text to encode (lowercase letters only): ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);

            ::std::cout << "Enter the shift steps (positive for forward, negative for backward): ";
            int steps = 0;
            if (!(::std::cin >> steps)) {
                ::std::cin.clear();
                IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                INVALID_STEPS
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::cout << "\nProcessing encryption with custom alphabet..." << ::std::endl;
            for (char i : inp) {
                if (steps < 0) {
                    steps = 26 + steps;
                }
                res += move_alpha_fwd(i, steps, sheet);
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif