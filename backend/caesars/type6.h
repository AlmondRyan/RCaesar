#ifndef RCAESAR_TYPE_6_H
#define RCAESAR_TYPE_6_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type6() {
            std::string inpx;
            ShowInstructions::show_help_for_encode_type_0();
            ::std::string res;
            ::std::cout << ::std::endl
                        << "Enter encrypted text: ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);

            ::std::cout << "Enter shift steps that used for encryption: ";
            int steps;
            if (!(::std::cin >> steps)) {
                ::std::cin.clear();
                IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                INVALID_STEPS
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::cout << "\nProcessing decryption..." << ::std::endl;
            for (int i = 0; i < inp.size(); i++) {
                if (steps < 0) {
                    steps = 26 + steps;
                }
                res += move_alpha_bwd(inp.at(i), steps);
            }
            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }

        CaesarStatus type6(std::string text, int steps) {
            ::std::string res;
            ::std::string inp = to_lower(text);
            
            if (steps < 0) {
                steps = 26 + steps;
            }
            
            for (int i = 0; i < inp.size(); i++) {
                res += move_alpha_bwd(inp.at(i), steps);
            }
            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif