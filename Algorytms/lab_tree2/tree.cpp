#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

typedef struct Vertex{
    int data;
    struct Vertex* left;
    struct Vertex* right;
}Vertex;

void fillMassive(int a[], int n) {
    for (int i = 0; i < n ; i++) {
        a[i] = i+100;
        //a[i] = rand() % 100;
    }
}

void Obhod_slevo_napravo(Vertex* root) {
    if (root != nullptr) {
        Obhod_slevo_napravo(root->left);
        cout << root->data << " ";
        Obhod_slevo_napravo(root->right);
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

int SumLen(Vertex* root, int l) {
    if (root == nullptr) {
        return 0;
    }
    else {
        return l + SumLen(root->left, l+1) + SumLen(root->right, l+1);
    }
}

Vertex* ISDP(int a[],int left, int right) {
    if (left > right) {
        return nullptr;
    }
    else {
        int m = (left + right) / 2;
        Vertex* p = new Vertex;
        p->data = a[m];
        p->left = ISDP(a, left, m - 1);
        p->right = ISDP(a,m+1, right);
        return p;
    }
}

int main() {
    srand(time(0));
    Vertex* root;
    Vertex* root2;
    Vertex* root3;
    Vertex* root4;
    Vertex* root5;
    int a[100];
    int a2[200];
    int a3[300];
    int a4[400];
    int a5[500];
    fillMassive(a, 100);
    fillMassive(a2, 200);
    fillMassive(a3, 300);
    fillMassive(a4, 400);
    fillMassive(a5, 500);
    root = ISDP(a, 0, 99);
    root2 = ISDP(a2, 0, 199);
    root3 = ISDP(a3, 0, 299);
    root4 = ISDP(a4, 0, 399);
    root5 = ISDP(a5, 0, 499);
    int size = Size(root);
    int height = Height(root);
    int sum = Sum(root);
    int sumLen = SumLen(root, 1);
    float h_sr = (float)sumLen / (float)size;
    cout << endl << "Высота дерева: " << height << endl << "Контрольная сумма: " << sum << endl << "Размер: " << size << endl;
    printf("Средняя высота: %0.2f\n", h_sr);
    cout << endl << "Высота дерева: " << Height(root2) << endl << "Контрольная сумма: " << Sum(root2) << endl << "Размер: " << Size(root2) << endl;
    printf("Средняя высота: %0.2f\n", (float)SumLen(root2, 1) / (float)Size(root2));
    cout << endl << "Высота дерева: " << Height(root3) << endl << "Контрольная сумма: " << Sum(root3) << endl << "Размер: " << Size(root3) << endl;
    printf("Средняя высота: %0.2f\n", (float)SumLen(root3, 1) / (float)Size(root3));
    cout << endl << "Высота дерева: " << Height(root4) << endl << "Контрольная сумма: " << Sum(root4) << endl << "Размер: " << Size(root4) << endl;
    printf("Средняя высота: %0.2f\n", (float)SumLen(root4, 1) / (float)Size(root4));
    cout << endl << "Высота дерева: " << Height(root5) << endl << "Контрольная сумма: " << Sum(root5) << endl << "Размер: " << Size(root5) << endl;
    printf("Средняя высота: %0.2f\n", (float)SumLen(root5, 1) / (float)Size(root5));
}