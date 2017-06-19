#include <fstream>

using namespace std;
ifstream fin("tst.in");
ofstream fout("tst.out");

class node {
 public:
  int value;
  int level;
  bool isRemoved;
  bool isInWay;
  node* left;
  node* right;
  node* father;

  node(int value, node* father, int level) : value(value), father(father),
                                             left(NULL), right(NULL),
                                             level(level), isRemoved(false),
                                             isInWay(false) {}
};

class BST {
 public:
  int min_way;

  BST() : root(NULL), min_way(INT_MAX) {}

  void add(int value);

  void order();

  void searchMin();

  void markInWay();

  void markRemoved();

  void remove();


 private:
  node* root;

  void add(int value, node* leaf);

  void order(node* leaf, bool isLRR);

  void markInWay(node* leaf);

  void markRemoved(node* leaf, int l = 0, int r = 0);

  void remove(node* leaf);

  void force_remove(node* leaf);

  void assign(node* leaf, node* new_leaf);

};

void BST::add(int value, node* leaf) {
  if (leaf->value == value) { return; }

  if (value < leaf->value) {
    if (leaf->left == NULL) {
      leaf->left = new node(value, leaf, leaf->level + 1);
      return;
    }

    add(value, leaf->left);
  } else {
    if (leaf->right == NULL) {
      leaf->right = new node(value, leaf, leaf->level + 1);
      return;
    }

    add(value, leaf->right);
  }
}

void BST::add(int value) {
  if (root == NULL) {
    root = new node(value, root, 0);
    return;
  }

  add(value, root);
}

void BST::order(node* leaf, bool isRLR) {
  if (isRLR) {
    fout << leaf->value << endl;
  }

  if (!isRLR &&
      leaf->left == NULL &&
      leaf->right == NULL &&
      leaf->level < min_way) {
    min_way = leaf->level;
  }


  if (leaf->left != NULL) {
    order(leaf->left, isRLR);
  }

  if (leaf->right != NULL) {
    order(leaf->right, isRLR);
  }
}

void BST::order() {
  if (root == NULL) { return; }
  order(root, true);
}

void BST::searchMin() {
  if (root == NULL) { return; }
  order(root, false);
}

void BST::markInWay(node* leaf) {
  if (leaf->left == NULL && leaf->right == NULL) {
    if (leaf->level == min_way) {
      leaf->isInWay = true;
    }

    return;
  }

  if (leaf->left != NULL) {
    markInWay(leaf->left);
    if (leaf->left->isInWay) { leaf->isInWay = true; }
  }

  if (leaf->right != NULL) {
    markInWay(leaf->right);
    if (leaf->right->isInWay) { leaf->isInWay = true; }
  }


}

void BST::markInWay() {
  if (min_way % 2 != 0 || root == NULL) { return; }

  markInWay(root);
};

void BST::markRemoved(node* leaf, int l, int r) {
  if (leaf->isInWay) {
    if (l == min_way / 2 && r == min_way / 2) {
      leaf->isRemoved = true;
    } else if (l == min_way / 2 && leaf->left && leaf->left->isInWay) {
      leaf->isRemoved = true;
    } else if (r == min_way / 2 && leaf->right && leaf->right->isInWay) {
      leaf->isRemoved = true;
    }
  }

  if (leaf->left != NULL) {
    markRemoved(leaf->left, l + 1, r);
  }

  if (leaf->right != NULL) {
    markRemoved(leaf->right, l, r + 1);
  }
}

void BST::markRemoved() {
  if (min_way % 2 != 0 || root == NULL) { return; }
  markRemoved(root);
}

void BST::remove(node* leaf) {
  if (leaf->left != NULL) {
    remove(leaf->left);
  }

  if (leaf->isRemoved) {
    force_remove(leaf);
  }

  if (leaf->right != NULL) {
    remove(leaf->right);
  }
}

void BST::remove() {
  if (min_way % 2 != 0 || root == NULL) { return; }
  remove(root);
}

void BST::force_remove(node* leaf) {
  if (leaf->left == NULL && leaf->right == NULL) {
    assign(leaf, NULL);
    return;
  }

  if (leaf->right == NULL) {
    assign(leaf, leaf->left);
    return;
  }

  if (leaf->left == NULL) {
    assign(leaf, leaf->right);
    return;
  }

  node* temp = leaf->left;

  if (temp->right == NULL) {
    leaf->value = temp->value;
    leaf->left = temp->left;
    delete temp;
    return;
  }

  while (temp->right != NULL) {
    temp = temp->right;
  }

  leaf->value = temp->value;
  temp->father->right = temp->left;

  delete temp;
}

void BST::assign(node* leaf, node* new_leaf) {
  if (leaf->father == NULL) {
    root = new_leaf;
  } else if (leaf->father->left == leaf) {
    leaf->father->left = new_leaf;
  } else if (leaf->father->right == leaf) {
    leaf->father->right = new_leaf;
  }
  delete leaf;
};


int main() {
  BST tree;
  while (!fin.eof()) {
    int v;
    fin >> v;
    tree.add(v);
  }

  tree.searchMin();
  tree.markInWay();
  tree.markRemoved();
  tree.remove();
  tree.order();

  fin.close();
  fout.close();
  return 0;
}
