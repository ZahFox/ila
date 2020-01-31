#pragma once

#include <iostream>
#include <memory>
#include <string>

#define ILA_DEBUG_LOG(category, message, ...)                                \
    fprintf(stderr, "[DEBUG] [%s] (%s:%d): ", category, __FILE__, __LINE__); \
    fprintf(stderr, message, ##__VA_ARGS__);                                 \
    fprintf(stderr, "\n");

#define ILA_CORE_LOG(category, level, message, ...)  \
    fprintf(stderr, "[%s] [%s]: ", level, category); \
    fprintf(stderr, message, ##__VA_ARGS__);         \
    fprintf(stderr, "\n");

namespace Ila {

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
}