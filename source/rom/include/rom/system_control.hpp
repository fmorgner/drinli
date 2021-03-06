#ifndef DRINLI_ROM_SYSTEM_CONTROL_HPP
#define DRINLI_ROM_SYSTEM_CONTROL_HPP

#include "rom/api.hpp"
#include "support/type_list.hpp"

#include <cstdint>
#include <type_traits>

namespace drinli::rom::system_control
{
  enum struct analog : std::uint32_t;
  enum struct gpio : std::uint32_t;
  enum struct timer : std::uint32_t;

  namespace detail
  {

    auto inline static untyped_enable(uint32_t peripheral) -> void
    {
      return api::tables::system_control::function<6, decltype(untyped_enable)>::invoke(peripheral);
    }

    auto inline static untyped_disable_ahb(uint32_t peripheral) -> void
    {
      return api::tables::system_control::function<30, decltype(untyped_disable_ahb)>::invoke(peripheral);
    }

    auto inline static untyped_enable_ahb(uint32_t peripheral) -> void
    {
      return api::tables::system_control::function<29, decltype(untyped_enable_ahb)>::invoke(peripheral);
    }

    template<typename Candidate>
    auto constexpr is_peripheral_type() -> bool
    {
      using support::type_list, support::type_v;
      // clang-format off
      return type_list{
          type_v<analog>,
          type_v<gpio>,
          type_v<timer>,
      }.contains(type_v<Candidate>);
      // clang-format on
    }

  }  // namespace detail

  /**
   * @brief Analog peripherals.
   */
  enum struct analog : std::uint32_t
  {
    analog_digital_converter_0 = 0x0010'0001,
    analog_digital_converter_1 = 0x0010'0002,
    comparator_0 = 0x1010'0100,
    comparator_1 = 0x1010'0200,
    comparator_2 = 0x1010'0400,
  };

  /**
   * @brief General Purpose Input/Output (GPIO) port peripherals.
   */
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

  /**
   * @brief Timer peripherals.
   */
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

  /**
   * @brief Determine whether a given type is a "peripheral" enumerator.
   *
   * @tparam EnumType The type to check
   */
  template<typename EnumType>
  concept peripheral = std::is_enum_v<EnumType> && detail::is_peripheral_type<EnumType>();

  /**
   * @brief Put the processor in sleep mode.
   *
   * This function will not return until the processor returns to run mode. If automatic clock gating is enabled, only
   * designated peripherals continue to operate and can wake up the processor. Otherwise, all peripherals continue to operate.
   *
   * @see enable_in_sleep_mode and enable_peripheral_clock_gating.
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
   * @warning This function will never return.
   */
  [[noreturn]] auto inline static reset() -> void
  {
    api::tables::system_control::function<19, decltype(reset)>::invoke();
    DRINLI_UNREACHABLE();
  }

  /**
   * @brief Enable a processor peripheral.
   *
   * After a reset of the processor (including initial startup), all periph=erals are disabled. This function allows for any
   * given peripheral to be enabled. After being enabled, read and write operations can be perfomed on the given peripheral.
   *
   * @warning Enabling a peripheral takes 5 clock cycles. Any access to the peripheral during that time will raise a Bus Fault
   * exception. Care must be taken to ensure no such access occurs during this period.
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
   * General Purpose Input/Output (GPIO) peripherals can be accessed via either the Advanced Periphal Bus (APB) or the Advanced
   * High-Performance Bus (AHB). This function disables access to the given GPIO peripheral via the AHB.
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
   * General Purpose Input/Output (GPIO) peripherals can be accessed via either the Advanced Periphal Bus (APB) or the Advanced
   * High-Performance Bus (AHB). This function enables access to the given GPIO peripheral via the AHB.
   *
   * @param[in] peripheral The GPIO peripheral to enable AHB access for
   */
  auto inline static enable_ahb(gpio peripheral) -> void
  {
    return detail::untyped_enable_ahb(static_cast<std::underlying_type_t<decltype(peripheral)>>(peripheral));
  }

  /**
   * @brief Enable or disable sleep mode clock gating for peripherals.
   *
   * By default, sleep mode clock gating is disabled for all peripherals. Thus all peripherals remain clocked when the processor
   * enters its sleep mode. This function allows for clock gating to be enabled or disabled.
   *
   * @param[in] yes_or_no Whether or not to enable clock gating for peripherals in sleep mode.
   */
  auto inline static enable_peripheral_clock_gating(bool yes_or_no) -> void
  {
    return api::tables::system_control::function<12, decltype(enable_peripheral_clock_gating)>::invoke(yes_or_no);
  }

}  // namespace drinli::rom::system_control

#endif
