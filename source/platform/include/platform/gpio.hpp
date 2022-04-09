#ifndef DRINLI_PLATFORM_GPIO_HPP
#define DRINLI_PLATFORM_GPIO_HPP

// #include "mcu/gpio.hpp"
// #include "rom/gpio.hpp"

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <numeric>
#include <type_traits>

namespace drinli::platform::gpio
{

  enum struct port : std::uint8_t
  {
    a,
    b,
    c,
    d,
    e,
    f,
  };

  /**
   * @brief A GPIO pin
   */
  enum struct pin : std::uint8_t
  {
    _0,  ///< Pin 0
    _1,  ///< Pin 1
    _2,  ///< Pin 2
    _3,  ///< Pin 3
    _4,  ///< Pin 4
    _5,  ///< Pin 5
    _6,  ///< Pin 6
    _7,  ///< Pin 7
  };

  /**
   * @brief Configured mode of a pin
   *
   * Each pin on a GPIO peripheral can be in one of these modes. In order to be used by an alternative HW module, a pin
   * must be configured to be in 'hardware controlled' (pin_mode::hw) mode.
   */
  enum struct pin_mode : std::uint8_t
  {
    input,                ///< software controlled input
    output,               ///< software controlled output
    hardware_controlled,  ///< hardware controlled
  };

  enum struct drive_strength : std::uint32_t
  {
    low,                   ///< maximum 2mA
    medium,                ///< maximum 4mA
    high,                  ///< maximum 8mA
    slew_controlled_high,  ///< maximum 8mA with additional rise and fall slew-rate control
  };

  /**
   * @brief A set of pins
   */
  struct pin_set
  {
    explicit constexpr pin_set(pin pin)
        : m_pins{static_cast<std::underlying_type_t<decltype(pin)>>(pin)}
    {
    }

    constexpr pin_set(std::initializer_list<pin> pins)
        : m_pins{
              std::accumulate(cbegin(pins), cend(pins), static_cast<std::underlying_type_t<pin>>(0), [](auto init, auto pin) {
                return init | static_cast<std::underlying_type_t<decltype(pin)>>(pin);
              })}
    {
    }

    auto constexpr operator|(pin pin) const noexcept -> pin_set
    {
      return {m_pins, pin};
    }

    auto constexpr operator|(pin_set other) const noexcept -> pin_set
    {
      return pin_set(m_pins | other.m_pins);
    }

    auto constexpr operator|(pin pin) noexcept -> pin_set &
    {
      m_pins |= static_cast<std::underlying_type_t<decltype(pin)>>(pin);
      return *this;
    }

    auto constexpr operator|(pin_set other) noexcept -> pin_set &
    {
      m_pins |= other.m_pins;
      return *this;
    }

    auto constexpr operator&(pin pin) const noexcept -> bool
    {
      return contains(pin);
    }

    explicit constexpr operator std::underlying_type_t<pin>() const noexcept
    {
      return m_pins;
    }

    template<pin Pin>
    auto constexpr contains() const noexcept -> bool
    {
      return contains(Pin);
    }

    auto constexpr contains(pin pin) const noexcept -> bool
    {
      return m_pins & static_cast<std::underlying_type_t<decltype(pin)>>(pin);
    }

  private:
    constexpr pin_set(std::underlying_type_t<pin> current, pin pin) noexcept
        : m_pins(current | static_cast<std::underlying_type_t<decltype(pin)>>(pin))
    {
    }

    explicit constexpr pin_set(std::underlying_type_t<pin> pins)
        : m_pins{pins}
    {
    }

    std::underlying_type_t<pin> m_pins{};
  };

  auto constexpr operator|(pin lhs, pin rhs) -> pin_set
  {
    return {lhs, rhs};
  }

  struct pin_configuration
  {
    pin_mode mode;
    drive_strength strength;
  };

  auto configure(port port, pin_set pins, pin_configuration configuration) -> void;

}  // namespace drinli::platform::gpio

#endif