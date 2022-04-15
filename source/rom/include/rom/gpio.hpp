#ifndef DRINLI_ROM_GPIO_HPP
#define DRINLI_ROM_GPIO_HPP

#include "rom/api.hpp"

#include <cstdint>

namespace drinli::rom::gpio
{

  namespace detail
  {
    auto inline static untyped_write(std::uint32_t port, std::uint8_t pins, std::uint8_t value) -> void
    {
      return api::tables::gpio::function<0, decltype(untyped_write)>::invoke(port, pins, value);
    }
  }  // namespace detail

  enum struct drive_strength : std::uint32_t
  {
    basic_2mA = 0x0000'0001,
    basic_4mA = 0x0000'0002,
    basic_8mA = 0x0000'0004,
    slew_rate_controlled_8mA = 0x0000'000C,
  };

  enum struct pin_mode : std::uint32_t
  {
    input = 0x0000'0000,
    output = 0x0000'0001,
    peripheral = 0x0000'0002,
  };

  enum struct pin_type : std::uint32_t
  {
    analog_comparator = 0x0000'0000,
    push_pull = 0x0000'0008,
    push_pull_with_weak_pull_up = 0x0000'000A,
    push_pull_with_weak_pull_down = 0x0000'000C,
    open_drain = 0x0000'0009,
    open_drain_with_weak_pull_up = 0x0000'000B,
    open_drain_with_weak_pull_down = 0x0000'000D,
  };

  /**
   * @brief Set the mode of the given pins in the give port
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   * @param mode The target mode of the `pins` on `port`
   */
  auto inline static set_mode(std::uint32_t port, std::uint8_t pins, pin_mode mode) -> void
  {
    return api::tables::gpio::function<1, decltype(set_mode)>::invoke(port, pins, mode);
  }

  /**
   * @brief Set the configuration of the desired GPIO pad.
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   * @param strength The desired drive strength
   * @param type The desired drive type
   */
  auto inline static set_pad_configuration(std::uint32_t port, std::uint8_t pins, drive_strength strength, pin_type type)
      -> void
  {
    return api::tables::gpio::function<5, decltype(set_pad_configuration)>::invoke(port, pins, strength, type);
  }

  /**
   * @brief Enable the desired pins to be outputs
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   */
  auto inline static enable_output(std::uint32_t port, std::uint8_t pins) -> void
  {
    return api::tables::gpio::function<15, decltype(enable_output)>::invoke(port, pins);
  }

  /**
   * @brief Write the state of the desired pins
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   * @param value The value to apply to the pins
   */
  [[gnu::noinline]] auto inline static write(std::uint32_t port, std::uint8_t pins, bool value) -> void
  {
    return detail::untyped_write(port, pins, (value ? 0xff : 0x00) & pins);
  }

}  // namespace drinli::rom::gpio

#endif
