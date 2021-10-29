#include "bootstrap/detail/startup.hpp"

#include "bootstrap/detail/symbols.hpp"

#include <algorithm>
#include <span>

auto firmware_main() -> void;

namespace drinli::bootstrap::detail
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

  auto start() noexcept -> void
  {
    load_data_section();
    zero_bss_section();
    invoke_initializers();
    firmware_main();
  }

}  // namespace drinli::bootstrap::detail