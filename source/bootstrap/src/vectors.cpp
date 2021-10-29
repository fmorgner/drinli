#include "bootstrap/detail/startup.hpp"
#include "bootstrap/detail/symbols.hpp"

#include <array>
#include <cstdlib>

namespace drinli::bootstrap::detail
{

  auto unhandled_interrupt() noexcept -> void
  {
    while (true)
      ;
  };

  auto constexpr reserved_vector = static_cast<void (*)() noexcept>(nullptr);

  extern "C" [[gnu::section(".initial_stack"), gnu::used]] auto constexpr initial_stack = &_initial_stack_end;
  static_assert(sizeof(initial_stack) == sizeof(void *));

  extern "C" [[gnu::section(".interrupt_vectors"), gnu::used]] auto constexpr interrupt_vectors = std::array{
      &start,                // Initial base reset vector
      &unhandled_interrupt,  // NMI vector
      &unhandled_interrupt,  // Hard Fault vector
      &unhandled_interrupt,  // Memory Management Fault vector
      &unhandled_interrupt,  // Bus Fault vector
      &unhandled_interrupt,  // Usage Fault vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &unhandled_interrupt,  // Supervisor Call vector
      &unhandled_interrupt,  // Debug Monitor vector
      reserved_vector,
      &unhandled_interrupt,  // Pending Service vector
      &unhandled_interrupt,  // base Tick vector
      &unhandled_interrupt,  // GPIO Port A vector
      &unhandled_interrupt,  // GPIO Port B vector
      &unhandled_interrupt,  // GPIO Port C vector
      &unhandled_interrupt,  // GPIO Port D vector
      &unhandled_interrupt,  // GPIO Port E vector
      &unhandled_interrupt,  // UART 0 Receive and Transmit vector
      &unhandled_interrupt,  // UART 1 Receive and Transmit vector
      &unhandled_interrupt,  // SSI 0 Receive and Transmit vector
      &unhandled_interrupt,  // I2C 0 Master and Slave vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &unhandled_interrupt,  // ADC Sequence 0 vector
      &unhandled_interrupt,  // ADC Sequence 1 vector
      &unhandled_interrupt,  // ADC Sequence 2 vector
      &unhandled_interrupt,  // ADC Sequence 3 vector
      &unhandled_interrupt,  // Watchdog Timer 0 and 1 vector
      &unhandled_interrupt,  // Timer 0 Subtimer A vector
      &unhandled_interrupt,  // Timer 0 Subtimer B vector
      &unhandled_interrupt,  // Timer 1 Subtimer A vector
      &unhandled_interrupt,  // Timer 1 Subtimer B vector
      &unhandled_interrupt,  // Timer 2 Subtimer A vector
      &unhandled_interrupt,  // Timer 2 Subtimer B vector
      &unhandled_interrupt,  // Analog Comparator 0 vector
      &unhandled_interrupt,  // Analog Comparator 1 vector
      reserved_vector,
      &unhandled_interrupt,  // base Control vector
      &unhandled_interrupt,  // Flash Memory and EEPROM Control vector
      &unhandled_interrupt,  // GPIO Port F vector
      reserved_vector,
      reserved_vector,
      &unhandled_interrupt,  // UART2 Receive and Transmit vector
      &unhandled_interrupt,  // SSI1 Receive and Transmit vector
      &unhandled_interrupt,  // Timer 3 Subtimer A vector
      &unhandled_interrupt,  // Timer 3 Subtimer B vector
      &unhandled_interrupt,  // I2C 1 Master and Slave vector
      reserved_vector,
      &unhandled_interrupt,  // CAN 0 vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &unhandled_interrupt,  // Hibernate vector
      &unhandled_interrupt,  // USB vector
      reserved_vector,
      &unhandled_interrupt,  // uDMA Software Transfer vector
      &unhandled_interrupt,  // uDMA Error vector
      &unhandled_interrupt,  // ADC 1 Sequence 0 vector
      &unhandled_interrupt,  // ADC 1 Sequence 1 vector
      &unhandled_interrupt,  // ADC 1 Sequence 2 vector
      &unhandled_interrupt,  // ADC 1 Sequence 3 vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &unhandled_interrupt,  // SSI 2 Receive and Transmit vector
      &unhandled_interrupt,  // SSI 3 Receive and Transmit vector
      &unhandled_interrupt,  // UART 3 Receive and Transmit vector
      &unhandled_interrupt,  // UART 4 Receive and Transmit vector
      &unhandled_interrupt,  // UART 5 Receive and Transmit vector
      &unhandled_interrupt,  // UART 6 Receive and Transmit vector
      &unhandled_interrupt,  // UART 7 Receive and Transmit vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &unhandled_interrupt,  // I2C 2 Master and Slave vector
      &unhandled_interrupt,  // I2C 3 Master and Slave vector
      &unhandled_interrupt,  // Timer 4 Subtimer A vector
      &unhandled_interrupt,  // Timer 4 Subtimer B vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &unhandled_interrupt,  // Timer 5 Subtimer A vector
      &unhandled_interrupt,  // Timer 5 Subtimer B vector
      &unhandled_interrupt,  // Wide Timer 0 Subtimer A vector
      &unhandled_interrupt,  // Wide Timer 0 Subtimer B vector
      &unhandled_interrupt,  // Wide Timer 1 Subtimer A vector
      &unhandled_interrupt,  // Wide Timer 1 Subtimer B vector
      &unhandled_interrupt,  // Wide Timer 2 Subtimer A vector
      &unhandled_interrupt,  // Wide Timer 2 Subtimer B vector
      &unhandled_interrupt,  // Wide Timer 3 Subtimer A vector
      &unhandled_interrupt,  // Wide Timer 3 Subtimer B vector
      &unhandled_interrupt,  // Wide Timer 4 Subtimer A vector
      &unhandled_interrupt,  // Wide Timer 4 Subtimer B vector
      &unhandled_interrupt,  // Wide Timer 5 Subtimer A vector
      &unhandled_interrupt,  // Wide Timer 5 Subtimer B vector
      &unhandled_interrupt,  // base Exception vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
  };

  static_assert(interrupt_vectors.size() == 154, "The LM4F120 expects 154 interrupt vectors!");

}  // namespace drinli::bootstrap::detail
