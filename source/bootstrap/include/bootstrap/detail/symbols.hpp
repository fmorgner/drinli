#ifndef DRINLI_BASE_SYMBOLS_HPP
#define DRINLI_BASE_SYMBOLS_HPP

#include <cstddef>
#include <cstdint>

namespace drinli::bootstrap::detail
{

  using initializer_function_type = void (*)();

  extern "C"
  {
    /**
     * Setinel representing the start of the .data section in flash memory.
     */
    extern std::uint32_t _data_start;

    /**
     * Setinel representing the end of the .data section in flash memory.
     */
    extern std::uint32_t _data_end;

    /**
     * Sentinel representing the position in RAM where to load the contents of the .data section to.
     */
    extern std::uint32_t _data_load_point;

    /**
     * Setinel representing the start of the .bss section in RAM.
     */
    extern std::uint32_t _bss_start;

    /**
     * Setinel representing the end of the .bss section in RAM.
     */
    extern std::uint32_t _bss_end;

    /**
     * Setinel representing the start of the initial system stack in RAM.
     */
    extern std::byte _initial_stack_end;

    /**
     * Sentinel representing the start of the initial system heap in RAM.
     */
    extern std::uint32_t _heap_start;

    /**
     * Sentinel representing the start of the pre-init array
     */
    extern detail::initializer_function_type _preinit_array_start;

    /**
     * Sentinel representing the end of the pre-init array
     */
    extern detail::initializer_function_type _preinit_array_end;

    /**
     * Sentinel representing the start of the init array
     */
    extern detail::initializer_function_type _init_array_start;

    /**
     * Sentinel representing the end of the init array
     */
    extern detail::initializer_function_type _init_array_end;
  }

}  // namespace drinli::bootstrap::detail

#endif