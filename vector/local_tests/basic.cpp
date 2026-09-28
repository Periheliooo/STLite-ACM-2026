// Standalone tests for the interfaces implemented so far.
#include <iostream>
#include "../src/vector.hpp"

template <typename Action>
bool throws_bounds(Action action) {
    try {
        action();
    } catch (const sjtu::index_out_of_bound &) {
        return true;
    }
    return false;
}

int main() {
#ifdef TEST_NO_DEFAULT
    struct NoDefault {
        int value;
        explicit NoDefault(int x) : value(x) {}
    };
    sjtu::vector<NoDefault> v;
    return v.size() == 0 ? 0 : 1;
#else
    int failures = 0;
    auto check = [&](bool passed, const char *name) {
        std::cout << (passed ? "PASS: " : "FAIL: ") << name << '\n';
        if (!passed) ++failures;
    };
    sjtu::vector<int> v;
    check(v.size() == 0, "default vector has size 0");
    check(throws_bounds([&] { (void)v.at(0); }), "empty at(0) throws");
    check(throws_bounds([&] { (void)v[0]; }), "empty operator[](0) throws");
    check(throws_bounds([&] { (void)v.at(static_cast<size_t>(-1)); }),
          "large unsigned index throws");
    const sjtu::vector<int> &cv = v;
    check(throws_bounds([&] { (void)cv.at(0); }), "const empty at(0) throws");
    check(throws_bounds([&] { (void)cv[0]; }), "const empty operator[](0) throws");
    {
        sjtu::vector<int> copy(v);
        check(copy.size() == 0, "copy of empty vector has size 0");
    }
    check(v.size() == 0, "original survives copy destruction");
    return failures == 0 ? 0 : 1;
#endif
}
