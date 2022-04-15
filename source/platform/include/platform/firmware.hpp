#ifndef DRINLI_PLATFORM_FIRMWARE_HPP
#define DRINLI_PLATFORM_FIRMWARE_HPP

[[noreturn]] auto firmware_main() -> void;

namespace drinli::platform::detail
{
  using ::firmware_main;
}

#endif