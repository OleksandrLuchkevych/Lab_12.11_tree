#include <iostream>
#include <string>

using namespace std;

struct Flat {
    int rooms;
    int floor;
    double area;
    string address;
    Flat* left;
    Flat* right;
};

Flat* createNode(const Flat& flat) {
    Flat* newNode = new Flat;
    newNode->rooms = flat.rooms;
    newNode->floor = flat.floor;
    newNode->area = flat.area;
    newNode->address = flat.address;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Flat* addFlat(Flat* root, const Flat& flat) {
    if (root == nullptr) {
        return createNode(flat);
    }

    if (flat.rooms < root->rooms) {
        root->left = addFlat(root->left, flat);
    }
    else if (flat.rooms > root->rooms) {
        root->right = addFlat(root->right, flat);
    }
    else {
        if (flat.floor < root->floor) {
            root->left = addFlat(root->left, flat);
        }
        else {
            root->right = addFlat(root->right, flat);
        }
    }

    return root;
}

Flat* findMinNode(Flat* node) {
    Flat* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Flat* removeFlat(Flat* root, const Flat& flat) {
    if (root == nullptr) {
        return nullptr;
    }

    if (flat.rooms < root->rooms) {
        root->left = removeFlat(root->left, flat);
    }
    else if (flat.rooms > root->rooms) {
        root->right = removeFlat(root->right, flat);
    }
    else {
        if (flat.floor < root->floor) {
            root->left = removeFlat(root->left, flat);
        }
        else if (flat.floor > root->floor) {
            root->right = removeFlat(root->right, flat);
        }
        else {
            if (root->left == nullptr) {
                Flat* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Flat* temp = root->left;
                delete root;
                return temp;
            }

            Flat* temp = findMinNode(root->right);
            root->rooms = temp->rooms;
            root->floor = temp->floor;
            root->area = temp->area;
            root->address = temp->address;
            root->right = removeFlat(root->right, *temp);
        }
    }

    return root;
}

void printAllFlats(Flat* root) {
    if (root != nullptr) {
        printAllFlats(root->left);
        cout << "Rooms: " << root->rooms << ", Floor: " << root->floor << ", Area: " << root->area << ", Address: " << root->address << endl;
        printAllFlats(root->right);
    }
}

void freeMemory(Flat* root) {
    if (root != nullptr) {
        freeMemory(root->left);
        freeMemory(root->right);
        delete root;
    }
}

Flat enterFlatInfo() {
    Flat flat;
    cout << "Enter the number of rooms: ";
    cin >> flat.rooms;
    cout << "Enter the floor: ";
    cin >> flat.floor;
    cout << "Enter the area: ";
    cin >> flat.area;
    cout << "Enter the address: ";
    cin.ignore();
    getline(cin, flat.address);
    return flat;
}

void printFlat(const Flat& flat) {
    cout << "Rooms: " << flat.rooms << ", Floor: " << flat.floor << ", Area: " << flat.area << ", Address: " << flat.address << endl;
}

int main() {
    Flat* root = nullptr;  // Початковий корінь дерева

    // Початкове формування картотеки
    Flat flat1{ 2, 3, 80.5, "Address 1", nullptr, nullptr };
    Flat flat2{ 3, 5, 120.0, "Address 2", nullptr, nullptr };
    Flat flat3{ 1, 2, 50.0, "Address 3", nullptr, nullptr };

    root = addFlat(root, flat1);
    root = addFlat(root, flat2);
    root = addFlat(root, flat3);

    
    // Введення заявки на обмін
    Flat requestedFlat = enterFlatInfo();
    cout << endl;
    // Пошук відповідного варіанту і вилучення з картотеки
    root = removeFlat(root, requestedFlat);

    // Виведення квартири, яку ввели з клавіатури
    cout << "Requested Flat: ";
    printFlat(requestedFlat);
    cout << endl;
    // Додавання заявки до картотеки
    root = addFlat(root, requestedFlat);


    cout << "All flats: " << endl;
    // Виведення всього списку
    printAllFlats(root);

    // Звільнення пам'яті
    freeMemory(root);

    return 0;
}
