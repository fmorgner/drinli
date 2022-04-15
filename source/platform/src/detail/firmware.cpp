#include <bootstrap/firmware.hpp>
#include <platform/firmware.hpp>

#include <type_traits>

static_assert(
    std::is_same_v<decltype(drinli::platform::detail::firmware_main), decltype(drinli::bootstrap::detail::firmware_main)>);
