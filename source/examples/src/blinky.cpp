#include <platform/firmware.hpp>
#include <rom/system_control.hpp>

[[noreturn]] auto firmware_main() -> void
{
  using namespace drinli;

  rom::system_control::enable(rom::system_control::gpio::f);
  rom::system_control::enable_ahb(rom::system_control::gpio::f);

  while (true)
  {
    rom::system_control::sleep();
  }
}