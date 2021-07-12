#pragma once
#include <concepts>

namespace utils {
// Generic utility stuff goes here

// Check if First is equal to any of Val in pack.
template<typename First, typename ... Val>
  requires (std::equality_comparable_with<First, Val> || ...)
constexpr bool isAnyOf(const First& first, const Val& ... val) {
    return ((first == val) || ...);
};

}