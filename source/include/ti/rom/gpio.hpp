#ifndef DRINLI_TI_ROM_GPIO_HPP
#define DRINLI_TI_ROM_GPIO_HPP

#include "ti/rom/api_table.hpp"

#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace ti::rom::gpio
{

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

  auto constexpr operator|(pin lhs, pin rhs) -> pin_set
  {
    return {lhs, rhs};
  }

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

  auto inline set_mode(port port, pin_set pins, mode mode) -> void
  {
    using RomFunctionType = void(std::uint32_t port_address, std::uint8_t pin_mask, std::uint32_t io_mode);

    return function<RomFunctionType, 4, 1>()(  //
        static_cast<std::uint32_t>(port),      //
        static_cast<std::uint8_t>(pins),       //
        static_cast<std::uint32_t>(mode)       //
    );
  }

  auto inline set_mode(port port, pin pin, mode mode) -> void
  {
    return set_mode(port, static_cast<pin_set>(pin), mode);
  }

  auto inline set_pad_configuration(port port, pin_set pins, strength strength, type type) -> void
  {
    using RomFunctionType = void(std::uint32_t port_address, std::uint8_t pin_mask, std::uint32_t strength, std::uint32_t type);

    return function<RomFunctionType, 4, 5>()(  //
        static_cast<std::uint32_t>(port),      //
        static_cast<std::uint8_t>(pins),       //
        static_cast<std::uint32_t>(strength),  //
        static_cast<std::uint32_t>(type)       //
    );
  }

  auto inline set_pad_configuration(port port, pin pin, strength strength, type type) -> void
  {
    return set_pad_configuration(port, static_cast<pin_set>(pin), strength, type);
  }

  auto inline enable_output(port port, pin_set pins) -> void
  {
    using RomFunctionType = void(std::uint32_t * port_address, std::uint8_t pin_mask);

    return function<RomFunctionType, 4, 15>()(    //
        reinterpret_cast<std::uint32_t *>(port),  //
        static_cast<std::uint8_t>(pins)           //
    );
  }

  auto inline enable_output(port port, pin pin) -> void
  {
    return enable_output(port, static_cast<pin_set>(pin));
  }

  auto inline write(port port, pin_set pins, level level) -> void
  {
    using RomFunctionType = void(std::uint32_t port_address, std::uint8_t pin_mask, std::uint8_t value);

    auto const base_levels = level == level::low ? 0x00 : 0xff;
    auto const levels = base_levels & static_cast<std::uint8_t>(pins);

    return function<RomFunctionType, 4, 0>()(  //
        static_cast<std::uint32_t>(port),      //
        static_cast<std::uint8_t>(pins),       //
        levels);                               //
  }

  auto inline write(port port, pin pin, level level) -> void
  {
    return write(port, static_cast<pin_set>(pin), level);
  }

}  // namespace ti::rom::gpio

#endif