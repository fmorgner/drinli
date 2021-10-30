#ifndef DRINLI_ROM_GPIO_HPP
#define DRINLI_ROM_GPIO_HPP

#include "mcu/gpio.hpp"
#include "rom/detail/api_table.hpp"

#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace drinli::rom
{

  struct gpio
  {
    using table = detail::api_table<4>;
    using pin = mcu::gpio::pin;
    using port = mcu::gpio::ahb_port;
    using mode = mcu::gpio::pin_mode;

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

    enum struct level : bool
    {
      low = false,
      high = true,
    };

    enum struct strength : std::uint32_t
    {
      _2mA = 0x0000'0001,
      _4mA = 0x0000'0002,
      _8mA = 0x0000'0004,
      _8mA_with_slew_control = 0x0000'000C,
    };

    enum struct type : std::uint32_t
    {
      analog_comparator = 0x0000'0000,
      push_pull = 0x0000'0008,
      open_drain = 0x0000'0009,
      push_pull_with_weak_pull_up = 0x0000'000A,
      open_drain_with_weak_pull_up = 0x0000'000B,
      push_pull_with_weak_pull_down = 0x0000'000C,
      open_drain_with_weak_pull_down = 0x0000'000D,
    };

    /**
     * @brief Set the mode of the given pins in the give port
     *
     * @param port A GPIO port
     * @param pins A set of pins on the `port`
     * @param mode The target mode of the `pins` on `port`
     */
    auto inline static set_mode(port port, pin_set pins, mode mode) -> void
    {
      using function = table::function<1, void(std::uint32_t, std::uint8_t, std::uint32_t)>;
      return function::invoke(port, pins, mode);
    }

    auto inline static set_mode(port port, pin pin, mode mode) -> void
    {
      return set_mode(port, static_cast<pin_set>(pin), mode);
    }

    auto inline static set_pad_configuration(port port, pin_set pins, strength strength, type type) -> void
    {
      using function = table::function<5, void(std::uint32_t, std::uint8_t, std::uint32_t, std::uint32_t)>;
      return function::invoke(port, pins, strength, type);
    }

    auto inline static set_pad_configuration(port port, pin pin, strength strength, type type) -> void
    {
      return set_pad_configuration(port, static_cast<pin_set>(pin), strength, type);
    }

    auto inline static enable_output(port port, pin_set pins) -> void
    {
      using function = table::function<15, void(std::uint32_t, std::uint8_t)>;
      return function::invoke(port, pins);
    }

    auto inline static enable_output(port port, pin pin) -> void
    {
      return enable_output(port, static_cast<pin_set>(pin));
    }

    auto inline static write(port port, pin_set pins, level level) -> void
    {
      using function = table::function<0, void(std::uint32_t, std::uint8_t, std::uint8_t)>;

      auto const base_levels = level == level::low ? 0x00 : 0xff;
      auto const levels = base_levels & static_cast<std::uint8_t>(pins);

      return function::invoke(port, pins, levels);
    }

    auto inline static write(port port, pin pin, level level) -> void
    {
      return write(port, static_cast<pin_set>(pin), level);
    }
  };

  auto constexpr operator|(gpio::pin lhs, gpio::pin rhs) -> gpio::pin_set
  {
    return {lhs, rhs};
  }

}  // namespace drinli::rom

#endif