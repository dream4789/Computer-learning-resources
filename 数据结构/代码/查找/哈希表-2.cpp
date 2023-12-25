#include <iostream>
using namespace std;

template <typename Type>
class HashTable {
public:
    enum KindofCell { Active, Empty, Deleted };

    HashTable();
    ~HashTable();
    const HashTable& operator=(const HashTable& R);
    int Insert(const Type& x);
    int Remove(const Type& x);
    const Type& Find(const Type& x);
    int IsFound(const Type& x) const;
    int WasFound() const;
    int IsEmpty() const;
    void MakeEmpty();

private:
    struct HashCell {
        Type Element;
        KindofCell info;

        HashCell(): info(HashTable<Type>::Empty) { }
        HashCell(const Type& E, KindofCell i = Empty): Element(E), info(i) { }
    };

    static const int DefaultSize = 11;
    int ArrSize;
    int CurrentSize;
    int LastFindOk;
    HashCell* Arr;

    void AllocateArr();
    unsigned int FindPos(const Type& x) const;
};

template <typename Type>
HashTable<Type>::HashTable() : ArrSize(DefaultSize), CurrentSize(0), LastFindOk(0), Arr(nullptr) {
    AllocateArr();
}

template <typename Type>
HashTable<Type>::~HashTable() {
    delete[] Arr;
}

template <typename Type>
const HashTable<Type>& HashTable<Type>::operator=(const HashTable& R) {
    if (this != &R) {
        delete[] Arr;
        ArrSize = R.ArrSize;
        CurrentSize = R.CurrentSize;
        LastFindOk = R.LastFindOk;
        AllocateArr();

        // Copy elements
        for (int i = 0; i < ArrSize; i++) {
            Arr[i] = R.Arr[i];
        }
    }
    return *this;
}

template <typename Type>
int HashTable<Type>::Insert(const Type& x) {
    unsigned int pos = FindPos(x);

    if (Arr[pos].info == Active) {
        return 0; // Element already present
    }

    Arr[pos] = HashCell(x, Active);
    CurrentSize++;
    return 1;
}

template <typename Type>
int HashTable<Type>::Remove(const Type& x) {
    unsigned int pos = FindPos(x);

    if (Arr[pos].info != Active) {
        return 0; // Element not found
    }

    Arr[pos].info = Deleted;
    CurrentSize--;
    return 1;
}

template <typename Type>
const Type& HashTable<Type>::Find(const Type& x) {
    unsigned int pos = FindPos(x);

    if (Arr[pos].info == Active) {
        LastFindOk = 1;
        return Arr[pos].Element;
    }

    LastFindOk = 0;
    throw "Element not found";
}

template <typename Type>
int HashTable<Type>::IsFound(const Type& x) const {
    unsigned int pos = FindPos(x);

    if (Arr[pos].info == Active) {
        return 1;
    }

    return 0;
}

template <typename Type>
int HashTable<Type>::WasFound() const {
    return LastFindOk;
}

template <typename Type>
int HashTable<Type>::IsEmpty() const {
    return CurrentSize == 0 ? 1 : 0;
}

template <typename Type>
void HashTable<Type>::MakeEmpty() {
    for (int i = 0; i < ArrSize; i++) {
        Arr[i].info = Empty;
    }
    CurrentSize = 0;
}

template <typename Type>
void HashTable<Type>::AllocateArr() {
    Arr = new HashCell[ArrSize];
}

template <typename Type>
unsigned int HashTable<Type>::FindPos(const Type& x) const {
    unsigned int hashVal = 0;
    for (int i = 0; i < sizeof(Type); i++) {
        char byte = *((char*)&x + i);
        hashVal = (hashVal << 5) + byte;
    }
    return hashVal % ArrSize;
}

int main() {
    HashTable<int> hashTable;

    hashTable.Insert(10);
    hashTable.Insert(20);
    hashTable.Insert(30);

    if (hashTable.IsFound(20)) {
        cout << "Element found in the hash table." << endl;
    }

    try {
        const int& result = hashTable.Find(30);
        cout << "Found element: " << result << endl;
    } catch(const char* msg) {
        cout << msg << endl;
    }

    hashTable.Remove(20);

    if (!hashTable.IsFound(20)) {
        cout << "Element successfully removed from the hash table." << endl;
    }

    if (hashTable.IsEmpty()) {
        cout << "Hash table is empty." << endl;
    } else {
        cout << "Hash table is not empty." << endl;
    }

    hashTable.MakeEmpty();

    if (hashTable.IsEmpty()) {
        cout << "Hash table is empty." << endl;
    } else {
        cout << "Hash table is not empty." << endl;
    }

    return 0;
}