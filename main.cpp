#include "HashTable.h"

class GetKey {
public:
    bool operator()(int n) {
        return n;
    }
};

int main() {
    int a[2] = {3, 2};
    HashTable<int, GetKey> hash(a, 2);
    return 0;
}

