#ifndef DRINLI_TI_ROM_SYSTEM_CONTROL_HPP
#define DRINLI_TI_ROM_SYSTEM_CONTROL_HPP

#include "ti/rom/api_table.hpp"

#include <cstdint>

namespace ti::rom::system_control
{

  enum struct peripheral : std::uint32_t
  {
    gpio_f = 0x2000'0020,
  };

  auto inline sleep = [] {
    function<void(), 13, 0>()();
  };

  auto inline reset = [] {
    function<void(), 13, 19>()();
  };

  auto inline enable = [](peripheral peripheral) {
    function<void(std::uint32_t * peripheral_address), 13, 6>()(reinterpret_cast<std::uint32_t *>(peripheral));
  };

}  // namespace ti::rom::system_control

#endif