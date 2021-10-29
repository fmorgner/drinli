#include "base/reset.hpp"

#include "base/entry.hpp"
#include "base/symbols.hpp"
#include "ti/rom/system_control.hpp"

#include <algorithm>
#include <span>

namespace base
{

  namespace
  {

    auto load_data_section() -> void
    {
      auto data_in_flash = std::span{&_data_start, &_data_end};
      auto target_in_ram = &_data_load_point;
      std::ranges::copy(data_in_flash, target_in_ram);
    }

    auto zero_bss_section() -> void
    {
      auto bss_in_ram = std::span{&_bss_start, &_bss_end};
      std::ranges::fill(bss_in_ram, 0);
    }

    auto invoke_initializers() -> void
    {
      auto preinit_array = std::span{&_preinit_array_start, &_preinit_array_end};
      std::ranges::for_each(preinit_array, [](auto initializer) { initializer(); });

      auto init_array = std::span{&_init_array_start, &_init_array_end};
      std::ranges::for_each(init_array, [](auto initializer) { initializer(); });
    }

  }  // namespace

  auto reset() -> void
  {
    load_data_section();
    zero_bss_section();
    invoke_initializers();
    firmware_main();
    ti::rom::system_control::sleep();
  }

}  // namespace base