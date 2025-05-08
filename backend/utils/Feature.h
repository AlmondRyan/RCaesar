#ifndef FEATURE
#define FEATURE

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace RCaesar {
    struct FeatureObject {
        int         id;
        std::string description;

        bool operator==(const FeatureObject &obj) const {
            return id == obj.id && description == obj.description;
        }
    };

} // namespace RCaesar

namespace std {
    template <>
    struct hash<RCaesar::FeatureObject> {
        size_t operator()(const RCaesar::FeatureObject &obj) const {
            size_t h1 = hash<int>()(obj.id);
            size_t h2 = hash<string>()(obj.description);
            return h1 ^ (h2 << 1);
        }
    };
} // namespace std

namespace RCaesar {

    class Features {
    private:
        Features() = default;
        Features(const Features &) = delete;
        Features                         &operator=(const Features &) = delete;
        ::std::unordered_set<FeatureObject> feature_lists;

    public:
        static Features &getInstance() {
            static Features instance;
            return instance;
        }

        static ::std::string genDescriptor(int id);
        static bool if_feature_enabled(int id);
        static void enable_feature(int id);
        static void disable_feature(int id);
    };
} // namespace RCaesar

#endif // FEATURE