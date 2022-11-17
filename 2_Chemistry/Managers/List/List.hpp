#ifndef LIST_HPP
#define LIST_HPP

#include <cstdio>
#include <cstddef>
#include <cassert>



template <class T> class ListIter;


template <class T>
struct TLink : public Link
{
	T elem;

	TLink (const T& init_elem) : elem (init_elem) {}
};



template <class T>
class List : private ListBase
{

public:


	/*** Allocator ***/

	List () : ListBase () {}


	/*** Members ***/

	bool Empty () { return ListBase::Size () == 0; }

	size_t Size () { return ListBase::Size (); }

	void PushFront (const T& new_elem) { ListBase::PushFront (new TLink<T> (new_elem)); }
	void PushBack  (const T& new_elem) { ListBase::PushBack  (new TLink<T> (new_elem)); }

	T PopFront ();
	T PopBack  ();

	ListIter<T> Remove (ListIter<T> elem_iter) { return *((ListIter<T>*) ListBase::Remove (&elem_iter)); }

	void Clear () {ListBase::Clear (); }


	/*** Iterators ***/

	ListIter<T> Begin ()
	{
		ListIter<T> begin = ListIter<T> (*this);

		begin.SetInBegin ();

		return begin;
	}

	ListIter<T> End ()
	{
		ListIter<T> end = ListIter<T> (*this);

		end.SetInEnd ();

		return end;
	}


	friend class ListIter<T>;
};



/*** Members ***/

template <class T>
T List<T>::PopFront ()
{
	TLink<T>* front = (TLink<T>*) ListBase::PopFront ();

	T elem = front->elem;

	delete front;

	return elem;
}

template <class T>
T List<T>::PopBack ()
{
	TLink<T>* back = (TLink<T>*) ListBase::PopBack ();

	T elem = back->elem;

	delete back;

	return elem;
}



template <class T>
class ListIter : public ListBaseIter
{

public:

	/*** Allocator ***/

	ListIter (List<T>& list) : ListBaseIter (list) {}


	/*** Members ***/

	void SetInBegin () { ListBaseIter::SetInBegin (); };
	void SetInEnd   () { ListBaseIter::SetInEnd   (); };


	/*** Operators ***/

	ListIter<T>* operator++ ();	// prefix increment
	ListIter<T>* operator-- ();	// prefix decrement

	T operator* ();

	bool operator== (ListIter<T> b) { return ListBaseIter::operator== (b); } ;

	bool operator!= (ListIter<T> b) { return ListBaseIter::operator!= (b); } ;
};


template <class T>
ListIter<T>* ListIter<T>::operator++ ()
{
	ListIter<T>* iter = (ListIter<T>*) ListBaseIter::operator++ ();

	return iter;
}


template <class T>
ListIter<T>* ListIter<T>::operator-- ()
{
	ListIter<T>* iter = (ListIter<T>*) ListBaseIter::operator-- ();

	return iter;
}


template <class T>
T ListIter<T>::operator* ()
{
	TLink<T>* link = (TLink<T>*) ListBaseIter::operator* ();

	return link->elem;
}



#endif