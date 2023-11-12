
#ifndef AVL_TREE_H_
#define AVL_TREE_H_

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

#endif