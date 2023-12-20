//	LinkedBag340.cpp
//	Created by: CSC340
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "LinkedBag.h"
#include "LinkedBag.cpp"

using namespace std;

// deletes the second node in the Linked Bag
template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340()
{
	if (this->headPtr->getNext() == nullptr) return false;

	Node<ItemType>* nodeToDelete = this->headPtr->getNext();
	this->remove(nodeToDelete->getItem());

	return true;
}

// inserts the new node at the end of the Linked Bag
template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& item)
{
	Node<ItemType>* temp = this->headPtr;
	Node<ItemType>* newNode = new Node<ItemType>();

	while (temp != NULL)
	{
		if (temp->getNext() == nullptr)
		{
			temp->setNext(newNode);
			newNode->setItem(item);
			newNode->setNext(nullptr);
			this->itemCount++;
			return true;
		}
		temp = temp->getNext();
	}
	return false;
}

// counts the number of nodes in the Linked Bag iteratively.
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const
{
	int count = 0;
	Node<ItemType>* temp = this->headPtr;

	while (temp != NULL)
	{
		count++;
		temp = temp->getNext();
	}
	return count;
}

// counts the number of nodes in the Linked Bag recursively. Use 1 helper function: getCurrentSize340RecursiveHelper.
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const 
{
	if (this->headPtr == NULL) return 0;

	Node<ItemType>* temp = this->headPtr;

	return getCurrentSize340RecursiveHelper(temp);
}

// helper function for the function: getCurrentSize340Recursive
template<typename ItemType>
int  LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* node) const 
{
	if (node == nullptr) return 0;
	return getCurrentSize340RecursiveHelper(node->getNext()) + 1;
} 

// counts the number of nodes in the Linked Bag recursively without a helper function.
template<typename ItemType>
int  LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const 
{
	if (this->headPtr == NULL) return 0;

	LinkedBag<ItemType> temp = *this;
	Node<ItemType>* tempHead = temp.headPtr;

	if (temp.remove(tempHead->getItem())) return temp.getCurrentSize340RecursiveNoHelper() + 1;

	return 0;
} 

// recursively counts the number of times an entry appears in the Linked Bag. Use 1 helper function: getFrequencyOf340RecursiveHelper.
template<typename ItemType>
int  LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& item) const
{
	if (this->headPtr == NULL) return 0;

	Node<ItemType>* temp = LinkedBag<ItemType>::headPtr;

	return getFrequencyOf340RecursiveHelper(temp, item);
}

// helper function for the function: getFrequencyOf340Recursive
template<typename ItemType>
int  LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* node, const ItemType& item) const 
{
	if (node == nullptr) return 0;
	else if (node->getItem() != item) return getFrequencyOf340RecursiveHelper(node->getNext(), item);
	return getFrequencyOf340RecursiveHelper(node->getNext(), item) + 1;
} 

// recursively counts the number of times an entry appears in the Linked Bag without a helper function
template<typename ItemType>
int  LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& item) const 
{
	if (this->headPtr == NULL) return 0;
		
	LinkedBag<ItemType> temp = *this;

	if (temp.remove(item)) return temp.getFrequencyOf340RecursiveNoHelper(item) + 1;
	
	return 0;
}

// removes a random entry from the Linked Bag.
template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340()
{
	srand(time(0));
	int randPosition = rand() % this->itemCount + 1;

	if (randPosition == 1)
	{
		ItemType removedItem = this->headPtr->getItem();
		this->remove(removedItem);
		return removedItem;
	}

	Node<ItemType>* prevNodeToDelete = this->headPtr;

	for (int i = 1; i < randPosition - 1; i++)
	{
		prevNodeToDelete = prevNodeToDelete->getNext();
	}

	Node<ItemType>* nodeToDelete = prevNodeToDelete->getNext();
	prevNodeToDelete->setNext(nodeToDelete->getNext());

	ItemType removedItem = nodeToDelete->getItem();

	nodeToDelete->setNext(nullptr);
	delete nodeToDelete;

	this->itemCount--;

	return removedItem;
}