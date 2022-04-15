#ifndef DRINLI_SUPORT_TYPE_LIST_HPP
#define DRINLI_SUPORT_TYPE_LIST_HPP

#include <cstddef>
#include <type_traits>
#include <utility>
#include <variant>

namespace drinli::support
{

  template<typename Type>
  struct type final
  {
    template<typename OtherType>
    auto constexpr operator==(type<OtherType>) const noexcept
    {
      return std::is_same_v<Type, OtherType>;
    }

    template<typename OtherType>
    auto constexpr operator!=(type<OtherType> other) const noexcept
    {
      return !(*this == other);
    }
  };

  template<typename Type>
  auto constexpr type_v = type<Type>{};

  template<typename... Types>
  struct type_list final
  {
    constexpr type_list(type<Types>...)
    {
    }

    template<typename Needle>
    auto constexpr contains(type<Needle> type) const noexcept -> bool
    {
      return count(type);
    }

    template<typename Needle>
    auto constexpr count(type<Needle> type) const noexcept -> std::size_t
    {
      return (std::size_t{} + ... + static_cast<std::size_t>(type_v<Types> == type));
    }
  };

  template<typename... Types>
  type_list(type<Types>...) -> type_list<Types...>;

}  // namespace drinli::support

#endif