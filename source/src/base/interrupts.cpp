#include "base/interrupts.hpp"

namespace base
{

  auto unhandled_interrupt() -> void
  {
    while (true)
      ;
  }

}  // namespace base