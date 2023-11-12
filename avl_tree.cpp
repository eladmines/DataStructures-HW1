#include <iostream>
template<typename T>
class AVLTree {

  private:
	class Node {

	  private:
		Node *left_child;
		Node *parent;
		Node *right_child;
		int height;
		T* data;

	  public:
		Node(T* n_data);

		// Get the data from the node.
		T* getData();
		// return the balance point.
		int getBalance();
		// Get the height of the node.
		int getHeight();
		// Get the left child of the node.
		Node *getLeftChild();
		// Get the parent of the node.
		Node *getParent();
		// Get the right child of the node.
		Node *getRightChild();
		// Set the left child of the node.
		Node *setLeftChild(Node *newLeft);
		// Set the right child of the node.
		Node *setRightChild(Node *newRight);
		// Set the height of the node.
		int setHeight();
		// deletes the parent of the node.
		void deleteParent();
	};

  private:
	// A pointer to the root of the tree.
	Node *root;

	// Set the root of the tree.
	void setRoot(Node *n);
	// Balance the subtree.
	void balanceSubTree(Node *n);
	// Find the node by data.
	Node *findNode(T* n_data);
	// Rotate the subtree left.
	void rotateLeft(Node *n);
	// Rotate the subtree right.
	void rotateRight(Node *n);
	// return the spacing for element.
	int spacing(int offset);

  public:
	// creates an empty tree.
	AVLTree();
	// creates a tree with 1 node from input (n_data).
	AVLTree(T* n_data);
	// returns the height of the tree.
	int getHeight();
	// add the data (n_data) into the tree.
	bool insert(T* n_data);
	// Remove the data (n_data) from the tree.
	bool remove(T* n_data);
}; 

template<typename T>
AVLTree<T>::Node::Node(T* n_data) {
  parent = nullptr;
  left_child = nullptr;
  right_child = nullptr;
  data = n_data;
  height = 0;
}

template<typename T>
T* AVLTree<T>::Node::getData() {
  return data;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getParent() {
  return parent;
}

template<typename T>
int AVLTree<T>::Node::getHeight() {
  return height;
} 

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getRightChild() {
  return right_child;
} 

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getLeftChild() {
  return left_child;
} 

template<typename T>
int AVLTree<T>::Node::getBalance() {

  int balance;
  if (left_child == nullptr)
	if (right_child == nullptr)
	  balance = 0;
	else
	  balance = -right_child->height-1;
  else if (right_child == nullptr)
	balance = left_child->height+1;
  else
	balance = left_child->height-right_child->height;
  return balance;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::Node::setLeftChild(Node *newLeftNode) {
  if (newLeftNode != nullptr)
	newLeftNode->parent = this;
  left_child = newLeftNode;
  setHeight();
  return left_child;
} 

template<typename T>
void AVLTree<T>::Node::deleteParent() {
  parent = nullptr;
}

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::Node::setRightChild(Node *newRight) {

  if (newRight != nullptr)
	newRight->parent = this;
  right_child = newRight;
  setHeight();
  return right_child;
}

template<typename T>
int AVLTree<T>::Node::setHeight() {
  if (left_child == nullptr)
	if (right_child == nullptr)
	  height = 0;
	else
	  height = right_child->height+1;
  else if (right_child == nullptr)
	height = left_child->height+1;
  else if (left_child->height > right_child->height)
	height = left_child->height+1;
  else
	height = right_child->height+1;
  return height;
} 


template<typename T>
AVLTree<T>::AVLTree() {
  root = nullptr;
} 

template<typename T>
AVLTree<T>::AVLTree(T* n_data) {
  root = new Node(n_data);
}

template<typename T>
void AVLTree<T>::balanceSubTree(Node *n) {
	
  int balance = n->getBalance();
  if (balance > 1) {
	if (n->getLeftChild()->getBalance() < 0)
	  rotateLeft(n->getLeftChild());
	rotateRight(n);
  } else if (balance < -1) {
	if (n->getRightChild()->getBalance() > 0)
	  rotateRight(n->getRightChild());
	rotateLeft(n);
  } 
} 

template<typename T>
typename AVLTree<T>::Node *AVLTree<T>::findNode(T* n_data) {
  Node *temp = root;
  while (temp != nullptr) {
	if (n_data == temp->getData())
	  break;
	else if (n_data < temp->getData())
	  temp = temp->getLeftChild();
	else
	  temp = temp->getRightChild();
  } 
  return temp;
} 

template<typename T>
int AVLTree<T>::getHeight() {
  return root->getHeight();
} 

template<typename T>
bool AVLTree<T>::insert(T* n_data) {

  if (root == nullptr)
	root = new Node(n_data);
  else {
	Node *added_node = nullptr;
	Node *temp = root;
	while (temp != nullptr && added_node == nullptr) {
	  if (n_data < temp->getData()) {
		if (temp->getLeftChild() == nullptr) {
		  added_node = temp->setLeftChild(
			  new Node(n_data));
		} else
		  temp = temp->getLeftChild();

	  } else if (n_data > temp->getData()) {
		if (temp->getRightChild() == nullptr) {
		  added_node = temp->setRightChild(
			  new Node(n_data));
		} else
		  temp = temp->getRightChild();

	  } else
		return false;
	}

	temp = added_node;
	while(temp != nullptr) {
	  temp->setHeight();
	  balanceSubTree(temp);
	  temp = temp->getParent();
	} 
  }
  return true;
} 

template<typename T>
bool AVLTree<T>::remove(T* n_data) {

  Node *nodeToDelete = findNode(n_data);
  if (nodeToDelete == nullptr)
	return false;
  enum {left, right} direction;
  Node *parent = nodeToDelete->getParent();
  if (parent != nullptr &&
	  parent->getLeftChild() == nodeToDelete)
	direction = left;
  else
	direction = right;

  if (nodeToDelete->getLeftChild() == nullptr)
	if (nodeToDelete->getRightChild() == nullptr) {
	  if (parent == nullptr) {
		setRoot(nullptr);
		delete nodeToDelete;
	  } else {
		if (direction == left)
		  parent->setLeftChild(nullptr);
		else
		  parent->setRightChild(nullptr);
		delete nodeToDelete;
		parent->setHeight();
		balanceSubTree(parent);
	  }

	} else {

	  if (parent == nullptr) {
		setRoot(nodeToDelete->getRightChild());
		delete nodeToDelete;

	  } else {
		if (direction == left)
		  parent->setLeftChild(nodeToDelete-> getRightChild());
		else
		  parent->setRightChild(nodeToDelete-> getRightChild());
		delete nodeToDelete;
		parent->setHeight();
		balanceSubTree(parent);
	  } 
	} 

  else if (nodeToDelete->getRightChild() == nullptr) {

	if (parent == nullptr) {
	  setRoot(nodeToDelete->getLeftChild());
	  delete nodeToDelete;

	} else {
	  if(direction == left)
		parent->setLeftChild(nodeToDelete-> getLeftChild());
	  else
		parent->setRightChild(nodeToDelete-> getLeftChild());
	  delete nodeToDelete;
	  parent->setHeight();
	  balanceSubTree(parent);
	}

  } else {
	Node *newNode;
	Node *newNodeParent;
	Node *tempNode;
	int bal = nodeToDelete->getBalance();
	if (bal > 0) {
	  if (nodeToDelete->getLeftChild()->
		  getRightChild() == nullptr) {
		newNode = nodeToDelete->getLeftChild();
		newNode->setRightChild(
			nodeToDelete->getRightChild());
		tempNode = newNode;

	  } else {
		newNode = nodeToDelete->
			getLeftChild()->getRightChild();
		while (newNode->getRightChild() !=
			nullptr)
		  newNode = newNode->getRightChild();
		newNodeParent = newNode->getParent();
		newNodeParent->setRightChild(
			newNode->getLeftChild());
		tempNode = newNodeParent;
		newNode->setLeftChild(
			nodeToDelete->getLeftChild());
		newNode->setRightChild(
			nodeToDelete->getRightChild());
	  } 

	} else if (nodeToDelete->getRightChild()->
		getLeftChild() == nullptr) {
	  newNode = nodeToDelete->getRightChild();
	  newNode->setLeftChild(
		  nodeToDelete->getLeftChild());
	  tempNode = newNode;

	} else {
	  newNode = nodeToDelete->
		  getRightChild()->getLeftChild();
	  while (newNode->getLeftChild() !=
		  nullptr)
		newNode = newNode->getLeftChild();
	  newNodeParent = newNode->getParent();
	  newNodeParent->setLeftChild(
		  newNode->getRightChild());
	  tempNode = newNodeParent;
	  newNode->setLeftChild(
		  nodeToDelete->getLeftChild());
	  newNode->setRightChild(
		  nodeToDelete->getRightChild());
	} 
	if (parent == nullptr)
	  setRoot(newNode);
	else if (direction == left)
	  parent->setLeftChild(newNode);
	else
	  parent->setRightChild(newNode);
	delete nodeToDelete;
	balanceSubTree(tempNode);
  }
  return true;
} 

template<typename T>
void AVLTree<T>::rotateRight(Node *n) {

  enum {left, right} direction;
  Node *parent = n->getParent();
  if (parent != nullptr && parent->getLeftChild() == n)
	direction = left;
  else
	direction = right;
  Node *leftToTop = n->getLeftChild();
  n->setLeftChild(leftToTop->getRightChild());
  leftToTop->setRightChild(n);
  if (parent == nullptr)
	setRoot(leftToTop);
  else if (direction == left)
	parent->setLeftChild(leftToTop);
  else
	parent->setRightChild(leftToTop);
} 


template<typename T>
void AVLTree<T>::rotateLeft(Node *n) {
  enum {left, right} direction;
  Node *parent = n->getParent();
  if (parent != nullptr && parent->getLeftChild() == n)
	direction = left;
  else
	direction = right;
  Node *rightToTop = n->getRightChild();
  n->setRightChild(rightToTop->getLeftChild());
  rightToTop->setLeftChild(n);
  if (parent == nullptr)
	setRoot(rightToTop);
  else if (direction == left)
	parent->setLeftChild(rightToTop);
  else
	parent->setRightChild(rightToTop);
} 


template<typename T>
void AVLTree<T>::setRoot(Node *n) {
  root = n;
  if (root != nullptr)
	root->deleteParent();
} 

template<typename T>
int AVLTree<T>::spacing(int rank) {
  int space = 2;
  for (int i = 0; i < rank; i++)
	space = space+1;
  return space;
}
