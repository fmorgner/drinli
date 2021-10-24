#include "base/interrupts.hpp"
#include "base/reset.hpp"
#include "base/symbols.hpp"

#include <array>
#include <cstdlib>

namespace
{
  auto constexpr reserved_vector = static_cast<void (*)()>(nullptr);

  [[gnu::section(".initial_stack"), gnu::used]] auto constexpr initial_stack = &base::_initial_stack_end;
  static_assert(sizeof(initial_stack) == sizeof(void *));

  [[gnu::section(".interrupt_vectors"), gnu::used]] auto constexpr interrupt_vectors = std::array{
      &::base::reset,                // Initial base reset vector
      &::base::unhandled_interrupt,  // NMI vector
      &::base::unhandled_interrupt,  // Hard Fault vector
      &::base::unhandled_interrupt,  // Memory Management Fault vector
      &::base::unhandled_interrupt,  // Bus Fault vector
      &::base::unhandled_interrupt,  // Usage Fault vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &::base::unhandled_interrupt,  // Supervisor Call vector
      &::base::unhandled_interrupt,  // Debug Monitor vector
      reserved_vector,
      &::base::unhandled_interrupt,  // Pending Service vector
      &::base::unhandled_interrupt,  // base Tick vector
      &::base::unhandled_interrupt,  // GPIO Port A vector
      &::base::unhandled_interrupt,  // GPIO Port B vector
      &::base::unhandled_interrupt,  // GPIO Port C vector
      &::base::unhandled_interrupt,  // GPIO Port D vector
      &::base::unhandled_interrupt,  // GPIO Port E vector
      &::base::unhandled_interrupt,  // UART 0 Receive and Transmit vector
      &::base::unhandled_interrupt,  // UART 1 Receive and Transmit vector
      &::base::unhandled_interrupt,  // SSI 0 Receive and Transmit vector
      &::base::unhandled_interrupt,  // I2C 0 Master and Slave vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &base::unhandled_interrupt,  // ADC Sequence 0 vector
      &base::unhandled_interrupt,  // ADC Sequence 1 vector
      &base::unhandled_interrupt,  // ADC Sequence 2 vector
      &base::unhandled_interrupt,  // ADC Sequence 3 vector
      &base::unhandled_interrupt,  // Watchdog Timer 0 and 1 vector
      &base::unhandled_interrupt,  // Timer 0 Subtimer A vector
      &base::unhandled_interrupt,  // Timer 0 Subtimer B vector
      &base::unhandled_interrupt,  // Timer 1 Subtimer A vector
      &base::unhandled_interrupt,  // Timer 1 Subtimer B vector
      &base::unhandled_interrupt,  // Timer 2 Subtimer A vector
      &base::unhandled_interrupt,  // Timer 2 Subtimer B vector
      &base::unhandled_interrupt,  // Analog Comparator 0 vector
      &base::unhandled_interrupt,  // Analog Comparator 1 vector
      reserved_vector,
      &base::unhandled_interrupt,  // base Control vector
      &base::unhandled_interrupt,  // Flash Memory and EEPROM Control vector
      &base::unhandled_interrupt,  // GPIO Port F vector
      reserved_vector,
      reserved_vector,
      &base::unhandled_interrupt,  // UART2 Receive and Transmit vector
      &base::unhandled_interrupt,  // SSI1 Receive and Transmit vector
      &base::unhandled_interrupt,  // Timer 3 Subtimer A vector
      &base::unhandled_interrupt,  // Timer 3 Subtimer B vector
      &base::unhandled_interrupt,  // I2C 1 Master and Slave vector
      reserved_vector,
      &base::unhandled_interrupt,  // CAN 0 vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &base::unhandled_interrupt,  // Hibernate vector
      &base::unhandled_interrupt,  // USB vector
      reserved_vector,
      &base::unhandled_interrupt,  // uDMA Software Transfer vector
      &base::unhandled_interrupt,  // uDMA Error vector
      &base::unhandled_interrupt,  // ADC 1 Sequence 0 vector
      &base::unhandled_interrupt,  // ADC 1 Sequence 1 vector
      &base::unhandled_interrupt,  // ADC 1 Sequence 2 vector
      &base::unhandled_interrupt,  // ADC 1 Sequence 3 vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &base::unhandled_interrupt,  // SSI 2 Receive and Transmit vector
      &base::unhandled_interrupt,  // SSI 3 Receive and Transmit vector
      &base::unhandled_interrupt,  // UART 3 Receive and Transmit vector
      &base::unhandled_interrupt,  // UART 4 Receive and Transmit vector
      &base::unhandled_interrupt,  // UART 5 Receive and Transmit vector
      &base::unhandled_interrupt,  // UART 6 Receive and Transmit vector
      &base::unhandled_interrupt,  // UART 7 Receive and Transmit vector
      reserved_vector,
      reserved_vector,
      reserved_vector,
      reserved_vector,
      &base::unhandled_interrupt,  // I2C 2 Master and Slave vector
      &base::unhandled_interrupt,  // I2C 3 Master and Slave vector
      &base::unhandled_interrupt,  // Timer 4 Subtimer A vector
      &base::unhandled_interrupt,  // Timer 4 Subtimer B vector
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
      &base::unhandled_interrupt,  // Timer 5 Subtimer A vector
      &base::unhandled_interrupt,  // Timer 5 Subtimer B vector
      &base::unhandled_interrupt,  // Wide Timer 0 Subtimer A vector
      &base::unhandled_interrupt,  // Wide Timer 0 Subtimer B vector
      &base::unhandled_interrupt,  // Wide Timer 1 Subtimer A vector
      &base::unhandled_interrupt,  // Wide Timer 1 Subtimer B vector
      &base::unhandled_interrupt,  // Wide Timer 2 Subtimer A vector
      &base::unhandled_interrupt,  // Wide Timer 2 Subtimer B vector
      &base::unhandled_interrupt,  // Wide Timer 3 Subtimer A vector
      &base::unhandled_interrupt,  // Wide Timer 3 Subtimer B vector
      &base::unhandled_interrupt,  // Wide Timer 4 Subtimer A vector
      &base::unhandled_interrupt,  // Wide Timer 4 Subtimer B vector
      &base::unhandled_interrupt,  // Wide Timer 5 Subtimer A vector
      &base::unhandled_interrupt,  // Wide Timer 5 Subtimer B vector
      &base::unhandled_interrupt,  // base Exception vector
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
  static_assert(interrupt_vectors.size() == 154);
}  // namespace
