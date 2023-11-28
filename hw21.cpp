#include <iostream>
using namespace std;

class SinglyLinkedList
{
public:
	struct Node
	{
		int data = 0;
		Node* next = nullptr;
	};

private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int count = 0;

	void Swap(Node* a, Node* b)
	{
		int temp = a->data;
		a->data = b->data;
		b->data = temp;
	}

	void SwapByIndex(int index1, int index2)
	{
		Node* node1 = GetNodeAt(index1);
		Node* node2 = GetNodeAt(index2);

		if (node1 != nullptr && node2 != nullptr)
		{
			Swap(node1, node2);
		}
	}

	Node* GetNodeAt(int index)
	{
		if (index < 0 || index >= count)
		{
			return nullptr; 
		}

		Node* current = head;
		for (int i = 0; i < index; ++i)
		{
			current = current->next;
		}

		return current;
	}

public:
	void AddToHead(int data)
	{
		Node* newElem = new Node();
		newElem->data = data;
		newElem->next = head;
		if (head == nullptr)
		{
			tail = newElem;
		}
		head = newElem;
		count++;
	}

	void AddToTail(int data)
	{
		Node* newElem = new Node();
		newElem->data = data;
		if (tail == nullptr)
		{
			head = newElem;
		}
		else
		{
			tail->next = newElem;
		}
		tail = newElem;
		count++;
	}

	void InsertInto(int data, int position)
	{
		if (position >= count)
		{
			AddToTail(data);
			return;
		}
		else if (position <= 0)
		{
			AddToHead(data);
			return;
		}

		Node* newElem = new Node();
		newElem->data = data;
		int i = 1;
		Node* beforeNew = head;
		while (i++ != position)
		{
			beforeNew = beforeNew->next;
		}
		newElem->next = beforeNew->next;
		beforeNew->next = newElem;

		count++;
	}

	void DeleteFromHead()
	{
		if (count == 0)
		{
			// cout << "Empty list!\n";
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
		count--;
		if (head == nullptr)
		{
			tail = nullptr;
		}
	}

	void DeleteFromTail()
	{
		if (count == 0) {
			// cout << "Empty list!\n";
			return;
		}
		DeleteByIndex(count - 1);
	}

	void DeleteByIndex(int position)
	{
		if (position <= 0)
		{
			DeleteFromHead();
			return;
		}

		if (position >= count)
		{
			position = count - 1;
		}

		int i = 1;
		Node* beforeDel = head;
		while (i++ != position)
		{
			beforeDel = beforeDel->next;
		}
		Node* sacrifice = beforeDel->next;
		beforeDel->next = sacrifice->next;
		delete sacrifice;
		count--;
		if (beforeDel->next == nullptr)
		{
			tail = beforeDel;
		}
	}

	void Clear()
	{
		while (head != nullptr)
		{
			DeleteFromHead();
		}
	}

	void Print() const
	{
		if (count == 0)
		{
			cout << "Empty list!\n";
			return;
		}
		Node* current = head;
		while (current != nullptr)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	int GetCount() const
	{
		return count;
	}

	int IndexOf(int data) const
	{
		if (count == 0)
		{
			// cout << "Empty list!\n";
			return -1;
		}
		Node* temp = head;
		int i = 0;
		while (i < count)
		{
			if (data == temp->data)
			{
				return i;
			}
			i++;
			temp = temp->next;
		}

		return -1;
	}

	bool IsEmpty() const
	{
		if (count == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int LastIndexOf(int data) const
	{
		if (count == 0)
		{
			return -1;
		}

		Node* current = head;
		int lastFoundIndex = -1;
		int currentIndex = 0;

		while (current != nullptr)
		{
			if (current->data == data)
			{
				lastFoundIndex = currentIndex;
			}

			currentIndex++;
			current = current->next;
		}

		return lastFoundIndex;
	}

	void Reverse()
	{

		Node* prev = nullptr;
		Node* current = head;
		Node* next = nullptr;

		tail = head; 

		while (current != nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		head = prev; 
	}

	void SortAsc()
	{
		if (count <= 1)
		{
			return; 
		}

		bool swapped;
		Node* current;
		Node* next = nullptr;

		do
		{
			swapped = false;
			current = head;

			while (current->next != next)
			{
				if (current->data > current->next->data)
				{
					Swap(current, current->next);
					swapped = true;
				}
				current = current->next;
			}
			next = current;

		} while (swapped);
	}

	void Shuffle()
	{

		srand(static_cast<unsigned int>(time(nullptr)));

		for (int i = count - 1; i > 0; --i)
		{
			int j = rand() % (i + 1); 
			SwapByIndex(i, j);
		}
	}

	int* ToArray() const
	{
		if (count == 0)
		{
			return nullptr; 
		}

		int* array = new int[count];
		Node* current = head;

		for (int i = 0; i < count; ++i)
		{
			array[i] = current->data;
			current = current->next;
		}

		return array;
	}

	int operator[](int index) const
	{
		if (index < 0 || index >= count)
		{
			
			cout << "Error: Index out of bounds.\n";

		}

		Node* current = head;
		for (int i = 0; i < index; ++i)
		{
			current = current->next;
		}

		return current->data;
	}

	int& operator[](int index)
	{
		if (index < 0 || index >= count)
		{
			
			cout << "Error: Index out of bounds.\n";
			return head->data;
		}

		Node* current = head;
		for (int i = 0; i < index; ++i)
		{
			current = current->next;
		}

		return current->data;
	}

	friend ostream& operator<<(ostream& os, const SinglyLinkedList& list)
	{
		if (list.count == 0)
		{
			os << "Empty list!";
			return os;
		}

		Node* current = list.head;
		while (current != nullptr)
		{
			os << current->data << " ";
			current = current->next;
		}

		return os;
	}

};

ostream& operator<<(ostream& os, const SinglyLinkedList& list);

int main()
{
	SinglyLinkedList sll;

	// вставка в конец списка
	sll.AddToTail(10);
	sll.AddToTail(20);
	sll.AddToTail(30);
	sll.AddToTail(40);
	sll.Print();

	// вставка в начало списка
	sll.AddToHead(50);
	sll.AddToHead(60);
	sll.AddToHead(70);
	sll.AddToHead(80);
	sll.Print();

	// количество элементов, поиск элементов
	cout << "count: " << sll.GetCount() << "\n";
	cout << "index of 70: " << sll.IndexOf(70) << ", index of 90: " << sll.IndexOf(90) << "\n";

	// вставка по позиции
	sll.InsertInto(-1, -1);
	sll.Print();
	sll.InsertInto(2, 2);
	sll.Print();
	sll.InsertInto(22, 22);
	sll.Print();

	// удаление по указанному индексу
	sll.DeleteByIndex(0);
	sll.DeleteByIndex(1);
	sll.DeleteByIndex(2);
	sll.Print();

	cout << "Is the list empty?\n " << sll.IsEmpty() << "\n";

	int lastIndex = sll.LastIndexOf(30);
	cout << "Last index of 30: " << lastIndex << "\n";

	cout << "Original list: ";
	sll.Print();

	sll.Reverse();
	cout << "Reversed list: ";
	sll.Print();

	sll.SortAsc();
	cout << "Sorted list (ascending): ";
	sll.Print();

	sll.Shuffle();
	cout << "Shuffled list: ";
	sll.Print();

	int* array = sll.ToArray();
	cout << "List converted to array: ";
	for (int i = 0; i < sll.GetCount(); ++i)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	delete[] array; 

	cout << "Element at index 2: " << sll[2] << endl;

	sll[2] = 100; 
	cout << "Modified list: ";
	sll.Print();

	cout << "List: " << sll << endl;


}