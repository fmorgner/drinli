#ifndef DRINLI_ROM_GPIO_HPP
#define DRINLI_ROM_GPIO_HPP

#include "mcu/gpio.hpp"
#include "rom/detail/api_table.hpp"

#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <type_traits>

namespace drinli::rom::gpio
{

  /**
   * @brief Set the mode of the given pins in the give port
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   * @param mode The target mode of the `pins` on `port`
   */
  auto inline static set_mode(std::uint32_t port, std::uint8_t pins, std::uint32_t mode) -> void
  {
    return gpio_api_table::function<1, decltype(set_mode)>::invoke(port, pins, mode);
  }

  /**
   * @brief Set the configuration of the desired GPIO pad
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   * @param strength The desired drive strength
   * @param type The desired drive type
   */
  auto inline static set_pad_configuration(std::uint32_t port, std::uint8_t pins, std::uint32_t strength, std::uint32_t type)
      -> void
  {
    return gpio_api_table::function<5, decltype(set_pad_configuration)>::invoke(port, pins, strength, type);
  }

  /**
   * @brief Enable the desired pins to be outputs
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   */
  auto inline static enable_output(std::uint32_t port, std::uint8_t pins) -> void
  {
    return gpio_api_table::function<15, decltype(enable_output)>::invoke(port, pins);
  }

  /**
   * @brief Write the state of the desired pins
   *
   * @param port A GPIO port
   * @param pins A set of pins on the `port`
   * @param value The value to apply to the pins
   */
  auto inline static write(std::uint32_t port, std::uint8_t pins, std::uint8_t value) -> void
  {
    return gpio_api_table::function<0, decltype(write)>::invoke(port, pins, value);
  }

}  // namespace drinli::rom::gpio

#endif
