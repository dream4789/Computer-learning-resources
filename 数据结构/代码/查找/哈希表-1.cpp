#include <iostream>

template<typename Type>
class HashTable {
public:
    enum KindofCell { Active, Empty, Deleted };

    HashTable() : ArrSize(DefaultSize), CurrentSize(0), LastFindOk(0) {
        AllocateArr();
    }

    ~HashTable() {
        delete[] Arr;
    }

    const HashTable& operator=(const HashTable& R) {
        if (this == &R) return *this;
        delete[] Arr;
        ArrSize = R.ArrSize;
        CurrentSize = R.CurrentSize;
        LastFindOk = R.LastFindOk;
        AllocateArr();
        for (int i = 0; i < ArrSize; ++i) {
            Arr[i] = R.Arr[i];
        }
        return *this;
    }

    int Insert(const Type& x) {
        unsigned int pos = FindPos(x);
        if (IsFound(x)) return 0;  // Element already exists in the table
        if (Arr[pos].info != Active) {
            Arr[pos].Element = x;
            Arr[pos].info = Active;
            CurrentSize++;
        }
        return 1;
    }

    int Remove(const Type& x) {
        unsigned int pos = FindPos(x);
        if (Arr[pos].info == Active && Arr[pos].Element == x) {
            Arr[pos].info = Deleted;
            CurrentSize--;
            return 1;
        }
        return 0;  // Element not found or is already deleted
    }

    const Type& Find(const Type& x) {
        unsigned int pos = FindPos(x);
        if (Arr[pos].info == Active && Arr[pos].Element == x) {
            LastFindOk = 1;
            return Arr[pos].Element;
        }
        LastFindOk = 0;
        // Returning a reference to a local variable is not ideal,
        // but it's done here for simplicity.
        static Type dummy;
        return dummy;  // Element not found
    }

    int IsFound(const Type& x) const {
        unsigned int pos = FindPos(x);
        return Arr[pos].info == Active && Arr[pos].Element == x;
    }

    int WasFound() const {
        return LastFindOk;
    }

    int IsEmpty() const {
        return CurrentSize == 0;
    }

    void MakeEmpty() {
        for (int i = 0; i < ArrSize; ++i) {
            Arr[i].info = Empty;
        }
        CurrentSize = 0;
    }

private:
    struct HashCell {
        Type Element;
        KindofCell info;

        HashCell() : info(Empty) {}

        HashCell(const Type& E, KindofCell i = Empty) : Element(E), info(i) {}
    };

    static const int DefaultSize = 11;
    int ArrSize;
    int CurrentSize;
    int LastFindOk;
    HashCell* Arr;

    void AllocateArr() {
        Arr = new HashCell[ArrSize];
    }

    unsigned int FindPos(const Type& x) const {
        unsigned int hashVal = HashFunction(x);
        unsigned int stepSize = HashStepSize(x);
        unsigned int currentPos = hashVal;

        while (Arr[currentPos].info != Empty &&
               Arr[currentPos].Element != x) {
            currentPos += stepSize;
            if (currentPos >= ArrSize)  // Wrap around to the beginning
                currentPos -= ArrSize;
        }
        return currentPos;
    }

    // Example hash function for integers
    unsigned int HashFunction(const Type& x) const {
        return x % ArrSize;
    }

    // Example step size function for linear probing
    unsigned int HashStepSize(const Type& x) const {
        return 1;
    }
};

int main() {
    HashTable<int> table;
    table.Insert(42);
    table.Insert(7);
    table.Insert(15);

    if (table.IsFound(7)) {
        std::cout << "Element 7 found in the hash table." << std::endl;
    }

    table.Remove(7);

    if (!table.IsFound(7)) {
        std::cout << "Element 7 not found in the hash table." << std::endl;
    }

    return 0;
}
