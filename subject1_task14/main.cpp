#include <fstream>
#include <limits.h>

using namespace std;
ifstream fin("tst.in");
ofstream fout("tst.out");

class node {
public:
    int value;
    int level;
    bool isDelete;
    bool isInWay;
    node *left;
    node *right;
    node *father;

    node(int value, node *father, int level) : value(value), father(father), left(NULL), right(NULL),
                                               level(level), isDelete(false), isInWay(false) { }
};

class BST {
public:
    int minway;

    BST() : root(NULL), minway(INT_MAX) { }

    void add(int value);

    void order();

    void searchMin();

    void markInWay();

    void markDelete();

    void Delete();


private:
    node *root;

    void add(int value, node *leaf);

    void order(node *leaf, bool isLRR);

    void markInWay(node *leaf);

    void markDelete(node *leaf, int l = 0, int r = 0);

    void Delete(node *leaf);

    void del(node *leaf);

    void assign(node *leaf, node *newleaf);

};

void BST::add(int value, node *leaf) {
    if (value < leaf->value) {
        if (leaf->left != NULL)
            add(value, leaf->left);
        else
            leaf->left = new node(value, leaf, leaf->level + 1);
    } else if (value > leaf->value) {
        if (leaf->right != NULL)
            add(value, leaf->right);
        else
            leaf->right = new node(value, leaf, leaf->level + 1);
    }
}

void BST::add(int value) {
    if (root != NULL)
        add(value, root);
    else
        root = new node(value, root, 0);
}

void BST::order(node *leaf, bool isRLR) {

    if (isRLR)
        fout << leaf->value << endl;
    else if (leaf->left == NULL && leaf->right == NULL && leaf->level < minway)
        minway = leaf->level;


    if (leaf->left != NULL)
        order(leaf->left, isRLR);


    if (leaf->right != NULL)
        order(leaf->right, isRLR);
}

void BST::order() {
    if (root != NULL)
        order(root, true);
}

void BST::searchMin() {
    if (root != NULL)
        order(root, false);
}

void BST::markInWay(node *leaf) {
    if (leaf->left == NULL && leaf->right == NULL) {
        if (leaf->level == minway)
            leaf->isInWay = true;
    } else {
        if (leaf->left != NULL) {
            markInWay(leaf->left);
            if (leaf->left->isInWay)
                leaf->isInWay = true;
        }
        if (leaf->right != NULL) {
            markInWay(leaf->right);
            if (leaf->right->isInWay)
                leaf->isInWay = true;
        }
    }

}

void BST::markInWay() {
    if (minway % 2 == 0 && root != NULL)
        markInWay(root);

};

void BST::markDelete(node *leaf, int l, int r) {
    if (leaf->isInWay) {
        if (l == minway / 2 && r == minway / 2)
            leaf->isDelete = true;
        else if (l == minway / 2 && leaf->left && leaf->left->isInWay)
            leaf->isDelete = true;
        else if (r == minway / 2 && leaf->right && leaf->right->isInWay)
            leaf->isDelete = true;
    }

    if (leaf->left != NULL)
        markDelete(leaf->left, l + 1, r);
    if (leaf->right != NULL)
        markDelete(leaf->right, l, r + 1);
}

void BST::markDelete() {
    if (minway % 2 == 0 && root != NULL) {
        markDelete(root);
    }
}

void BST::Delete(node *leaf) {
    if (leaf->left != NULL)
        Delete(leaf->left);

    if (leaf->isDelete)
        del(leaf);

    if (leaf->right != NULL)
        Delete(leaf->right);
}

void BST::Delete() {
    if (minway % 2 == 0 && root != NULL)
        Delete(root);
}

void BST::del(node *leaf) {
    if (leaf->left == NULL && leaf->right == NULL)
        assign(leaf, NULL);
    else if (leaf->right == NULL)
        assign(leaf, leaf->left);
    else if (leaf->left == NULL)
        assign(leaf, leaf->right);
    else {
        node *temp = leaf->left;

        if (temp->right == NULL) {
            leaf->value = temp->value;
            leaf->left = temp->left;
        }
        else {
            while (temp->right != NULL)
                temp = temp->right;

            leaf->value = temp->value;

            if (temp->left != NULL)
                temp->father->right = temp->left;
            else
                temp->father->right = NULL;
        }
        delete temp;
    }
}

void BST::assign(node *leaf, node *newleaf) {
    if (leaf->father == NULL)
        root = newleaf;
    else if (leaf->father->left == leaf)
        leaf->father->left = newleaf;
    else if (leaf->father->right == leaf)
        leaf->father->right = newleaf;
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
    tree.markDelete();
    tree.Delete();
    tree.order();

    fin.close();
    fout.close();
    return 0;
}