#ifndef DRINLI_ROM_SYSTEM_CONTROL_HPP
#define DRINLI_ROM_SYSTEM_CONTROL_HPP

#include "rom/api.hpp"

#include <cstdint>

namespace drinli::rom::system_control
{

  // enum struct peripheral : std::uint32_t
  // {
  //   gpio_a = 0x2000'0001,
  //   gpio_b = 0x2000'0002,
  //   gpio_c = 0x2000'0004,
  //   gpio_d = 0x2000'0008,
  //   gpio_e = 0x2000'0010,
  //   gpio_f = 0x2000'0020,
  //   gpio_g = 0x2000'0040,
  //   gpio_h = 0x2000'0080,
  //   gpio_j = 0x2000'0100,
  // };

  auto inline static sleep() -> void
  {
    return api::tables::system_control::function<0, decltype(sleep)>::invoke();
  }

  auto inline static reset() -> void
  {
    return api::tables::system_control::function<19, decltype(reset)>::invoke();
  }

  auto inline static enable(uint32_t peripheral) -> void
  {
    return api::tables::system_control::function<6, decltype(enable)>::invoke(peripheral);
  }

  auto inline static disable_gpio_ahb(uint32_t gpio_peripheral) -> void
  {
    return api::tables::system_control::function<30, decltype(enable)>::invoke(gpio_peripheral);
  }

  auto inline static enable_gpio_ahb(uint32_t gpio_peripheral) -> void
  {
    return api::tables::system_control::function<29, decltype(enable)>::invoke(gpio_peripheral);
  }

}  // namespace drinli::rom::system_control

#endif
