#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector
{
private:
	T *data;
	size_t size_;
	size_t capacity_;

public:
	/**
	 * TODO
	 * a type for actions of the elements of a vector, and you should write
	 *   a class named const_iterator with same interfaces.
	 */
	/**
	 * you can see RandomAccessIterator at CppReference for help.
	 */
	class const_iterator;
	class iterator
	{
	// The following code is written for the C++ type_traits library.
	// Type traits is a C++ feature for describing certain properties of a type.
	// For instance, for an iterator, iterator::value_type is the type that the
	// iterator points to.
	// STL algorithms and containers may use these type_traits (e.g. the following
	// typedef) to work properly. In particular, without the following code,
	// @code{std::sort(iter, iter1);} would not compile.
	// See these websites for more information:
	// https://en.cppreference.com/w/cpp/header/type_traits
	// About value_type: https://blog.csdn.net/u014299153/article/details/72419713
	// About iterator_category: https://en.cppreference.com/w/cpp/iterator
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::output_iterator_tag;

	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		vector<T> *owner;
		size_t index;

	public:
		iterator(vector<T> *v, size_t i) : owner(v), index(i) {}
		/**
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		iterator operator+(const int &n) const
		{
			//TODO
			return iterator(owner, index + n);
		}
		iterator operator-(const int &n) const
		{
			//TODO
			return iterator(owner, index - n);
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const
		{
			//TODO
			if (owner != rhs.owner)
				throw invalid_iterator();
			return static_cast<int>(index) - static_cast<int>(rhs.index);
		}
		iterator& operator+=(const int &n)
		{
			//TODO
			index += n;
			return *this;
		}
		iterator& operator-=(const int &n)
		{
			//TODO
			index -= n;
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			index++;
			return iterator(owner, index - 1);
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {return ((*this) += 1);}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			index--;
			return iterator(owner, index + 1);
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {return ((*this) -= 1);}
		/**
		 * TODO *it
		 */
		T& operator*() const{return owner->data[index];}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const iterator &rhs) const {
			return owner == rhs.owner && index == rhs.index;
		}
		bool operator==(const const_iterator &rhs) const {
			return owner == rhs.owner && index == rhs.index;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {return !(*this == rhs);}
		bool operator!=(const const_iterator &rhs) const {return !(*this == rhs);}

	friend class vector<T>;
	};
	/**
	 * TODO
	 * has same function as iterator, just for a const object.
	 */
	class const_iterator
	{
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::output_iterator_tag;

	private:
		/*TODO*/
		const vector<T> *owner;
		size_t index;

		friend class iterator;

	public:
		const_iterator(const vector<T> *v, size_t i) : owner(v), index(i) {}
		
		const_iterator(const iterator &other)
        	: owner(other.owner), index(other.index) {}
		/**
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		const_iterator operator+(const int &n) const
		{
			//TODO
			return const_iterator(owner, index + n);
		}
		const_iterator operator-(const int &n) const
		{
			//TODO
			return const_iterator(owner, index - n);
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const const_iterator &rhs) const
		{
			//TODO
			if (owner != rhs.owner)
				throw invalid_iterator();
			return static_cast<int>(index) - static_cast<int>(rhs.index);
		}
		const_iterator& operator+=(const int &n)
		{
			//TODO
			index += n;
			return *this;
		}
		const_iterator& operator-=(const int &n)
		{
			//TODO
			index -= n;
			return *this;
		}
		/**
		 * TODO iter++
		 */
		const_iterator operator++(int) {
			index++;
			return const_iterator(owner, index - 1);
		}
		/**
		 * TODO ++iter
		 */
		const_iterator& operator++() {return ((*this) += 1);}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			index--;
			return const_iterator(owner, index + 1);
		}
		/**
		 * TODO --iter
		 */
		const_iterator& operator--() {return ((*this) -= 1);}
		/**
		 * TODO *it
		 */
		const T& operator*() const{return owner->data[index];}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const iterator &rhs) const {
			return owner == rhs.owner && index == rhs.index;
		}
		bool operator==(const const_iterator &rhs) const {
			return owner == rhs.owner && index == rhs.index;
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {return !(*this == rhs);}
		bool operator!=(const const_iterator &rhs) const {return !(*this == rhs);}

	};
	/**
	 * TODO Constructs
	 * At least two: default constructor, copy constructor
	 */
	vector() {
		data = static_cast<T *>(::operator new(4 * sizeof(T)));
		size_ = 0;
		capacity_ = 4;
	}
	vector(const vector &other) {
		size_ = other.size_;
		capacity_ = other.capacity_;
		data = static_cast<T *>(::operator new(capacity_ * sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			new (data + i) T(other.data[i]);
		}
	}
	/**
	 * TODO Destructor
	 */
	~vector() {
		for (size_t i = 0; i < size_; ++i) {
        	data[i].~T();
    	}
    	::operator delete(data);
	}
	/**
	 * TODO Assignment operator
	 */
	vector &operator=(const vector &other) {
		if (this == &other) return *this;
		
		for (size_t i = 0; i < size_; ++i) {
        	data[i].~T();
    	}
    	::operator delete(data);
		size_ = other.size_;
		capacity_ = other.capacity_;
		data = static_cast<T *>(::operator new(capacity_ * sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			new (data + i) T(other.data[i]);
		}
		return *this;
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 */
	T & at(const size_t &pos) {
		if (pos < 0 || pos >= size_) {
			throw index_out_of_bound();
		}
		return data[pos];
	}
	const T & at(const size_t &pos) const {
		if (pos < 0 || pos >= size_) {
			throw index_out_of_bound();
		}
		return data[pos];
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 * !!! Pay attentions
	 *   In STL this operator does not check the boundary but I want you to do.
	 */
	T & operator[](const size_t &pos) {
		if (pos < 0 || pos >= size_) {
			throw index_out_of_bound();
		}
		return data[pos];
	}
	const T & operator[](const size_t &pos) const {
		if (pos < 0 || pos >= size_) {
			throw index_out_of_bound();
		}
		return data[pos];
	}
	/**
	 * access the first element.
	 * throw container_is_empty if size == 0
	 */
	const T & front() const {
		if (size_ == 0) 
			throw container_is_empty();
		return data[0];
	}
	/**
	 * access the last element.
	 * throw container_is_empty if size == 0
	 */
	const T & back() const {
		if (size_ == 0)
			throw container_is_empty();
		return data[size_ - 1];
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {return iterator(this, 0);}
	const_iterator begin() const {return const_iterator(this, 0);}
	const_iterator cbegin() const {return const_iterator(this, 0);}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {return iterator(this, size_);}
	const_iterator end() const {return const_iterator(this, size_);}
	const_iterator cend() const {return const_iterator(this, size_);}
	/**
	 * checks whether the container is empty
	 */
	bool empty() const {return (size_ == 0);}
	/**
	 * returns the number of elements
	 */
	size_t size() const {return size_;}
	/**
	 * clears the contents
	 */
	void clear() {
		for (size_t i = 0; i < size_; ++i) {
        	data[i].~T();
    	}
		size_ = 0;
	}
	
	/**
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value.
	 */
	iterator insert(iterator pos, const T &value) {
		if (pos.owner != this || pos.index > size_)
        	throw invalid_iterator();
    	return insert(pos.index, value);
	}
	/**
	 * inserts value at index ind.
	 * after inserting, this->at(ind) == value
	 * returns an iterator pointing to the inserted value.
	 * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
	 */
	iterator insert(const size_t &ind, const T &value) {
		if (ind > size_)
			throw index_out_of_bound();

		T saved(value);
		if (size_ == capacity_)
			reserve(2 * capacity_);

		if (ind == size_ || size_ == 0) {
			new (data + size_) T(saved);
			size_++;
			return iterator(this, ind);
		}

		new (data + size_) T(data[size_ - 1]);
		for (size_t i = size_ - 1; i > ind; i--)
			data[i] = data[i - 1];
		data[ind] = saved;
		size_++;
		return iterator(this, ind);
	}
	/**
	 * removes the element at pos.
	 * return an iterator pointing to the following element.
	 * If the iterator pos refers the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) {
		if (pos.owner != this || pos.index >= size_)
        	throw invalid_iterator();
    	return erase(pos.index);
	}
	/**
	 * removes the element with index ind.
	 * return an iterator pointing to the following element.
	 * throw index_out_of_bound if ind >= size
	 */
	iterator erase(const size_t &ind) {
		if (ind >= size_)
			throw index_out_of_bound();
		
		for (size_t i = ind; i < size_ - 1; i++) {
			data[i] = data[i + 1];
		}
		--size_;
		data[size_].~T();
		return iterator(this, ind);
	}
	/**
	 * adds an element to the end.
	 */
	void push_back(const T &value) {
		T saved(value);
		if (size_ == capacity_)
			reserve(2 * capacity_);
		new (data + size_) T(saved);
		size_++;
	}
	/**
	 * remove the last element from the end.
	 * throw container_is_empty if size() == 0
	 */
	void pop_back() {
		if (size_ == 0)
        	throw container_is_empty();
    	--size_;
    	data[size_].~T();
	}

private:
	void reserve(size_t newcapacity_) {
		T *newdata = static_cast<T *>(::operator new(newcapacity_ * sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			new (newdata + i) T(data[i]);
		}
		for (size_t i = 0; i < size_; ++i) {
        	data[i].~T();
    	}
		::operator delete(data);
		data = newdata;
		capacity_ = newcapacity_;
	}
};


}

#endif
