#ifndef RCAESAR_TYPE_1_H
#define RCAESAR_TYPE_1_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type1() {
            std::string inpx;
            ShowInstructions::show_help_for_encode_type_1();
            ::std::string res;

            ::std::cout << ::std::endl
                        << "Enter the text to encode (lowercase letters only): ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);

            ::std::cout << "Enter the initial shift step (will increase for each character): ";
            int steps = 0;
            if (!(::std::cin >> steps)) {
                ::std::cin.clear();
                IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                INVALID_STEPS
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::cout << ::std::endl
                        << "Processing increasing encryption..." << ::std::endl;
            for (int i = 0; i < inp.size(); i++) {
                if (steps < 0) {
                    steps = 26 + steps;
                }
                int fstep = steps + i;
                res += move_alpha_fwd(inp.at(i), fstep);
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }

        CaesarStatus type1(std::string text, int steps) {
            ::std::string res;
            for (int i = 0; i < text.size(); i++) {
                if (steps < 0) {
                    steps = 26 + steps;
                }
                int fstep = steps + i;
                res += move_alpha_fwd(text.at(i), fstep);
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif