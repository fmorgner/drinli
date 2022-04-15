#include <platform/firmware.hpp>
#include <rom/gpio.hpp>
#include <rom/system_control.hpp>

auto constexpr red_led = 0b0000'0010;
auto constexpr blue_led = 0b0000'0100;
auto constexpr green_led = 0b0000'1000;

auto constexpr all_leds = red_led | blue_led | green_led;

[[noreturn]] auto firmware_main() -> void
{
  using namespace drinli;

  rom::system_control::enable(rom::system_control::gpio::f);
  rom::system_control::enable_ahb(rom::system_control::gpio::f);

  rom::gpio::set_mode(0x4005'D000, all_leds, rom::gpio::pin_mode::output);
  rom::gpio::set_pad_configuration(0x4005'D000,
                                   all_leds,
                                   rom::gpio::drive_strength::basic_2mA,
                                   rom::gpio::pin_type::push_pull_with_weak_pull_down);

  rom::gpio::write(0x4005'D000, all_leds, true);

  while (true)
  {
    rom::system_control::sleep();
  }
}
