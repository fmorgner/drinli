#ifndef DRINLI_ROM_DETAIL_API_TABLE_HPP
#define DRINLI_ROM_DETAIL_API_TABLE_HPP

#include <cstddef>
#include <cstdint>

namespace drinli::rom::detail
{

  using function_table_element = void (*)();
  using function_table = function_table_element[];
  using function_table_pointer = function_table const *;

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

}  // namespace drinli::rom::detail

#endif
