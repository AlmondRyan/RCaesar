#include "Feature.h"
#include <stdexcept>

namespace RCaesar {
    ::std::string Features::genDescriptor(int id) {
        switch (id) {
        case 1:
            return R"(Enable error check of "If unsupported characters found in encode sheet.)";
        case 2:
            return R"(Enable error check of "If the length is not 26 (0 ~ 26) of encode sheet.)";
        case 3:
            return R"(Just, don't.)";
        default:
            throw ::std::invalid_argument("Unknown feature ID");
        }
    }

    bool Features::if_feature_enabled(int id) {
        auto         &features = getInstance();
        ::std::string desc = genDescriptor(id);
        return features.feature_lists.find({id, desc}) != features.feature_lists.end();
    }

    void Features::enable_feature(int id) {
        auto         &features = getInstance();
        ::std::string desc = genDescriptor(id);
        features.feature_lists.insert({id, desc});
    }

    void Features::disable_feature(int id) {
        auto         &features = getInstance();
        ::std::string desc = genDescriptor(id);
        features.feature_lists.erase({id, desc});
    }
} // namespace RCaesar