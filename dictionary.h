#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <algorithm>
#include <string>


namespace Containers
{
	class Node
	{
	public:
		std::string key;
		std::string item;
		Node* next;

		Node() {
			key = "";
			item = "";
			next = NULL;
		}

	};

	template <typename T>
	class Dictionary
	{
	public:

		using Key = T;
		using Item = T;


		Node* head, * tail;

		/*Best, average and worst cases have a time complexity of constant O(1) as it has a running time independant of other variables.*/
		Dictionary();

		/*Best, average and worst cases have a time complexity of constant O(1) as it has a running time independant of other variables.*/
		//How to test if this is working or not? If there is a memory leak or not?
		~Dictionary();

		/*At best has a time complexity of constant O(1) if the list only exists of 1 node.Average and worst cases have a time complexity of 
		linear O(n) as it must traverse the entire list to make a deep copy.*/
		Dictionary(const Dictionary& original);

		/*Best has a time complexity of constant O(1) if the list only exists of 1 node.
		Average and worst cases have a time complexity of linear O(n) as it has to traverse the entire list to make a deep copy.*/
		Dictionary& operator = (const Dictionary& original) //copy assignment operator
		{
			Dictionary temp(original); //make use of copy constructor to copy object
			std::swap(temp.head, head); //swap head of copy for head of source
			return *this;
		}

		/*At best has a time complexity of constant O(1) if the list only exists of 1 node to be moved. Average and worst cases have a time 
		complexity of linear O(n) as it must traverse the entire list to move it before freeing memory from the original..*/
		Dictionary(Dictionary&& original);

		/*Best has a time complexity of constant O(1) if the list only exists of 1 node to be moved.
		Average and worst cases have a time complexity of linear O(n) as it has to traverse the entire list to move it before freeing memory
		from the original.*/
		//declare noexcept??
		Dictionary& operator = (Dictionary&& original)//move assignment operator
		{
			if (this != &original)
			{
				//empties existing list without calling destructor
				clearList();

				head = original.head;
				original.head = nullptr;
				tail = original.tail;
				original.tail = nullptr;
			}
			return *this;
		}



		/*Best case is of O(1) constant complexity, if the list is empty.
		Average and worst cases are of O(n) linear complexity as function has to traverse the entire list to find if k already exists.*/
		bool insert(Key k, Item i);

		/*Best case is of constant complexity, O(1), if the key to be looked up exists in the first node of the list.
		Average and worst cases are of linear complexity O(n), if the key exists in the middle of the list or if the key does not exist.*/
		Item* lookup(Key k);


		/*Best case is of O(1) constant complexity, if the key exists and is at the start of the list.
		Average and worst cases are of O(n²) quadratic complexity as function has to traverse the entire list to find if k already exists,
		and then traverse the list again to find and remove the key.*/
		bool remove(Key k);

		void removeIf(Key k, T isKeyPresent);

		/*Best case is of O(1) constant complexity, if the list is empty.
		Average and worst cases are of O(n) linear complexity as function has to traverse the entire list to find if k exists.*/
		bool isKeyPresent(Key k);

		/*Best case is of O(1) constant complexity, if the key is at the start of the list.
		Average and worst cases are of O(n) linear complexity if function has to traverse the entire list to find k.*/
		void deleteKey(Key k);

		/*Best case is O(1) if the list consist of only 1 node.
		Average and worst cases are of linear complexity O(n) if the list consists of a linear growth in number of nodes.*/
		void clearList();
	};

	template<typename T>
	Dictionary<T>::Dictionary()
	{
		head = nullptr;
		tail = nullptr;
	}

	template<typename T>
	Dictionary<T>::~Dictionary()//RAII methodology
	{
		Node* current = head;
		while (current != nullptr)
		{
			Node* next = current->next;
			delete current; 
			current = next;
		}
		head = nullptr;
	}

	template<typename T>
	Dictionary<T>::Dictionary(const Dictionary& original) //copy constructor
	{
		head = nullptr;
		tail = nullptr;

		Node* ptr = original.head;

		while (ptr != nullptr)
		{
			insert(ptr->key, ptr->item);
			ptr = ptr->next;
		}
	}

	template<typename T>
	Dictionary<T>::Dictionary(Dictionary&& original)//move constructor
	{
		head = nullptr;
		tail = nullptr;

		Node* current = original.head;

		while (current != nullptr)
		{
			insert(current->key, current->item);
			current = current->next;
		}
		original.head = nullptr;
		original.tail = nullptr;
	}


	template<typename T>
	bool Dictionary<T>::insert(Key k, Item i)
	{
		Node* temp = new Node; //create new node and pass values to Node data members
		temp->key = k;
		temp->item = i;
		temp->next = nullptr;

		Node* kTemp = new Node;
		kTemp = head;

		bool keyAbsent = true;

		while (kTemp != nullptr) //Used to check if k is absent
		{
			if (kTemp->key == k)
			{
				keyAbsent = false;
				break;
			}
			else
			{
				kTemp = kTemp->next;
			}
		}

		if (keyAbsent == true) //if key was not already present in list
		{
			if (head == nullptr) //If head of list is empty then new node is head and tail
			{
				head = temp;
				tail = temp;
			}
			else
			{
				tail->next = temp;
				tail = temp;
			}
		}

		return keyAbsent;
	}

	template<typename T>
	T* Dictionary<T>::lookup(Key k)
	{
		Node* temp = new Node;
		temp = head;
		Item item;

		Item* i = new Item;

		while (temp != nullptr)
		{
			if (temp->key == k)
			{
				i = &temp->item;
				break;
			}
			else if (temp->next == nullptr)
			{
				i = nullptr;
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		return i;
	}

	template<typename T>
	bool Dictionary<T>::remove(Key k)
	{
		bool keyPresent = false;

		keyPresent = isKeyPresent(k);


		if (keyPresent == true)//Runs while loop to find and remove k only if key is present in list
		{
			deleteKey(k);
		}
		return keyPresent;
	}

	template<typename T>
	void Dictionary<T>::removeIf(Key k, T isKeyPresent)
	{
		if (isKeyPresent(k) == true)
		{
			deleteKey(k);
		}
	}

	template<typename T>
	bool Dictionary<T>::isKeyPresent(Key k)
	{
		Node* kTemp = new Node;
		kTemp = head;

		bool keyPresent = false;

		while (kTemp != nullptr) //Used to check if k is present in list
		{
			if (kTemp->key == k)
			{
				keyPresent = true;
				break;
			}
			else
			{
				kTemp = kTemp->next;
			}
		}

		return keyPresent;
	}

	template<typename T>
	void Dictionary<T>::deleteKey(Key k)
	{
		Node* current = new Node;
		Node* previous = new Node;
		Node* temp = new Node;

		current = head;
		while (current != nullptr)
		{
			if (current->key == k)
			{
				temp = current;

				previous->next = current->next;

				delete temp;
				break;
			}
			else
			{
				previous = current;
				current = current->next;
			}
		}
	}

	template<typename T>
	void Dictionary<T>::clearList()
	{
		Node* current = head;
		Node* next;

		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}

		head = NULL;
	}
}

#endif