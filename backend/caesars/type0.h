#ifndef RCAESAR_TYPE_0_H
#define RCAESAR_TYPE_0_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type0() {
            std::string inpx;

            ShowInstructions::show_help_for_encode_type_0();
            ::std::string res;
            ::std::cout << ::std::endl
                        << "Enter the text to encode (lowercase letters only): ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);

            ::std::cout << "Enter the shift steps (Positive numbers shift forward, negative shift backward): ";
            int steps;
            if (!(::std::cin >> steps)) {
                ::std::cin.clear();
                IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                INVALID_STEPS
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::cout << "\nProcessing encryption..." << ::std::endl;
            for (char i : inp) {
                if (steps < 0) {
                    steps = 26 + steps;
                }
                res += move_alpha_fwd(i, steps);
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }

        CaesarStatus type0(std::string target, int steps) {
            std::string res;
            for (char i : target) {
                if (steps < 0) {
                    steps = 26 + steps;
                }
                res += move_alpha_fwd(i, steps);
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif