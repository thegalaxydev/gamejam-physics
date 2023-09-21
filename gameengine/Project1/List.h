#pragma once
#include <forward_list>

namespace GameEngine
{
	template<typename T>
	class List
	{
	public:
		List<T>() { m_list = std::forward_list<T>(); }

		void add(T item);
		void remove(T item);
		void clear();

		auto begin();
		auto end();

		bool isEmpty(); 
	private:
		std::forward_list<T> m_list;
	};

	template<typename T>
	inline void List<T>::add(T item)
	{
		m_list.push_front(item);
	}

	template<typename T>
	inline void List<T>::remove(T item)
	{
		m_list.remove(item);
	}

	template<typename T>
	inline void List<T>::clear()
	{
		m_list.clear();
	}

	template<typename T>
	inline auto List<T>::begin()
	{
		return m_list.begin();
	}

	template<typename T>
	inline auto List<T>::end()
	{
		return m_list.end();
	}

	template<typename T>
	inline bool List<T>::isEmpty()
	{
		return m_list.empty();
	}


}
