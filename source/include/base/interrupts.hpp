#ifndef DRINLI_BASE_INTERRUPTS_HPP
#define DRINLI_BASE_INTERRUPTS_HPP

namespace base
{

  /**
   * Handler for unhandled interrupts
   */
  auto unhandled_interrupt() -> void;

}  // namespace base

#endif