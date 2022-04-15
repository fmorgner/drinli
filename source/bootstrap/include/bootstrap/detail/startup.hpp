#ifndef DRINLI_BOOTSTRAP_DETAIL_STARTUP_HPP
#define DRINLI_BOOTSTRAP_DETAIL_STARTUP_HPP

namespace drinli::bootstrap::detail
{

  /**
   * @brief Start the firmware.
   */
  [[noreturn]] auto start() noexcept -> void;

}  // namespace drinli::bootstrap::detail

#endif
