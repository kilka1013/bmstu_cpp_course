#pragma once
#include <exception>
#include <utility>

namespace bmstu
{

template <typename T>
class stack
{
   private:
	struct Node
	{
		T value;
		Node* next;

		template <typename... Args>
		Node(Node* nextNode, Args&&... args)
			: value(std::forward<Args>(args)...), next(nextNode)
		{
		}
	};

	Node* head;
	size_t sz;

   public:
	stack() : head(nullptr), sz(0) {}

	~stack() { clear(); }

	bool empty() const { return sz == 0; }

	size_t size() const { return sz; }

	template <typename... Args>
	void emplace(Args&&... args)
	{
		head = new Node(head, std::forward<Args>(args)...);
		++sz;
	}

	void push(const T& value)
	{
		head = new Node(head, value);
		++sz;
	}

	void push(T&& value)
	{
		head = new Node(head, std::move(value));
		++sz;
	}

	void pop()
	{
		if (empty())
			throw std::underflow_error("stack is empty");

		Node* temp = head;
		head = head->next;
		delete temp;
		--sz;
	}

	T& top()
	{
		if (empty())
			throw std::underflow_error("stack is empty");

		return head->value;
	}

	const T& top() const
	{
		if (empty())
			throw std::underflow_error("stack is empty");

		return head->value;
	}

	void clear()
	{
		while (!empty())
		{
			pop();
		}
	}
};

}  // namespace bmstu