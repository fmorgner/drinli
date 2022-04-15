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

  enum struct analog : std::uint32_t
  {
    analog_digital_converter_0 = 0x0010'0001,
    analog_digital_converter_1 = 0x0010'0002,
    comparator_0 = 0x1010'0100,
    comparator_1 = 0x1010'0200,
    comparator_2 = 0x1010'0400,
  };

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
  };

  enum struct timer : std::uint32_t
  {
    watchdog_0 = 0x0000'0008,
    watchdog_1 = 0x0010'1000,
    basic_0 = 0x1010'0001,
    basic_1 = 0x1010'0002,
    basic_2 = 0x1010'0004,
    basic_3 = 0x1010'0008,
    basic_4 = 0xf000'0404,
    basic_5 = 0xf000'0405,
    wide_0 = 0xf000'5c00,
    wide_1 = 0xf000'5c01,
    wide_2 = 0xf000'5c02,
    wide_3 = 0xf000'5c03,
    wide_4 = 0xf000'5c04,
    wide_5 = 0xf000'5c05,
  };

  // clang-format off
  template<typename EnumType>
  concept peripheral = std::is_enum_v<EnumType> &&
                       std::disjunction_v<
                         std::is_same<analog, EnumType>,
                         std::is_same<gpio, EnumType>,
                         std::is_same<timer, EnumType>
                       >;
  // clang-format on

  /**
   * @brief Put the processor in sleep mode.
   *
   * This function will not return until the processor returns to run mode. If automatic clock gating is enabled, only
   * designated peripherals continue to operate and can wake up the processor. Otherwise, all peripherals continue to operate.
   *
   * @see system_control::enable_in_sleep_mode and system_control::enable_clock_gating.
   */
  auto inline static sleep() -> void
  {
    return api::tables::system_control::function<0, decltype(sleep)>::invoke();
  }

  /**
   * @brief Reset the device.
   *
   * The processor and all of its peripherals are reset. All device registers (except the Reset Cause (RESC) will be restored to
   * their reset values. In addition to its original value, the Reset Cause (RESC) register will have the Software Reset (SW)
   * bit set.
   *
   * @warn This function will never return.
   */
  {
    return api::tables::system_control::function<19, decltype(reset)>::invoke();
  }

  /**
   * @brief Enable a processor peripheral.
   *
   * @param[in] peripheral The peripheral that shall be enabled.
   */
  auto inline static enable(peripheral auto peripheral) -> void
  {
    return detail::untyped_enable(static_cast<std::underlying_type_t<decltype(peripheral)>>(peripheral));
  }

  /**
   * @brief Disable General Purpose Input/Output (GPIO) access via the Advanced High-Performance Bus (AHB).
   *
   * @param[in] peripheral The GPIO peripheral to disable AHB access for
   */
  auto inline static disable_ahb(gpio peripheral) -> void
  {
    return detail::untyped_disable_ahb(static_cast<std::underlying_type_t<decltype(peripheral)>>(peripheral));
  }

  /**
   * @brief Enable General Purpose Input/Output (GPIO) access via the Advanced High-Performance Bus (AHB).
   *
   * @param[in] peripheral The GPIO peripheral to enable AHB access for
   */
  auto inline static enable_ahb(gpio peripheral) -> void
  {
    return detail::untyped_enable_ahb(static_cast<std::underlying_type_t<decltype(peripheral)>>(peripheral));
  }

}  // namespace drinli::rom::system_control

#endif
