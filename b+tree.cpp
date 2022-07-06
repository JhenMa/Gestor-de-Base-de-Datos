#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int const MAX = 3;

// BP node
template <typename T>
class Node {
    bool IS_LEAF;
    int *key, size;
    Node<T> **ptr;
    friend class BPTree;

    public:
      Node();
};

template <typename T>
Node<T>::Node() {
    key = new T[MAX];
    ptr = new Node<T> *[MAX + 1];
}

// BP tree
template <typename T>
class BPTree {
    Node<T> *root;
    void insertInternal(int, Node<T> *, Node<T> *);
    Node<T> *findParent(Node<T> *, Node<T> *);

    public:
      BPTree();
      void search(int);
      void insert(int);
      void display(Node<T> *);
      Node<T> *getRoot();
};


template <typename T>
BPTree<T>::BPTree() {
    root = NULL;
}

// Search operation
template <typename T>
void BPTree<T>::search(int x) {
    if (root == NULL) {
      cout << "Tree is empty\n";
    } else {
      Node<T> *cursor = root;
      while (cursor->IS_LEAF == false) {
        for (int i = 0; i < cursor->size; i++) {
          if (x < cursor->key[i]) {
            cursor = cursor->ptr[i];
            break;
          }
          if (i == cursor->size - 1) {
            cursor = cursor->ptr[i + 1];
            break;
          }
        }
      }
      for (int i = 0; i < cursor->size; i++) {
        if (cursor->key[i] == x) {
          cout << "Found\n";
          return;
        }
      }
      cout << "Not found\n";
    }
}

// Insert Operation
template <typename T>
void BPTree<T>::insert(int x) {
    if (root == NULL) {
        root = new Node<T>;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    } else {
        Node<T> *cursor = root;
        Node<T> *parent;
        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        } else {
          Node<T> *newLeaf = new Node<T>;
          int virtualNode[MAX + 1];
          for (int i = 0; i < MAX; i++) {
              virtualNode[i] = cursor->key[i];
          }
          int i = 0, j;
          while (x > virtualNode[i] && i < MAX)
            i++;
          for (int j = MAX + 1; j > i; j--) {
            virtualNode[j] = virtualNode[j - 1];
          }
          virtualNode[i] = x;
          newLeaf->IS_LEAF = true;
          cursor->size = (MAX + 1) / 2;
          newLeaf->size = MAX + 1 - (MAX + 1) / 2;
          cursor->ptr[cursor->size] = newLeaf;
          newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
          cursor->ptr[MAX] = NULL;
          for (i = 0; i < cursor->size; i++) {
            cursor->key[i] = virtualNode[i];
          }
          for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
            newLeaf->key[i] = virtualNode[j];
          }
          if (cursor == root) {
              Node<T> *newRoot = new Node<T>;
              newRoot->key[0] = newLeaf->key[0];
              newRoot->ptr[0] = cursor;
              newRoot->ptr[1] = newLeaf;
              newRoot->IS_LEAF = false;
              newRoot->size = 1;
              root = newRoot;
          } else {
              insertInternal(newLeaf->key[0], parent, newLeaf);
          }
        }
    }
}

// Insert Operation
template <typename T>
void BPTree<T>::insertInternal(int x, Node<T> *cursor, Node<T> *child) {
  if (cursor->size < MAX) {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--) {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--) {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  } else {
    Node<T> *newInternal = new Node<T>;
    int virtualKey[MAX + 1];
    Node<T> *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++) {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX + 1; i++) {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX)
      i++;
    for (int j = MAX + 1; j > i; j--) {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root) {
      Node<T> *newRoot = new Node<T>;
      newRoot->key[0] = cursor->key[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    } else {
      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent
template <typename T>
Node<T> *BPTree<T>::findParent(Node<T> *cursor, Node<T> *child) {
    Node<T> *parent;
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        } else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != NULL)
              return parent;
        }
    }
    return parent;
}

// Print the tree
template <typename T>
void BPTree<T>::display(Node<T> *cursor) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            cout << cursor->key[i] << " ";
        }
        cout << "\n";
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}

// Get the root
template <typename T>
Node<T> *BPTree<T>::getRoot() {
    return root;
}

int main() {
  BPTree<int> bptree;
  bptree.insert(5);
  bptree.insert(15);
  bptree.insert(25);
  bptree.insert(35);
  bptree.insert(45);
  bptree.insert(55);
  bptree.insert(40);
  bptree.insert(30);
  bptree.insert(20);
  bptree.display(bptree.getRoot());

  bptree.search(15);
}
