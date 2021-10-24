#ifndef DRINLI_TI_ROM_API_TABLE_HPP
#define DRINLI_TI_ROM_API_TABLE_HPP

#include <cstddef>
#include <cstdint>

namespace ti::rom
{

  template<typename FunctionType, std::size_t Table, std::size_t Function>
  auto function() -> FunctionType *
  {
    return reinterpret_cast<FunctionType *>(                       //
        reinterpret_cast<std::uint32_t *>(                         //
            reinterpret_cast<std::uint32_t *>(0x0100'0010)[Table]  //
            )[Function]                                            //
    );
  }

}  // namespace ti::rom

#endif