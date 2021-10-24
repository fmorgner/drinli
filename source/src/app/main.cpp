#include <base/entry.hpp>
#include <ti/rom/gpio.hpp>
#include <ti/rom/system_control.hpp>

namespace gpio = ti::rom::gpio;
namespace sysctl = ti::rom::system_control;

auto constexpr red_led = gpio::pin::_1;
auto constexpr blue_led = gpio::pin::_2;
auto constexpr green_led = gpio::pin::_3;

auto constexpr all_leds = gpio::pin_set{
    red_led,
    blue_led,
    green_led,
};

auto firmware_main() -> void
{
  sysctl::enable(sysctl::peripheral::gpio_f);

  set_mode(gpio::port::f, all_leds, gpio::mode::out);
  set_pad_configuration(gpio::port::f, all_leds, gpio::strength::_2mA, gpio::type::push_pull_with_weak_pull_down);

  write(gpio::port::f, red_led, gpio::level::high);
}