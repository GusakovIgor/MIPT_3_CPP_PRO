#ifndef LIST_BASE_HPP
#define LIST_BASE_HPP


#include <cstdio>
#include <cstddef>
#include <cassert>


struct Link
{
	Link* next;
	Link* prev;
	
	Link ()
	{
		next = NULL;
	}

	Link (Link* init_next, Link* init_prev)
	{
		next = init_next;
		prev = init_prev;
	}
};



class ListBaseIter;



class ListBase
{

private:

	Link* head;
	Link* tail;

	Link* fictive;

	size_t size;


public:

	ListBase ()
	{
		fictive = new Link ();
		head = fictive;
		tail = fictive;

		size = 0;
	}


	size_t Size ()
	{
		return size;
	}


	/*** Modification ***/

	void PushFront (Link* new_elem);	// O(1)

	void PushBack  (Link* new_elem);	// O(1)



	Link* PopFront ();	// O(1)
	
	Link* PopBack  ();	// O(n)


	ListBaseIter* Remove (ListBaseIter* elem_iter);

	void Clear ();


	/*** Iteration ***/

	friend class ListBaseIter;
};





class ListBaseIter
{

private:

	Link* cur_elem;
	ListBase* cur_list;


public:

	ListBaseIter ()
	{
		cur_elem = NULL;
		cur_list = NULL;
	}

	ListBaseIter (ListBase& list);



	void SetInBegin ();
	void SetInEnd   ();

	
	ListBaseIter* operator++ ();

	ListBaseIter* operator-- ();

	Link* operator* ();

	bool operator== (ListBaseIter b);

	bool operator!= (ListBaseIter b);
};



#endif