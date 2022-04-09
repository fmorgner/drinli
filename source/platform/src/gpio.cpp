#include "platform/gpio.hpp"

#include "mcu/gpio.hpp"
#include "rom/gpio.hpp"
#include "rom/system_control.hpp"

namespace drinli::platform::gpio
{

  namespace detail
  {

  }

  // auto configure(port port, pin_set pins, pin_configuration configuration) -> void
  // {
  //   // rom::system_control::enable()
  //   // auto [mode, strength] = configuration;
  // }

  // namespace detail
  // {

  // }

  // auto enable(port port) noexcept -> void
  // {
  //   static_cast<void>(port);
  // }

  // auto ready(port port) noexcept -> bool
  // {
  //   static_cast<void>(port);
  //   return false;
  // }

}  // namespace drinli::platform::gpio