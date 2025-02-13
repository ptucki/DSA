#ifndef DATA_STRUCTURES_VECTOR_H_
#define DATA_STRUCTURES_VECTOR_H_

#include <memory>
#include <utility>
#include <initializer_list>

#include "Iterator.h"

namespace Ds {

template<class T, class Allocator = std::allocator<T>>
class Vector {

  using value_type = T;
  using allocator_type  = Allocator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer 
    = typename std::allocator_traits<Allocator>::const_pointer;
  using iterator = Iterator<T>;
  using const_iterator = Iterator<T, true>;
  using reverse_iterator = std::reverse_iterator<Iterator<T>>;
  using const_reverse_iterator = const std::reverse_iterator<Iterator<T>>;

  static constexpr size_type kInitialCapacity{ 2 };
  static constexpr size_type kInitialSize{ 0 };
public:

  Vector();
  Vector(std::initializer_list<T> values);
  ~Vector();

  template<class U = T>
  void PushBack(U&& value);
  template<typename... Args>
  T& EmplaceBack(Args... arg);
  size_type Capacity() const;
  size_type Size() const;
  T& Front() const;
  T& Back() const;
  void Reserve(size_type new_cap);
  T& At(size_type pos) const;
  T& operator[](size_type pos) const;
  bool Empty() const;
  void Clear();
  void Resize(size_t new_size);

  iterator begin() const;
  const_iterator cbegin() const;
  iterator end() const;
  const_iterator cend() const;

private:

  Allocator allocator_;
  size_type capacity_;
  size_type size_;
  T* data_;
};

template<class T, class Allocator>
Vector<T, Allocator>::Vector()
  : allocator_{}
  , capacity_{ kInitialCapacity }
  , size_{ kInitialSize }
  , data_{ std::allocator_traits<Allocator>::allocate(
      allocator_,
      kInitialCapacity
    )} {}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> values)
  : allocator_{}
  , capacity_{ values.size() }
  , size_{ values.size() }
  , data_{ std::allocator_traits<Allocator>::allocate(
    allocator_,
    values.size()
  )}
{
  auto it = begin();
  for (auto& value : values) {
    std::allocator_traits<Allocator>::construct(
      allocator_, &(*it), std::move(value));
    it++;
  }
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector() {
  for (size_type i = 0; i < size_; ++i) {
    std::allocator_traits<Allocator>::destroy(allocator_, &data_[i]);
  }
  std::allocator_traits<Allocator>::deallocate(allocator_, data_, capacity_);
}

template<class T, class Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::Capacity() const {
  return capacity_;
}

template<class T, class Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::Size() const {
  return size_;
}

template<class T, class Allocator>
void Vector<T, Allocator>::Reserve(size_type new_cap) {
  if (new_cap <= capacity_) {
    return;
  }

  auto new_data =
    std::allocator_traits<Allocator>::allocate(allocator_, new_cap);

  auto size = Size();
  auto allocator = Allocator{};
  for (auto i = 0; i < size; ++i) {
    std::allocator_traits<Allocator>::construct(
      allocator, &new_data[i], std::move(data_[i]));
    std::allocator_traits<Allocator>::destroy(allocator, &data_[i]);
  }
  std::allocator_traits<Allocator>::deallocate(allocator, data_, capacity_);
  data_ = new_data;
  capacity_ = new_cap;
}

template<class T, class Allocator>
template<class U>
void Vector<T, Allocator>::PushBack(U&& value) {
  if (size_ == capacity_) {
    Reserve(2 * capacity_);
  }
  std::allocator_traits<Allocator>::construct(
    allocator_, &data_[size_], std::forward<U>(value));
  size_++;
}

template<class T, class Allocator>
template<typename... Args>
T& Vector<T, Allocator>::EmplaceBack(Args... arg) {
  if (size_ == capacity_) {
    Reserve(2 * capacity_);
  }
  std::allocator_traits<Allocator>::construct(
    allocator_, &data_[size_], std::forward<Args>(arg)...);
  size_++;

  return data_[size_ - 1];
}

template<class T, class Allocator>
T& Vector<T, Allocator>::At(size_type pos) const {
  if (pos >= size_) {
    throw std::invalid_argument("Parameter pos exceeds vector size.");
  }
  return data_[pos];
}

template<class T, class Allocator>
T& Vector<T, Allocator>::operator[](size_type pos) const {
  return At(pos);
}

template<class T, class Allocator>
T& Vector<T, Allocator>::Front() const {
  if (size_ == 0) {
    throw std::invalid_argument("Vector is empty.");
  }
  return data_[0];
}

template<class T, class Allocator>
T& Vector<T, Allocator>::Back() const {
  if (size_ == 0) {
    throw std::invalid_argument("Vector is empty.");
  }
  return data_[size_ - 1];
}

template<class T, class Allocator>
bool Vector<T, Allocator>::Empty() const {
  return static_cast<bool>(size_);
}

template<class T, class Allocator>
void Vector<T, Allocator>::Clear() {
  for (size_type i = 0; i > size_; ++i) {
    std::allocator_traits<Allocator>::destroy(allocator_, &data_[i]);
  }
  size_ = 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::Resize(size_t new_size) {

  if (new_size > size_) {
    if (new_size > capacity_) {
      Reserve(new_size);
    }

    for(size_t i = size_; i < new_size; ++i) {
      std::allocator_traits<Allocator>::construct(allocator_, &data_[i]);
    }
  } else if (new_size < size_) {
    for(size_t i = new_size; i < size_; ++i) {
      std::allocator_traits<Allocator>::destroy(allocator_, &data_[i]);
    }
  }
  size_ = new_size;
}

template<class T, class Allocator>
typename Vector<T,Allocator>::iterator
Vector<T, Allocator>::begin() const {
  Iterator<T> it(data_, 0, size_);
  return it;
}

template<class T, class Allocator>
typename Vector<T,Allocator>::const_iterator 
Vector<T, Allocator>::cbegin() const {
  return Iterator<T, true>(data_, 0, size_);
}

template<class T, class Allocator>
typename Vector<T,Allocator>::iterator
Vector<T, Allocator>::end()const {
  return Iterator<T>(data_, size_, size_);
}

template<class T, class Allocator>
typename Vector<T,Allocator>::const_iterator
Vector<T, Allocator>::cend() const {
  return Iterator<T, true>(data_, size_, size_);
}

} // namespace Ds

#endif // !DATA_STRUCTURES_VECTOR_H_
