#ifndef DRINLI_TI_ROM_GPIO_HPP
#define DRINLI_TI_ROM_GPIO_HPP

#include "ti/rom/api_table.hpp"

#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace ti::rom
{

  struct gpio
  {
    using table = api_table<4>;

    /**
     * @brief Configured mode of a pin
     */
    enum struct mode : std::uint32_t
    {
      in = 0x0000'0000,   ///< software controlled input
      out = 0x0000'0001,  ///< software controlled output
      hw = 0x0000'0002,   ///< hardware controlled
    };

    /**
     * @brief GPIO port
     */
    enum struct port : std::uint32_t
    {
      a = 0x4005'8000,  ///< Port A
      b = 0x4005'9000,  ///< Port B
      c = 0x4005'A000,  ///< Port C
      d = 0x4005'B000,  ///< Port D
      e = 0x4005'C000,  ///< Port E
      f = 0x4002'5000,  ///< Port F
    };

    /**
     * @brief GPIO pin
     */
    enum struct pin : std::uint8_t
    {
      _0 = 0b0000'0001,  ///< Pin 0
      _1 = 0b0000'0010,  ///< Pin 1
      _2 = 0b0000'0100,  ///< Pin 2
      _3 = 0b0000'1000,  ///< Pin 3
      _4 = 0b0001'0000,  ///< Pin 4
      _5 = 0b0010'0000,  ///< Pin 5
      _6 = 0b0100'0000,  ///< Pin 6
      _7 = 0b1000'0000,  ///< Pin 7
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
        return pin_set{m_pins | other.m_pins};
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
          : m_pins{current | static_cast<std::underlying_type_t<decltype(pin)>>(pin)}
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

}  // namespace ti::rom

#endif