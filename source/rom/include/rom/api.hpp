#ifndef DRINLI_ROM_API_HPP
#define DRINLI_ROM_API_HPP

#include <rom/detail/api_constant.hpp>
#include <rom/detail/api_table.hpp>

namespace drinli::rom::api
{

  namespace tables
  {
    namespace detail
    {
      extern "C"
      {
        extern rom::detail::function_table const _rom_adc_table;
        extern rom::detail::function_table const _rom_can_table;
        extern rom::detail::function_table const _rom_comparator_table;
        extern rom::detail::function_table const _rom_eeprom_table;
        extern rom::detail::function_table const _rom_epi_table;
        extern rom::detail::function_table const _rom_ethernet_table;
        extern rom::detail::function_table const _rom_fan_table;
        extern rom::detail::function_table const _rom_flash_table;
        extern rom::detail::function_table const _rom_fpu_table;
        extern rom::detail::function_table const _rom_gpio_table;
        extern rom::detail::function_table const _rom_hibernate_table;
        extern rom::detail::function_table const _rom_i2c_table;
        extern rom::detail::function_table const _rom_i2s_table;
        extern rom::detail::function_table const _rom_interrupt_table;
        extern rom::detail::function_table const _rom_lpc_table;
        extern rom::detail::function_table const _rom_mpu_table;
        extern rom::detail::function_table const _rom_peci_table;
        extern rom::detail::function_table const _rom_pwm_table;
        extern rom::detail::function_table const _rom_qei_table;
        extern rom::detail::function_table const _rom_smbus_table;
        extern rom::detail::function_table const _rom_software_table;
        extern rom::detail::function_table const _rom_ssi_table;
        extern rom::detail::function_table const _rom_system_control_table;
        extern rom::detail::function_table const _rom_system_exception_table;
        extern rom::detail::function_table const _rom_systick_table;
        extern rom::detail::function_table const _rom_timer_table;
        extern rom::detail::function_table const _rom_uart_table;
        extern rom::detail::function_table const _rom_udma_table;
        extern rom::detail::function_table const _rom_usb_table;
        extern rom::detail::function_table const _rom_watchdog_table;
      }
    }  // namespace detail

    using adc = rom::detail::api_table<&detail::_rom_adc_table>;
    using can = rom::detail::api_table<&detail::_rom_can_table>;
    using comparator = rom::detail::api_table<&detail::_rom_comparator_table>;
    using eeprom = rom::detail::api_table<&detail::_rom_eeprom_table>;
    using epi = rom::detail::api_table<&detail::_rom_epi_table>;
    using ethernet = rom::detail::api_table<&detail::_rom_ethernet_table>;
    using fan = rom::detail::api_table<&detail::_rom_fan_table>;
    using flash = rom::detail::api_table<&detail::_rom_flash_table>;
    using fpu = rom::detail::api_table<&detail::_rom_fpu_table>;
    using gpio = rom::detail::api_table<&detail::_rom_gpio_table>;
    using hibernate = rom::detail::api_table<&detail::_rom_hibernate_table>;
    using i2c = rom::detail::api_table<&detail::_rom_i2c_table>;
    using i2s = rom::detail::api_table<&detail::_rom_i2s_table>;
    using interrupt = rom::detail::api_table<&detail::_rom_interrupt_table>;
    using lpc = rom::detail::api_table<&detail::_rom_lpc_table>;
    using mpu = rom::detail::api_table<&detail::_rom_mpu_table>;
    using peci = rom::detail::api_table<&detail::_rom_peci_table>;
    using pwm = rom::detail::api_table<&detail::_rom_pwm_table>;
    using qei = rom::detail::api_table<&detail::_rom_qei_table>;
    using smbus = rom::detail::api_table<&detail::_rom_smbus_table>;
    using software = rom::detail::api_table<&detail::_rom_software_table>;
    using ssi = rom::detail::api_table<&detail::_rom_ssi_table>;
    using system_control = rom::detail::api_table<&detail::_rom_system_control_table>;
    using system_exception = rom::detail::api_table<&detail::_rom_system_exception_table>;
    using systick = rom::detail::api_table<&detail::_rom_systick_table>;
    using timer = rom::detail::api_table<&detail::_rom_timer_table>;
    using uart = rom::detail::api_table<&detail::_rom_uart_table>;
    using udma = rom::detail::api_table<&detail::_rom_udma_table>;
    using usb = rom::detail::api_table<&detail::_rom_usb_table>;
    using watchdog = rom::detail::api_table<&detail::_rom_watchdog_table>;

  }  // namespace tables

  namespace constants
  {
    namespace detail
    {
      extern "C"
      {
        extern std::uint32_t const _rom_version;
      }
    }  // namespace detail

    /**
     * The version of the ROM in use
     */
    auto constexpr version = rom::detail::api_constant<std::uint32_t, &detail::_rom_version>{};

  }  // namespace constants

}  // namespace drinli::rom::api

#endif