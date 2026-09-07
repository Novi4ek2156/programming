#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct Vertex {
    int data;
    struct Vertex* left;
    struct Vertex* right;
}Vertex;

void Obhod_sverhu_vniz(Vertex* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        Obhod_sverhu_vniz(root->left);
        Obhod_sverhu_vniz(root->right);
    }
}

void Obhod_slevo_napravo(Vertex* root) {
    if (root != nullptr) {
        Obhod_slevo_napravo(root->left);
        cout << root->data << " ";
        Obhod_slevo_napravo(root->right);
    }
}

void Obhod_snizu_vverx(Vertex* root) {
    if (root != nullptr) {
        Obhod_snizu_vverx(root->left);
        Obhod_snizu_vverx(root->right);
        cout << root->data << " ";
    }
}

int Size(Vertex* root) {
    if(root == nullptr) {
        return 0;
    }
    else return 1 + Size(root->left) + Size(root->right);
}

int Height(Vertex* root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        return 1 +  max(Height(root->left), Height(root->right));
    }
}

int Sum(Vertex* root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        return root->data + Sum(root->left)+ Sum(root->right);
    }
}

int main() {
    Vertex* root;
    root = new Vertex;
    root->data = 1;
    root->left = new Vertex;
    root->left->data = 2;
    root->left->right = nullptr;
    root->left->left = new Vertex;
    root->left->left->data = 3;
    root->left->left->left = nullptr;
    root->left->left->right = nullptr;
    root->right = new Vertex;
    root->right->data = 4;
    root->right->left = new Vertex;
    root->right->left->data= 5;
    root->right->left->left = nullptr;
    root->right->left->right = nullptr;
    root->right->right = new Vertex;
    root->right->right->data = 6;
    root->right->right->left = nullptr;
    root->right->right->right = nullptr;
    cout << "Обход сверху вниз: ";
    Obhod_sverhu_vniz(root);
    cout << endl;
    cout << "Обход слево направо: ";
    Obhod_slevo_napravo(root);
    cout << endl;
    cout << "Обход снизу вверх: ";
    Obhod_snizu_vverx(root);
    int size = Size(root);
    int h = Height(root);
    int sum = Sum(root);
    float h_sr = (float)sum / (float)size; 
    cout << endl << "Высота дерева: " << h << endl << "Контрольная сумма: " << sum << endl << "Размер: " << size << endl;
    printf("Средняя высота: %0.2f", h_sr);
}