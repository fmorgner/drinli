#ifndef DRINLI_MCU_GPIO_HPP
#define DRINLI_MCU_GPIO_HPP

#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace drinli::mcu::gpio
{

  /**
   * @brief GPIO port on the AHB
   */
  enum struct apb_port : std::uint32_t
  {
    a = 0x4000'4000,  ///< Port A
    b = 0x4000'5000,  ///< Port B
    c = 0x4000'6000,  ///< Port C
    d = 0x4000'7000,  ///< Port D
    e = 0x4002'4000,  ///< Port E
    f = 0x4002'5000,  ///< Port F
  };

  /**
   * @brief GPIO port on the AHB
   */
  enum struct ahb_port : std::uint32_t
  {
    a = 0x4005'8000,  ///< Port A
    b = 0x4005'9000,  ///< Port B
    c = 0x4005'A000,  ///< Port C
    d = 0x4005'B000,  ///< Port D
    e = 0x4005'C000,  ///< Port E
    f = 0x4005'D000,  ///< Port F
  };

  /**
   * @brief Configured mode of a pin
   *
   * Each pin on a GPIO peripheral can be in one of these modes. In order to be used by an alternative HW module, a pin
   * must be configured to be in 'hardware controlled' (pin_mode::hw) mode.
   */
  enum struct pin_mode : std::uint32_t
  {
    in = 0x0000'0000,   ///< software controlled input
    out = 0x0000'0001,  ///< software controlled output
    hw = 0x0000'0002,   ///< hardware controlled
  };

  enum struct pad_drive_strength : std::uint32_t
  {
    _2mA = 0x0000'0001,                    ///< maximum 2mA
    _4mA = 0x0000'0002,                    ///< maximum 4mA
    _8mA = 0x0000'0004,                    ///< maximum 8mA
    _8mA_with_slew_control = 0x0000'000C,  ///< maximum 8mA with additional rise and fall slew-rate control
  };

  enum struct pad_drive_mode : std::uint32_t
  {
    analog_comparator = 0x0000'0000,
    push_pull = 0x0000'0008,
    open_drain = 0x0000'0009,
    push_pull_with_weak_pull_up = 0x0000'000A,
    open_drain_with_weak_pull_up = 0x0000'000B,
    push_pull_with_weak_pull_down = 0x0000'000C,
    open_drain_with_weak_pull_down = 0x0000'000D,
  };

}  // namespace drinli::mcu::gpio

#endif
