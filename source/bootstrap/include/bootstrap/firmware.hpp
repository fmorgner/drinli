#ifndef DRINLI_BOOTSTRAP_FIRMWARE_HPP
#define DRINLI_BOOTSTRAP_FIRMWARE_HPP

[[noreturn]] auto firmware_main() -> void;

namespace drinli::bootstrap::detail
{
  using ::firmware_main;
}

#endif
