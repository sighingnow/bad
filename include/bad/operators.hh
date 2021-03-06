#ifndef BAD_OPERATORS_HH
#define BAD_OPERATORS_HH

#include "attributes.hh"

/// \file
/// \brief operators and move semantics
/// \author Edward Kmett
/// \author Daniel Friy

/// \defgroup operators_group operators
/// \brief operators and move semantics

/// \namespace bad
/// \private
namespace bad {
  /// \namespace bad::operators
  /// \ref operators_group "operators" internals, import bad::operators::api
  /// \ingroup operators_group
  namespace operators {
    /// \namespace bad::operators::common
    /// \ingroup operators_group
    /// re-exported by \ref bad and bad::operators::api
    namespace common {}
    /// \namespace bad::operators::api
    /// \ingroup operators_group
    /// See \ref operators_group "operators" for a complete listing.
    namespace api { using namespace common; }
    using namespace api;
  }
  using namespace operators::common;
}

/// \def bad_op(name,op)
/// \private
#define bad_op(name,op) \
  /** provides `T op U` given `T op## = U`. \n\
   \tparam T current type \n\
   \tparam U the other type */\
  template<class T, class U = T>\
  struct BAD(empty_bases) name {\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T const & lhs, T const & rhs)\
    noexcept(noexcept(T(lhs), std::declval<T&>() op## = rhs,T(std::declval<T&>()))) {\
      T x(lhs); x op## = rhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T const & lhs, T && rhs)\
    noexcept(noexcept(T(lhs), std::declval<T&>() op## = std::move(rhs),T(std::declval<T&>()))) {\
      T x(lhs); x op## = std::move(rhs); return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T && lhs, T const & rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = rhs, T(std::declval<T&>()))) {\
      T x(std::move(lhs)); x op## = rhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T && lhs, T && rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = std::move(rhs), T(std::declval<T&>()))) {\
      T x(std::move(lhs)); x op## = std::move(rhs); return rhs;\
    }\
  }

/// \def bad_op_left(name,op)
/// \private
#define bad_op_left(name,op) \
  bad_op(name,op);\
  /** provides `U op T` given both `T(U)` and `T op## = U` \n\
   \tparam T current type \n\
   \tparam U the other type */\
  template<class T, class U>\
  struct BAD(empty_bases) name##_left {\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(U const & lhs, T const & rhs)\
    noexcept(noexcept(T(lhs), std::declval<T&>() op## = rhs, T(std::declval<T&>()))) {\
      T x(lhs); x op## = rhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(U const & lhs, T&& rhs)\
    noexcept(noexcept(T(lhs), std::declval<T&>() op## = std::move(rhs), T(std::declval<T&>()))) {\
      T x(lhs); x op## = std::move(rhs); return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(U&& lhs, T const & rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = rhs, T(std::declval<T&>()))) {\
      T x(std::move(lhs)); x op## = rhs; return x;\
    }\
    friend T operator op(U&& lhs, T&& rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = std::move(rhs), T(std::declval<T&>()))) {\
      T x( std::move(lhs)); x op## = std::move(rhs); return x;\
    }\
  }

/// \private
#define bad_op_commutative(name,op) \
  bad_op_left(name,op);\
  /** provides `T op U` and `U op T` given `T op## = U` \n\
   \tparam T current type \n\
   \tparam U the other type */\
  template<class T, class U = T>\
  struct BAD(empty_bases) commutative_##name {\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T const & lhs, U const & rhs)\
    noexcept(noexcept(T(lhs), std::declval<T&>() op## = rhs,T(std::declval<T&>()))) {\
      T x(lhs); x op## = rhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T const & lhs, U&& rhs)\
    noexcept(noexcept(T(lhs), std::declval<T&>() op## = std::move(rhs), T(std::declval<T&>()))) {\
      T x(lhs); x op## = std::move(rhs); return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T&& lhs, U const & rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = rhs, T(std::declval<T&>()))) {\
      T x(std::move(lhs)); x op## = rhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T&& lhs, U&& rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = std::move(rhs), T(std::declval<T&>()))) {\
      T x(std::move(lhs)); x op## = std::move(rhs); return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(U const & lhs, T const & rhs)\
    noexcept(noexcept(T(rhs), std::declval<T&>() op## = lhs, T(std::declval<T&>()))) {\
      T x(rhs); x op## = lhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(U const & lhs, T&& rhs)\
    noexcept(noexcept(T(std::move(rhs)),std::declval<T&>() op## = lhs, T(std::declval<T&>()))) {\
      T x(std::move(rhs)); x op## = lhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(U&& lhs, T const & rhs)\
    noexcept(noexcept(T(rhs), std::declval<T&>() op## = std::move(lhs))) {\
      T x(rhs); x op## = std::move( lhs ); return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(U&& lhs, T&& rhs)\
    noexcept(noexcept(T(std::move(rhs)), std::declval<T&>() op## = std::move(lhs))) {\
      T x(std::move(rhs)); x op## = std::move(lhs); return x;\
    }\
  };\
\
  template<class T>\
  /** provides `T op T` given `T op##= T` \n\
   \tparam T current type */\
  struct BAD(empty_bases) commutative_##name< T> {\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T const & lhs, T const & rhs)\
    noexcept(noexcept(T(lhs), std::declval<T&>() op## = rhs, T(std::declval<T&>()))) {\
      T x(lhs); x op## = rhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T const & lhs, T&& rhs)\
    noexcept(noexcept(T(lhs), std::declval< T& >() op## = std::move(rhs), T(std::declval<T&>()))) {\
      T x(lhs); x op## = std::move(rhs); return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T&& lhs, T const & rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = rhs, T(std::declval<T&>()))) {\
      T x(std::move(lhs)); x op## = rhs; return x;\
    }\
    BAD(hd,nodiscard,inline,flatten)\
    friend T operator op(T&& lhs, T&& rhs)\
    noexcept(noexcept(T(std::move(lhs)), std::declval<T&>() op## = std::move(rhs), T(std::declval<T&>()))) {\
      T x(std::move(lhs));\
      x op## = std::move(rhs);\
      return x;\
    }\
  }

/// \ingroup operators_group
/// \{

namespace bad::operators::api {

  /// \defgroup equality equality
  /// `!=` and `==`
  /// \ingroup operators_group
  /// \{

  /// provides `T != U`, `U == T`, and `U != T`, when given `T == U`
  /// \tparam T current type
  /// \tparam U the other type
  template <class T, class U=T>
  struct BAD(empty_bases) equality_comparable {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator != (BAD(noescape) T const & lhs, BAD(noescape) U const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs==rhs))) {
      return !static_cast<bool>(lhs==rhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator == (BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs==rhs))) {
      return static_cast<bool>(lhs==rhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator != (BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs!=rhs))) {
      return static_cast<bool>(lhs!=rhs);
    }
  };

  /// provides `T != T` when given `T == T`
  /// \tparam T current type
  template <class T>
  struct BAD(empty_bases) equality_comparable<T> {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator != (BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs==rhs))) {
      return !static_cast<bool>(lhs==rhs);
    }
  };

  /// \}

  /// \defgroup ordering ordering
  /// `<`, `>`, `<=`, and `=>`
  /// \ingroup operators_group
  /// \{

  /// provides `T <= U`, `T >= U`, `U < T`, `U > T`, `U <= T`, and `U >= T` when given `T < U` and `T > U`
  /// \tparam T current type
  /// \tparam U the other type
  template<class T, class U = T>
  struct BAD(empty_bases) less_than_comparable {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<=(BAD(noescape) T const & lhs, BAD(noescape) U const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs > rhs))) {
      return !static_cast<bool>(lhs > rhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>=(BAD(noescape) T const & lhs, BAD(noescape) U const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs < rhs))) {
      return !static_cast<bool>(lhs < rhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs > lhs))) {
      return static_cast<bool>(rhs > lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs < lhs))) {
      return static_cast<bool>(rhs < lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<=(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs >= lhs))) {
      return static_cast<bool>(rhs >= lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>=(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs <= lhs))) {
      return static_cast<bool>(rhs <= lhs);
    }
  };

  /// provides `T <= T`, `T >= T`, `T > T` when given `T < T`
  /// \tparam T current type
  template<class T>
  struct BAD(empty_bases) less_than_comparable<T> {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>(BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs < lhs))) {
      return static_cast<bool>(rhs < lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<=(BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs < lhs))) {
      return !static_cast<bool>(rhs < lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>=(BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs < rhs))) {
      return !static_cast<bool>(lhs < rhs);
    }
  };

  template<class T, class U = T>
  struct BAD(empty_bases) totally_ordered
  : less_than_comparable<T,U>
  , equality_comparable<T,U> {};

  /// provides `T == U` when given `T < U` and `T > U`
  /// \tparam T current type
  /// \tparam U the other type
  template<class T, class U = T>
  struct BAD(empty_bases) equivalent {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator==(BAD(noescape) T const & lhs, BAD(noescape) U const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs < rhs), static_cast<bool>(lhs > rhs))) {
      return !static_cast<bool>(lhs < rhs) && !static_cast<bool>(lhs > rhs);
    }
  };

  /// provides `T == T when given `T < T`
  /// \tparam T current type
  template<class T>
  struct BAD(empty_bases) equivalent<T> {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator==(BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs < rhs))) {
      return !static_cast<bool>(lhs < rhs) && !static_cast<bool>(rhs < lhs);
    }
  };

  /// provides `T <= U`, `T >= U`, `U < T`, `U <= T`, and `U >= T` when given `T < U`, `T > U`, `T == U`
  /// \tparam T current type
  /// \tparam U the other type
  template<class T, class U = T>
  struct BAD(empty_bases) partially_ordered {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<=(BAD(noescape) T const & lhs, BAD(noescape) U const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs < rhs), static_cast<bool>(lhs == rhs))) {
      return static_cast<bool>(lhs < rhs) || static_cast<bool>(lhs == rhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>=(BAD(noescape) T const & lhs, BAD(noescape) U const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs > rhs), static_cast<bool>(lhs == rhs))) {
      return static_cast<bool>(lhs > rhs) || static_cast<bool>(lhs == rhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs > lhs))) {
      return static_cast<bool>(rhs > lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept( noexcept( static_cast<bool>(rhs < lhs))) {
      return static_cast<bool>(rhs < lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<=(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs >= lhs))) {
      return static_cast< bool >(rhs >= lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>=(BAD(noescape) U const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs <= lhs))) {
      return static_cast<bool>(rhs <= lhs);
    }
  };

  /// provides `T > T`, `T <= T`, and `T >= T` when given `T < T` and `T == T`
  /// \tparam T current type
  template<class T>
  struct BAD(empty_bases) partially_ordered<T> {
    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>(BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs < lhs))) {
      return static_cast<bool>(rhs < lhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator<=(BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(lhs < rhs), static_cast<bool>(lhs == rhs))) {
      return static_cast<bool>(lhs < rhs) || static_cast<bool>(lhs == rhs);
    }

    BAD(hd,nodiscard,inline,flatten) constexpr
    friend bool operator>=(BAD(noescape) T const & lhs, BAD(noescape) T const & rhs)
    noexcept(noexcept(static_cast<bool>(rhs < lhs), static_cast<bool>(lhs == rhs))) {
      return static_cast<bool>(rhs < lhs) || static_cast<bool>(lhs == rhs);
    }
  };

  /// \}

  /// \defgroup arithmetic arithmetic
  /// `+`,`-`,`*`,`/`, and `%`
  /// \ingroup operators_group
  /// \{

  bad_op_commutative(addable, +);
  bad_op_left(subtractable, -);
  bad_op_commutative(multipliable, *);
  bad_op_left(dividable, /);
  bad_op_left(modable, % );

  /// provides `T @ U` and `U @ T` when given `T(U)`, `T @= U` for `@` in `{+,-,*}`
  /// \tparam T current type
  /// \tparam U the other type
  template <class T, class U=T>
  struct BAD(empty_bases) ringlike
  : commutative_addable<T,U>
  , subtractable<T,U>
  , subtractable_left<T,U>
  , multipliable<T,U> {};

  /// \}

  /// \defgroup bitwise bitwise
  /// `&`, `|`, `^`, `<<` and `>>`
  /// \ingroup operators_group
  /// \{

  bad_op_commutative(andable, &);
  bad_op_commutative(orable, |);
  bad_op_commutative(xorable, ^);

  /// provides `T @ U` when given `T @= U` for `@` in `{&,|,^}`
  /// \tparam T current type
  /// \tparam U the other type
  template <class T, class U=T>
  struct BAD(empty_bases) bitwise
  : andable<T,U>
  , orable<T,U>
  , xorable<T,U> {};

  /// provides `U @ T` when given `T @= U` and `T(U)` for `@` in `{&,|,^}`
  /// \tparam T current type
  /// \tparam U the other type
  template <class T, class U=T>
  struct BAD(empty_bases) bitwise_left
  : andable_left<T,U>
  , orable_left<T,U>
  , xorable_left<T,U> {};

  /// provides `T @ U` and `U @ T` when given `T @= U` in `{&,|,^}`
  /// \tparam T current type
  /// \tparam U the other type
  template <class T, class U=T>
  struct BAD(empty_bases) commutative_bitwise
  : commutative_andable<T,U>
  , commutative_orable<T,U>
  , commutative_xorable<T,U> {};

  bad_op(left_shiftable, <<);
  bad_op(right_shiftable, >>);

  /// provides `T @ U` when given `T @= U` for `@` in `{<<,>>}`
  /// \tparam T current type
  /// \tparam U the other type
  template <class T, class U=T>
  struct BAD(empty_bases) shiftable
  : left_shiftable<T,U>
  , right_shiftable<T,U> {};

  /// \}
}
/// \}

#undef bad_op
#undef bad_op_left
#undef bad_op_commutative

// The MIT License (MIT)
//
// Copyright (c) 2021 Edward Kmett
// Copyright (c) 2013-2020 Daniel Frey
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#endif
