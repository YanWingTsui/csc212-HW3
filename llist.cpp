#include "llist.h"

namespace nodespace{
	
void LList::append(const node::value_type& entry)
{
	if(list_length == 0)
	{
		nodespace::mode*temp = new node(entry, NULL);
		head_ptr = temp;
		tail_ptr = temp;
		list_length++;
	}
		
	else if(list_length == 1)
	{
		nodespace::node* temp = new node(entry, NULL);
		head_ptr->set_link(temp);
		tail_ptr = temp;
		list_length ++;
	}
	else
	{
		nodespace::node* temp = new node(entry);
		tail_ptr->set_link(temp);
		tail_ptr = tail_ptr->link();
		list_length ++;
	}
};
	
void LList::insert(std::size_t position, const node::value_type& entry)
{
	if(position >list_length || position < 0)
		throw std::out_of_range(std::string("The position is not in the range!!"));
	if(position == 0)
	{
		nodespace::node* temp = new node(entry, head_ptr);
		head_ptr = temp;
		list_length ++;
	}
	else if(position == list_length)
		this->append(entry);
	else{
		int p = 0;
		nodespace::node* prev;
		nodespace::node* pointer;
		for(pointer = head_ptr; pointer != NULL; pointer = pointer->link()){
			if(p == position){
				nodespace::node* temp = new node(entry, pointer);
				prev->set_link(temp);
				list_length ++;
			}
			p++;
			prev = pointer;
		}
	}
};   

	//find first occurrence
const node* LList::search(const node::value_type& target)
{
	nodespace::node* result = NULL;
	nodespace::node* pointer;
	for(pointer = head_ptr; pointer != NULL; pointer = pointer->link())
	{
		if(pointer->data() == target)
		{
			result = pointer;
			break;
		}
	}
	return result;
};
	
const node* LList::locate(std::size_t position)
{
	int p = 0;
	if(position < 0 || position > list_length)
		return NULL;
	nodespace::node* pointer;
	for(pointer = head_ptr; pointer != NULL; pointer = pointer->link())
	{
		if(p == position)
			return pointer;
		p++;
	}
};

	//remove by value, remove all
bool LList::remove(const node::value_type& target)
{
	bool a = false;
	nodespace::node* prev;
	nodespace::node* pointer;
	for(pointer = head_ptr; pointer != NULL; pointer = pointer->link())
	{
		if(pointer->data() == target)
		{
			a = true;
			if(pointer == head_ptr)
			{
				head_ptr = head_ptr->link();
				list_length --;
			}	
			else if(pointer == tail_ptr)
			{
				tail_ptr = prev;
				tail_ptr->set_link(NULL);
				list_length --;
			}	
			else{
				prev->set_link(pointer->link());
				list_length --;
			}
			break;
		}
		prev = pointer;
	}
	return a;
};

void LList::clear()
{
	tail_ptr = NULL;
	head_ptr = NULL;
	list_length = 0;
};

	//returns new list
LList* LList::copy()
{
	nodespace::LList* b = new LList();
	nodespace::node* pointer;
	for(pointer = head_ptr; pointer != NULL; pointer = pointer->link())
		b->append(pointer->data());
	return b;
};

//additional functions to index into list
node* LList::operator[] (size_t ind)
{
	if(ind >= list_length || ind <0)
		throw std::out_of_range(std::string("The position is not in the range!!"));
	int p = 0;
	nodespace::node* pointer;
	for(pointer = head_ptr; pointer != NULL; pointer = pointer->link()){
		if(p == ind)
			return pointer;
		p++;
	}
};
const std::size_t LList::getLength()
{
	return list_length;
};

void LList::functionIMadeForPrinting(){
	if(list_length == 0)
		std::cout << "empty" << std::endl;
	else{
		node* pointer;
		for(pointer = head_ptr; pointer != NULL; pointer = pointer->link()){
			std::cout << pointer->data() << std::endl;
		}		
	}
};


std::list<std::tuple<node::value_type, int>> frequency(LList data){
	std::list<std::tuple<node::value_type, int>> a;
	while(data.getLength() != 0){
		int temp1 = 1;
		node::value_type temp = data[0]->data();
		data.remove(temp);
		while(data.search(temp) != NULL){
			temp1 ++;
			data.remove(temp);
		}
		std::tuple<node::value_type, int> elements(temp,temp1);
		a.push_back(elements);
	}
	return a;
}
