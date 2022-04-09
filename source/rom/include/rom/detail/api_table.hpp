#ifndef DRINLI_ROM_DETAIL_API_TABLE_HPP
#define DRINLI_ROM_DETAIL_API_TABLE_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace drinli::rom
{

  namespace detail
  {
    extern "C" std::uint32_t const _rom_version;

    template<typename ValueType, ValueType const * Variable>
    struct api_constant
    {
      operator ValueType() const noexcept
      {
        return *Variable;
      }
    };

    using function_table_element = void (*)();
    using function_table = function_table_element[];
    using function_table_pointer = function_table const *;

    extern "C" function_table const _rom_gpio_table;
    extern "C" function_table const _rom_system_control_table;

    template<function_table_pointer Table>
    struct api_table
    {
      template<std::size_t Function, typename Signature>
      struct function;

      template<std::size_t Function, typename ReturnType, typename... ArgumentTypes>
      struct function<Function, ReturnType(ArgumentTypes...)>
      {
        using Signature = ReturnType(ArgumentTypes...);

        auto inline static table_pointer() -> Signature ** const *
        {
          return reinterpret_cast<Signature ** const *>(Table);
        }

        auto inline static function_pointer() -> Signature *
        {
          return reinterpret_cast<Signature *>((*table_pointer())[Function]);
        }

        template<typename... Arguments>
        auto static invoke(Arguments &&... arguments) -> auto
        {
          return function_pointer()(static_cast<ArgumentTypes>(arguments)...);
        }
      };
    };
  }  // namespace detail

  using gpio_api_table = detail::api_table<&detail::_rom_gpio_table>;
  using system_control_api_table = detail::api_table<&detail::_rom_system_control_table>;

  /**
   * The version of the ROM in use
   */
  auto constexpr version = detail::api_constant<std::uint32_t, &detail::_rom_version>{};

}  // namespace drinli::rom

#endif
