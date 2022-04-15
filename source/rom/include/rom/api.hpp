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

    //! The Analog Digital Converter (ADC) function table
    using adc = rom::detail::api_table<&detail::_rom_adc_table>;
    //! The Controller Area Network (CAN) function table
    using can = rom::detail::api_table<&detail::_rom_can_table>;
    //! The Analog Comparator function table
    using comparator = rom::detail::api_table<&detail::_rom_comparator_table>;
    //! The Electrically Eraseable Programmable Read-Only Memory function table
    using eeprom = rom::detail::api_table<&detail::_rom_eeprom_table>;
    //! The External Peripheral Interface (EPI) function table
    using epi = rom::detail::api_table<&detail::_rom_epi_table>;
    //! The Ethernet controller function table
    using ethernet = rom::detail::api_table<&detail::_rom_ethernet_table>;
    //! The Fan controller function table
    using fan = rom::detail::api_table<&detail::_rom_fan_table>;
    //! The Flash Memory function table
    using flash = rom::detail::api_table<&detail::_rom_flash_table>;
    //! The Floating-Point Unit (FPU) function table
    using fpu = rom::detail::api_table<&detail::_rom_fpu_table>;
    //! The General Purpose Input/Output function table
    using gpio = rom::detail::api_table<&detail::_rom_gpio_table>;
    //! The Hibernation Module function table
    using hibernate = rom::detail::api_table<&detail::_rom_hibernate_table>;
    //! The Inter-Integrated Circuit controller function table
    using i2c = rom::detail::api_table<&detail::_rom_i2c_table>;
    //! The Inter-IC Sound controller function table
    using i2s = rom::detail::api_table<&detail::_rom_i2s_table>;
    //! The Interrupt controller function table
    using interrupt = rom::detail::api_table<&detail::_rom_interrupt_table>;
    //! The Low Pin-Count (LPC) interface function table
    using lpc = rom::detail::api_table<&detail::_rom_lpc_table>;
    //! The Memory Protection Unit (MPU) function table
    using mpu = rom::detail::api_table<&detail::_rom_mpu_table>;
    //! The Platform Environment Control Interface function table
    using peci = rom::detail::api_table<&detail::_rom_peci_table>;
    //! The Pulse-Width Modulation (PWM) controller function table
    using pwm = rom::detail::api_table<&detail::_rom_pwm_table>;
    //! The Quadrature Encoder Interface (QEI) function table
    using qei = rom::detail::api_table<&detail::_rom_qei_table>;
    //! The System Management Bus (SMBUS) controller function table
    using smbus = rom::detail::api_table<&detail::_rom_smbus_table>;
    //! The assorted Software function table
    using software = rom::detail::api_table<&detail::_rom_software_table>;
    //! The Synchronous Serial Interface (SSI) controller function table
    using ssi = rom::detail::api_table<&detail::_rom_ssi_table>;
    //! The System Control function table
    using system_control = rom::detail::api_table<&detail::_rom_system_control_table>;
    //! The System Exception management function table
    using system_exception = rom::detail::api_table<&detail::_rom_system_exception_table>;
    //! The System Tick function table
    using systick = rom::detail::api_table<&detail::_rom_systick_table>;
    //! The Timer controller function table
    using timer = rom::detail::api_table<&detail::_rom_timer_table>;
    //! The Universal Asynchronous Receiver/Transmitter controller function table
    using uart = rom::detail::api_table<&detail::_rom_uart_table>;
    //! The Micro Direct Memory Access (uDMA) controller function table
    using udma = rom::detail::api_table<&detail::_rom_udma_table>;
    //! The Universal Serial Bus (USB) controller function table
    using usb = rom::detail::api_table<&detail::_rom_usb_table>;
    //! The Watchdog timer controller function table
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
     * @brief The version of the ROM in use.
     */
    auto constexpr version = rom::detail::api_constant<std::uint32_t, &detail::_rom_version>{};

  }  // namespace constants

}  // namespace drinli::rom::api

#endif