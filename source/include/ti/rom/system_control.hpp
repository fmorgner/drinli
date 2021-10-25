#ifndef DRINLI_TI_ROM_SYSTEM_CONTROL_HPP
#define DRINLI_TI_ROM_SYSTEM_CONTROL_HPP

#include "ti/rom/api_table.hpp"

#include <cstdint>

namespace ti::rom
{
  struct system_control
  {
    using table = api_table<13>;

    enum struct peripheral : std::uint32_t
    {
      gpio_f = 0x2000'0020,
    };

    auto inline static sleep() -> void
    {
      using function = table::function<0, void()>;
      return function::invoke();
    }

    auto inline static reset() -> void
    {
      using function = table::function<19, void()>;
      return function::invoke();
    }

    auto inline static enable(peripheral peripheral) -> void
    {
      using function = table::function<6, void(std::uint32_t)>;
      return function::invoke(peripheral);
    };
  };

}  // namespace ti::rom::system_control

#endif