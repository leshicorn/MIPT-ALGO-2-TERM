#include <iostream>
#include <vector>

using namespace std;

class HashTable {
private:
    vector<int> table;
    int size;
    int hash(int key) {
        return key % size;
    }
public:
    void insert(int key) {
        int index = hash(key);
        table[index] = key;
    }
    
    int remove(int key) {
        int index = hash(key);
        int deleted = table[index];
        table[index] = -1;
        return deleted;
    }
    int find(int key) {
        int index = hash(key);
        return table[index];
    }
    HashTable(int size) {
        this->size = size;
        table.resize(size);
        for (int i = 0; i < size; i++) {
            table[i] = -1;
        }
    }
};

int main()
{
    return 0;
}
