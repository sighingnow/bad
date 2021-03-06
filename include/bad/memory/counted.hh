#ifndef BAD_MEMORY_COUNTED_HH
#define BAD_MEMORY_COUNTED_HH

#include "bad/common.hh"
#include "bad/memory/namespace.hh"

namespace bad::memory::api {

  // TODO: incorporate an allocator into the policy so we can free on the gpu, etc.

  struct thread_unsafe_policy {
    using type = size_t;

    BAD(hd,inline,const)
    static size_t load(type s) {
      return s;
    }

    BAD(hd,inline,noalias)
    static void inc(
      BAD(noescape) type & s
    ) noexcept {
      ++s;
    }

    BAD(hd,inline,noalias)
    static size_t dec(
      BAD(noescape) type & s
    ) noexcept {
      return --s;
    }
  };

  // this will probably have to be hacked up to work with cuda as std::atomic and cuda::atomic are separate beasts
  struct atomic_policy {
    using type = std::atomic_size_t;

    BAD(hd,inline,const)
    static size_t load(type const & s) {
      return s.load();
    }

    BAD(hd,inline,noalias)
    static void inc(
      BAD(noescape) type & s
    ) noexcept {
      ++s;
    }

    BAD(hd,inline,noalias)
    static size_t dec(
      BAD(noescape) type & s
    ) noexcept {
      return --s;
    }
  };
}

namespace bad::memory::common {

  template <class B, class Policy = thread_unsafe_policy>
  struct counted {
    using policy = Policy;
    using ref_count_type = typename policy::type;

    mutable ref_count_type ref_count;

    BAD(hd,inline)
    counted() noexcept : ref_count(0) {}

    BAD(hd,inline)
    counted(BAD(maybe_unused) counted const & rhs) noexcept : ref_count(0) {}

    BAD(hd,inline,const)
    counted & operator = (BAD(maybe_unused) counted const & rhs) noexcept {
      return *this;
    }

    BAD(hd,inline,pure)
    size_t reference_count() noexcept {
      return policy::load(ref_count);
    }

  };

  template <class B>
  using atomically_counted = counted<B,atomic_policy>;

  template <class B, class Policy>
  BAD(hd,inline)
  void acquire(counted<B,Policy> const * rhs) noexcept {
    Policy::inc(rhs->ref_count);
  }

  template <class B, class Policy>
  BAD(hd,inline)
  void release(counted<B,Policy> const * rhs) noexcept {
    if (Policy::dec(rhs->ref_count) == 0)
      delete static_cast<B const *>(rhs);
  }
}

#endif
