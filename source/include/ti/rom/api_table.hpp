#ifndef DRINLI_TI_ROM_API_TABLE_HPP
#define DRINLI_TI_ROM_API_TABLE_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace ti::rom
{

  template<std::size_t Table>
  struct api_table
  {
    using base_address = std::integral_constant<std::uint32_t, 0x0100'0010>;

    template<std::size_t Function, typename Signature>
    struct function;

    template<std::size_t Function, typename ReturnType, typename... ArgumentTypes>
    struct function<Function, ReturnType(ArgumentTypes...)>
    {
      using Signature = ReturnType(ArgumentTypes...);

      auto inline static table_pointer() -> Signature **
      {
        return reinterpret_cast<Signature ***>(base_address::value)[Table];
      }

      auto inline static function_pointer() -> Signature *
      {
        return reinterpret_cast<Signature *>(table_pointer()[Function]);
      }

      template<typename... Arguments>
      auto static invoke(Arguments &&... arguments) -> auto
      {
        return function_pointer()(static_cast<ArgumentTypes>(arguments)...);
      }
    };
  };

  /**
   * @brief Retrieve the version of the ROM in use
   *
   * @return std::uint32_t The version of the on-chip ROM
   */
  auto inline static version() -> std::uint32_t
  {
    return *reinterpret_cast<std::uint32_t *>(api_table<0>::base_address::value);
  }

}  // namespace ti::rom

#endif