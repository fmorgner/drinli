// #include <rom/gpio.hpp>
// #include <platform/gpio.hpp>
#include <rom/system_control.hpp>

// using gpio = drinli::rom::gpio;
// using sysctl = drinli::rom::system_control;

// auto constexpr red_led = gpio::pin::_1;
// auto constexpr blue_led = gpio::pin::_2;
// auto constexpr green_led = gpio::pin::_3;

// auto constexpr all_leds = gpio::pin_set{
//     red_led,
//     blue_led,
//     green_led,
// };

// auto firmware_main() -> void
// {
//   sysctl::enable(sysctl::peripheral::gpio_f);
//   sysctl::enable_ahb(sysctl::peripheral::gpio_f);

//   gpio::set_mode(gpio::port::f, all_leds, gpio::mode::out);
//   gpio::set_pad_configuration(gpio::port::f, all_leds, gpio::strength::_2mA, gpio::type::push_pull_with_weak_pull_down);

//   gpio::write(gpio::port::f, all_leds, gpio::level::high);
// }

[[gnu::noreturn]] auto firmware_main() -> void
{
  using namespace drinli;

  rom::system_control::enable(0x2000'0020);
  rom::system_control::enable_gpio_ahb(0x2000'0020);

  while (true)
  {
    rom::system_control::sleep();
  }

  __builtin_unreachable();
}