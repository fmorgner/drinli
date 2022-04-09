#ifndef DRINLI_ROM_SYSTEM_CONTROL_HPP
#define DRINLI_ROM_SYSTEM_CONTROL_HPP

#include "rom/detail/api_table.hpp"

#include <cstdint>

namespace drinli::rom::system_control
{

  auto inline static sleep() -> void
  {
    system_control_api_table::function<0, decltype(sleep)>::invoke();
  }

  // struct system_control
  // {
  //   using table = detail::api_table<13>;

  //   enum struct peripheral : std::uint32_t
  //   {
  //     gpio_f = 0x2000'0020,
  //   };

  //   auto inline static sleep() -> void
  //   {
  //     using function = table::function<0, void()>;
  //     return function::invoke();
  //   }

  //   auto inline static reset() -> void
  //   {
  //     using function = table::function<19, void()>;
  //     return function::invoke();
  //   }

  //   auto inline static enable(peripheral peripheral) -> void
  //   {
  //     using function = table::function<6, void(std::uint32_t)>;
  //     return function::invoke(peripheral);
  //   };

  //   auto inline static enable_ahb(peripheral peripheral) -> void
  //   {
  //     using function = table::function<29, void(std::uint32_t)>;
  //     return function::invoke(peripheral);
  //   };
  // };

}  // namespace drinli::rom::system_control

#endif
