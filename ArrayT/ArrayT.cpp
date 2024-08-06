#include <iostream>
using namespace std;


template<typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

public:
    Array(int capacity = 0, int grow = 1) : size(0), capacity(capacity), grow(grow) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }


    int GetSize()  {
        return size;
    }

    void SetSize(int nsize, int grow1 = 1) {
        if (nsize < size) {
            size = nsize;
        }
        grow = grow1;
        if (nsize != capacity) {
            T* newData = new T[nsize];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = nsize;
        }
    }


    int GetUpperBound()  {
        return size - 1;
    }

    bool IsEmpty()  {
        return size == 0;
    }

    void FreeExtra() {
        if (capacity > size) {
            T* newData = new T[size];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = size;
        }
    }

    void RemoveAll() {
        delete[] data;
        data = new T[capacity];
        size = 0;
    }

    T GetAt(int index) {
        return data[index];
    }

    void SetAt(int index, const T& value) {
        data[index] = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            return data[0];
        }
        return data[index];
    }

    void Add(const T& value) {
        if (size >= capacity) {
            SetSize(capacity + grow);
        }
        data[size++] = value;
    }

    void Append(const Array& other) {
        for (int i = 0; i < other.size; ++i) {
            Add(other.data[i]);
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            grow = other.grow;
            data = new T[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T* GetData() {
        return data;
    }

    const T* GetData() const {
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (size >= capacity) {
            SetSize(capacity + grow);
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    void RemoveAt(int index) {
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }
};

int main() {
    Array<int> arr(5, 2);

    arr.Add(1);
    arr.Add(2);
    arr.Add(3);
    arr.Add(4);

    cout << "size : " << arr.GetSize() << endl;
    cout << "UpperBound : " << arr.GetUpperBound() << endl;

    arr.SetAt(2, 10);
    cout << "add 10" << endl;
    
    arr.InsertAt(2, 20);
    cout << "add 20" << endl;

    for (int i = 0; i < arr.GetSize(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    arr.RemoveAt(3);
    cout << "remove at 3 indx" << endl;

    for (int i = 0; i < arr.GetSize(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    Array<int> arr2(3, 1);
    arr2.Add(5);
    arr2.Add(6);

    arr.Append(arr2);
    cout << "appended arr2 (5,6)" << endl;

    for (int i = 0; i < arr.GetSize(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}