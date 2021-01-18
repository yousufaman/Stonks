#include <iostream>
#include <cstring>

using namespace std;

class ArrayIndexOutOfBoundException
{
public:
    ArrayIndexOutOfBoundException()
        : message("Array Index Out of Bound") {}
    ~ArrayIndexOutOfBoundException()
    { /*delete message; */
    }
    const string what() const { return message; }

private:
    char *message;
};

template <typename T> 
class Array
{
private:
    T *Data;
    int size;
	
public:
    Array()
    {
        Data = NULL;

        size = 0;
    }
    Array(int n)
    {
        size = n;
        Data = new T[size];
        memset(this->Data, 0, sizeof(T) * size);
    }
    Array(const Array &rhs)
    {

        this->size = rhs.size;
        this->Data = new T[size];
        memcpy(this->Data, rhs.Data, (sizeof(T) * rhs.getSize()));
    }
    ~Array()
    {
        if (Data != 0)
        {
            cout << "Cleaning Memory, destroying arrays" << endl;
            delete[] Data;
            Data = 0;
            size = 0;
        }
    }
    void ReSize(int nSize)
    {
        if (size != nSize)
        {
            T *temp = new T[size];
            for (int i = 0; i < size; i++)
            {
                temp[i] = *(Data + i);
            }
            delete[] Data;
            Data = 0;
            Data = new T[nSize];
            memset(this->Data, 0, sizeof(T) * nSize);
            for (int i = 0; i < size; i++)
            {
                *(Data + i) = temp[i];
            }
            size = nSize;
            delete[] temp;
            temp = 0;
        }
    }
    unsigned int getSize() const
    {
        return size;
    }
    Array &operator=(Array &rhs)
    {
        if (this != &rhs)
        {
            int s = rhs.getSize();
            this->size = s;
            this->Data = new T[s];
            memcpy(this->Data, rhs.Data, sizeof(rhs.Data));
        }
        return (*this);
    }
    //lval
    T& operator[](int i)
    {
        return *(Data + i);
    }
    //rval
    const T &operator[](int i) const
    {
        return *(Data + i);
    }
    friend istream &operator>>(istream &infile, Array &rhs)
    {
        for (int count = 0; count < rhs.size; count++)
            infile >> rhs.Data[count];
        return infile;
    }
    friend ostream &operator<<(ostream &outfile, Array &rhs)
    {
        for (int count = 0; count < rhs.size; count++)
            outfile << rhs.Data[count];
        return outfile;
    }
};