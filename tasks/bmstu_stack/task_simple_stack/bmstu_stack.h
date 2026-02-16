#pragma once

#include <exception>
#include <utility>

namespace bmstu
{
template <typename T>
class stack
{
   public:
	stack() : data_(nullptr), size_(0), capacity_(0) {}

	bool empty() const noexcept { return size_ == 0; }

	size_t size() const noexcept { return size_; }

	~stack()
	{
		clear();
		::operator delete(data_);
	}

	template <typename... Args>
	void emplace(Args&&... args)
	{
		if (size_ == capacity_)
		{
			reserve_more();
		}
		new (data_ + size_) T(std::forward<Args>(args)...);
		++size_;
	}

	void push(const T& value) { emplace(value); }

	void push(T&& value) { emplace(std::move(value)); }

	void clear() noexcept
	{
		while (size_ > 0)
		{
			--size_;
			(data_ + size_)->~T();
		}
	}

	void pop()
	{
		if (empty())
			throw std::underflow_error("Stack is empty!");

		--size_;
		(data_ + size_)->~T();
	}

	T& top()
	{
		if (empty())
			throw std::underflow_error("Stack is empty!");
		return data_[size_ - 1];
	}

	const T& top() const
	{
		if (empty())
			throw std::underflow_error("Stack is empty!");
		return data_[size_ - 1];
	}

   private:
	T* data_;
	size_t size_;
	size_t capacity_;

	void reserve_more()
	{
		size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
		T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

		for (size_t i = 0; i < size_; ++i)
		{
			new (new_data + i) T(std::move(data_[i]));
			(data_ + i)->~T();
		}

		::operator delete(data_);
		data_ = new_data;
		capacity_ = new_capacity;
	}
};
}  // namespace bmstu