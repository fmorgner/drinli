#ifndef DRINLI_ROM_DETAIL_API_CONSTANT_HPP
#define DRINLI_ROM_DETAIL_API_CONSTANT_HPP

#include <cstddef>
#include <cstdint>

namespace drinli::rom::detail
{

  template<typename ValueType, ValueType const * Variable>
  struct api_constant
  {
    operator ValueType() const noexcept
    {
      return *Variable;
    }
  };

}  // namespace drinli::rom::detail

#endif
