#include "ListBase.hpp"

void ListBase::PushFront (Link* new_elem)
{
	if (size == 0)
	{
			new_elem->next = fictive;
			new_elem->prev = NULL;
			head = new_elem;
			tail = new_elem;
	}
	else
	{
			head->prev = new_elem;
			new_elem->next = head;
			new_elem->prev = NULL;
			head = new_elem;
	}

	size++;
}

void ListBase::PushBack (Link* new_elem)
{
	switch (size)
	{
		case 0:
				new_elem->prev = NULL;
				new_elem->next = fictive;
				head = new_elem;
				tail = new_elem;
				break;

		case 1:
				head->next = new_elem;
				tail = new_elem;
				new_elem->prev = head;
				new_elem->next = fictive;
				break;

		default:
				tail->next = new_elem;
				new_elem->prev = tail;
				new_elem->next = fictive;
				tail = new_elem;
				break;
	}

	size++;
}


Link* ListBase::PopFront ()
{
	Link* target = head;
	
	head = head->next;

	head->prev = NULL;

	if (target == tail)
	{
		tail = head;
	}

	size--;

	return target;
}

Link* ListBase::PopBack ()
{
	assert (size > 0);

	Link* target = tail;

	if (size > 1)
	{
		tail = tail->prev;

		tail->next = fictive;
	}
	else
	{
		head = fictive;

		tail = fictive;
	}

	size--;

	return target;
}

void ListBase::Clear ()
{
	while (size > 0)
	{
		delete (PopFront ());
	}

	assert (size == 0);
}



ListBaseIter::ListBaseIter (ListBase& list)
{
	cur_list = &list;
	cur_elem = list.head;
}


void ListBaseIter::SetInBegin ()
{
	cur_elem = cur_list->head;
}

void ListBaseIter::SetInEnd ()
{
	cur_elem = cur_list->fictive;
}


ListBaseIter* ListBaseIter::operator++ ()
{
	if (cur_elem)
	{
		cur_elem = cur_elem->next;
	}

	return this;
}

ListBaseIter* ListBaseIter::operator-- ()
{
	if (cur_elem)
	{
		cur_elem = cur_elem->prev;
	}

	return this;
}

Link* ListBaseIter::operator* ()
{
	return cur_elem;
}


bool ListBaseIter::operator== (ListBaseIter b)
{
	return ((*this).cur_elem == b.cur_elem) && ((*this).cur_list == b.cur_list);
}

bool ListBaseIter::operator!= (ListBaseIter b)
{
	return ((*this).cur_elem != b.cur_elem) || ((*this).cur_list != b.cur_list);
}



ListBaseIter* ListBase::Remove (ListBaseIter* elem_iter)
{
	Link* elem = *(*elem_iter);

	if (elem == head)
	{
		PopFront ();
	}
	else if (elem == tail)
	{
		PopBack ();
	}
	else
	{		
		elem->prev->next = elem->next;

		elem->next->prev = elem->prev;
		
		size--;

		delete elem;
	}

	return ++(*elem_iter);
}