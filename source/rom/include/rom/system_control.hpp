#ifndef DRINLI_ROM_SYSTEM_CONTROL_HPP
#define DRINLI_ROM_SYSTEM_CONTROL_HPP

#include "rom/api.hpp"

#include <cstdint>
#include <type_traits>

namespace drinli::rom::system_control
{

  namespace detail
  {

    auto inline static untyped_enable(uint32_t peripheral) -> void
    {
      return api::tables::system_control::function<6, decltype(untyped_enable)>::invoke(peripheral);
    }

    auto inline static untyped_disable_ahb(uint32_t peripheral) -> void
    {
      return api::tables::system_control::function<30, decltype(untyped_enable)>::invoke(peripheral);
    }

    auto inline static untyped_enable_ahb(uint32_t peripheral) -> void
    {
      return api::tables::system_control::function<29, decltype(untyped_enable)>::invoke(peripheral);
    }

  }  // namespace detail

  enum struct gpio : std::uint32_t
  {
    a = 0x2000'0001,
    b = 0x2000'0002,
    c = 0x2000'0004,
    d = 0x2000'0008,
    e = 0x2000'0010,
    f = 0x2000'0020,
    g = 0x2000'0040,
    h = 0x2000'0080,
    j = 0x2000'0100,
    k = 0xf000'0809,
    l = 0xf000'080a,
    m = 0xf000'080b,
    n = 0xf000'080c,
    p = 0xf000'080d,
    q = 0xf000'080e,
    r = 0xf000'080f,
    s = 0xf000'0810,
  };

  enum struct timer : std::uint32_t
  {
    watchdog_zero = 0x0000'0008,
    zero = 0x1010'0001,
    one = 0x1010'0002,
    two = 0x1010'0004,
    three = 0x1010'0008,
  };

  template<typename EnumType>
  concept peripheral =
      std::is_enum_v<EnumType> && std::disjunction_v<std::is_same<gpio, EnumType>, std::is_same<timer, EnumType>>;

  auto inline static sleep() -> void
  {
    return api::tables::system_control::function<0, decltype(sleep)>::invoke();
  }

  auto inline static reset() -> void
  {
    return api::tables::system_control::function<19, decltype(reset)>::invoke();
  }

  template<peripheral PeripheralType>
  auto inline static enable(PeripheralType gpio) -> void
  {
    return detail::untyped_enable(static_cast<std::underlying_type_t<decltype(gpio)>>(gpio));
  }

  auto inline static disable_ahb(gpio gpio) -> void
  {
    return detail::untyped_disable_ahb(static_cast<std::underlying_type_t<decltype(gpio)>>(gpio));
  }

  auto inline static enable_ahb(gpio gpio) -> void
  {
    return detail::untyped_enable_ahb(static_cast<std::underlying_type_t<decltype(gpio)>>(gpio));
  }

}  // namespace drinli::rom::system_control

#endif
