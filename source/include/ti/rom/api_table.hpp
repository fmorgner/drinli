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

      template<typename... Arguments>
      auto static invoke(Arguments &&... arguments) -> auto
      {
        return reinterpret_cast<Signature *>(                                  //
            reinterpret_cast<std::uint32_t *>(                                 //
                reinterpret_cast<std::uint32_t *>(base_address::value)[Table]  //
                )[Function])(static_cast<ArgumentTypes>(arguments)...);
      }
    };
  };

}  // namespace ti::rom

#endif