#ifndef RCAESAR_TYPE_2_H
#define RCAESAR_TYPE_2_H

#include <string>
#include <iostream>
#include "../utils/utils.h"
#include "../utils/ColorTextManager.h"
#include "../utils/CaesarStatus.h"

namespace RCaesar {
    namespace Caesars {
        CaesarStatus type2() {
            std::string inpx;

            ShowInstructions::show_help_for_encode_type_2();
            ::std::vector<::std::string> splited;

            ::std::cout << ::std::endl
                        << "Enter the group size (number of characters per group): ";
            int groupSize;
            if (!(::std::cin >> groupSize)) {
                ::std::cin.clear();
                IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                INVALID_STEPS
                return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
            }

            ::std::cout << "Enter the text to encode (lowercase letters only): ";
            ::std::cin >> inpx;
            ::std::string inp = to_lower(inpx);
            ::std::cout << ::std::endl;
            int           ksize = static_cast<int>(inp.size());
            ::std::string res;
            splited = split_size(groupSize, inp);

            ::std::cout << CONSOLE_COLOR_CYAN << "[Info]: " << CONSOLE_COLOR_DEFAULT
                        << "Text split into " << splited.size() << " groups" << ::std::endl;

            int totalSteps = static_cast<int>(splited.size());
            int currentStep = 0;

            for (const auto& i : splited) {
                currentStep++;
                ::std::cout << "\nProcessing group " << currentStep << " of " << totalSteps << " (" << i << ")" << ::std::endl;
                int step = 0;

                if (i.size() < groupSize) {
                    ::std::cout << "Enter shift step for remaining characters: ";
                    if (!(::std::cin >> step)) {
                        ::std::cin.clear();
                        IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                        INVALID_STEPS
                        return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
                    }

                    if (step < 0) {
                        step += 26;
                    }
                } else {
                    ::std::cout << "Enter shift step for group " << currentStep << ": ";
                    if (!(::std::cin >> step)) {
                        ::std::cin.clear();
                        IGNORE_REMAIN_CHARACTERS_UNTIL_MEET_LINE_FEED
                        INVALID_STEPS
                        return CaesarStatus(RCaesar::Status::FAILED, "", "Invalid Steps.");
                    }
                    if (step < 0) {
                        step = 26 + step;
                    }
                }

                ::std::cout << "Processing group..." << ::std::endl;
                for (char j : i) {
                    res += move_alpha_fwd(j, step);
                }
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }

        CaesarStatus type2(int groupSize, std::string input, std::vector<int> moveSteps) {
            std::string inpx = input;
            ::std::vector<::std::string> splited;
            ::std::string inp = to_lower(inpx);
            ::std::string res;

            splited = split_size(groupSize, inp);

            int totalGroups = static_cast<int>(splited.size());
            int moveStepCount = static_cast<int>(moveSteps.size());

            for (int i = 0; i < totalGroups; ++i) {
                const auto& group = splited[i];
                int step = moveSteps[i % moveStepCount];
                step = ((step % 26) + 26) % 26;

                for (char ch : group) {
                    res += move_alpha_fwd(ch, step);
                }
            }

            return CaesarStatus(RCaesar::Status::SUCCESS, res);
        }
    }
}

#endif