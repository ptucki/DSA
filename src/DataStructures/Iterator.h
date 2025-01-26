#ifndef DATA_STRUCTURES_ITERATOR_H_
#define DATA_STRUCTURES_ITERATOR_H_

#include <iterator>

template<class T, bool Const = false>
class Iterator {
public:

  using value_type = T;
  using difference_type = size_t;
  using reference = T&;
  using pointer = T*;
  using iterator_category = std::random_access_iterator_tag;

  Iterator(T* ptr, size_t pos, size_t size)
    : ptr_{ ptr }, pos_{ pos }, size_{ size } {}
  ~Iterator() = default;
  Iterator(const Iterator& obj)
    : ptr_{ obj.ptr_ }, pos_{ obj.pos_ }, size_{ obj.size_ } {}
  Iterator(Iterator&& obj) noexcept
    : ptr_{ obj.ptr_ }, pos_{ obj.pos_ }, size_{ obj.size_ }
  {
    obj.ptr_ = nullptr;
    obj.pos_ = 0;
  }

  Iterator& operator=(const Iterator& obj) {
    if (this == &obj) return *this;
    ptr_ = obj.ptr_;
    pos_ = obj.pos_;
    size_ = obj.size_;
    return *this;
  }

  Iterator& operator=(Iterator&& obj) {
    if (this == &obj) return *this;
    ptr_ = obj.ptr_;
    pos_ = obj.pos_;
    size_ = obj.size_;
    obj.ptr_ = nullptr;
    obj.pos_ = 0;
    obj.size_ = 0;
    return *this;
  }

  void swap(Iterator& obj) {
    std::swap(ptr_, obj.ptr_);
    std::swap(pos_, obj.pos_);
  }

  decltype(auto) operator*() const {
    if (pos_ == size_) {
      throw std::overflow_error("It's end iterator");
    }

    if constexpr(Const) {
      return const_cast<const reference>(*(ptr_ + pos_));
    } else {
      return *(ptr_ + pos_);
    }
  }

  decltype(auto) operator->() const {
    if (pos_ == size_) {
      throw std::overflow_error("It's end iterator");
    }
    if constexpr(Const) {
      return const_cast<const value_type* const>(ptr_ + pos_);
    } else {
      return ptr_ + pos_;
    }
  }

  Iterator operator++() const {
    if (pos_ == size_) {
      throw std::overflow_error("It's end iterator");
    }
    pos_++;
    return *this;
  }

  Iterator operator++(int) const {
    if (pos_ == size_) {
      throw std::overflow_error("It's end iterator");
    }
    Iterator current(*this);
    pos_++;
    return current;
  }

  Iterator& operator--() const {
    if (pos_ == 0) {
      throw std::overflow_error("It's begin iterator");
    }
    pos_--;
    return *this;
  }

  Iterator operator--(int) const {
    if (pos_ == 0) {
      throw std::overflow_error("It's begin iterator");
    }
    Iterator current(*this);
    pos_--;
    return current;
  }

  bool operator==(const Iterator& obj) {
    return (ptr_ == obj.ptr_) && (pos_ == obj.pos_);
  }

  bool operator!=(const Iterator& obj) {
    return (ptr_ != obj.ptr_) || (pos_ != obj.pos_);
  }

  Iterator& operator+=(int distance) const {
    if (((pos_ + distance) >= size_) || ((pos_ + distance) < 0)) {
      throw std::overflow_error("Distance exceeds array boundries");
    }
    pos_ += distance;
    return *this;
  }

  Iterator& operator-=(int distance) const {
    if (((pos_ - distance) >= size_) || ((pos_ - distance) < 0)) {
      throw std::overflow_error("Distance exceeds array boundries");
    }
    pos_ -= distance;
    return *this;
  }

  Iterator operator+(int distance) const {
    if (((pos_ + distance) > size_) || ((pos_ + distance) < 0)) {
      throw std::overflow_error("Distance exceeds array boundries");
    }
    auto it = *this;
    it.pos_ += distance;
    return it;
  }

  Iterator operator-(int distance) const {
    if (((pos_ - distance) > size_) || ((pos_ - distance) < 0)) {
      throw std::overflow_error("Distance exceeds array boundries");
    }
    auto it = *this;
    it.pos_ -= distance;
    return it;
  }

  size_t operator-(const Iterator& it) const {
    if ((ptr_ != it.ptr_) || (it.pos_ > pos_)) {
      throw std::overflow_error("Distance exceeds array boundries");
    } 

    return pos_ - it.pos_;
  }

  value_type& operator[](size_t pos) const {
    if (pos + pos_ >= size_) {
      throw std::overflow_error("Overflows container size");
    } 

    return *(ptr_ + pos_ + pos);
  }

  static int Distance(const Iterator& it1, const Iterator& it2) {
    if (it1.ptr_ != it2.ptr_) {
      throw std::invalid_argument("Iterators point to different containers");
    }
    return static_cast<int>(it2.pos_) - static_cast<int>(it1.pos_);
  }

private:
  mutable size_t pos_;
  size_t size_;
  value_type* ptr_;
};

template<typename T, bool Const>
Iterator<T, Const>& operator+(int distance, Iterator<T, Const>& it) {
  it += distance;
  return it;
}


#endif // !DATA_STRUCTURES_ITERATOR_H_
