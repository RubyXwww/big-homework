#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
    T *a;
    int size;
    void double_space(){
        size = size * 2;
        //if (size == 0) size = 1; //if there is no elements in the array, add one.
        T *b = new T [size];
        for (int i = 0;i < size/2;++i) b[i] = a[i];
        delete [] a;
        a = b;
    }//double the list when necessary
    void quickSort(T a[],int s,int e){
        if (s < e){
            int k = a[s];
            int i = s,j = e;
            while (i < j) {
                while (i < j && a[j] >= k) --j;
                if (i < j) {a[i] = a[j];++i;}
                while (i < j && a[i] <= k) ++i;
                if (i < j) {a[j] = a[i];--j;}
            }
            a[i] = k;
            quickSort(a,s,i-1);
            quickSort(a,i+1,e);
        }
    }
public:
    MyList(){
        size = 0;
        a = new T [100];
    }
    MyList(int num, const T &item){
        try{
            if (num <= 0) throw 0;
            size = num;
            a = new T [size];
            for (int i = 0;i < size;++i) a[i] = item;
        }
        catch (int){
            size = 0;
            a = new T [100];
            cout << "Error! the size of the array can't less than or equal to 0" << endl;
        }
    }//fill the list with item for num times
    MyList(const MyList &l){
        size = l.size;
        a = new T [size];
        for (int i = 0;i < size;++i) a[i] = *(l.a + i);
    }//duplicate another list
    MyList(T* arr, int len){
        try{
            int com = sizeof(arr)/sizeof(T);
            if(len > com || len < 0) throw 0;
            size = len;
            a = new T [size];
            for (int i = 0;i < size;++i) a[i] = arr[i];
        }
        catch (int){
            size = 0;
            a = new T [100];
            cout << "Error! len is greater than the size of array" << endl;
        }
    }//construct the list with the elements in the array
    
    void push(const T &item){
        double_space();
        size = size/2 + 1;
        a[size-1] = item;
    }//add item at the end of the list
    T pop(){
        try{
            if (size == 0) throw 0;
            --size;
            return a[size];
        }
        catch(int) {
            cout << "Error! There is no element in your list" << endl;
            return a[0];
        }
    }//delete the last element in the list and return it at the same time
    void insert(int index, const T &item){
        try{
            if (index < -size) throw 0;
            while (index < 0) index += size;
            try{
                if (index > size) throw 0.0;
                ++size;
                T *b = new T [size];
                for (int i = 0;i < index;++i) b[i] = a[i];
                b[index] = item;
                for (int i = index+1;i < size;++i) b[i] = a[i-1];
                delete [] a;
                a = b;
            }
            catch(double) {
                cout << "Error! out of range!" << endl;
            }
        }
        catch(int) {cout << "illegal input" << endl;}
    }//insert item at requiring place
    void clean(){
        size = 0;
    }//clean the list
    int get_size(){
        return size;
    }//return the size
    void erase(int start, int end){
        try{
            if (start < -size || end < -size) throw false;
            while (start < 0) start += size;
            while (end < 0) end += size;
            if (start >= size || end >= size) throw 0;
            if (start > end) throw 0.0;
            size -= (end - start + 1);
            T *b = new T [size];
            for (int i = 0;i < start;++i) b[i] = a[i];
            for (int i = start;i < size;++i) b[i] = a[i + end - start + 1];
            delete [] a;
            a = b;
        }
        catch (int){
            cout << "Error! It's out of my range!" << endl;
        }
        catch (double){
            cout << "start is greater than end" << endl;
        }
        catch (bool){
            cout << "illegal input" << endl;
        }
    }//delete elements in the list from start to end, including the start and the end
    T get_item(int index){
        try {
            if (index < -size) throw 0.0;
            while (index < 0) index += size;
            if (index >= size) throw 0;
            return a[index];
        }
        catch(int) {
            cout << "Error! out of range!!!" << endl;
            return a[0];
        }
        catch(double){
            cout << "illegal input" << endl;
            return a[0];
        }
    }//return the required element
    MyList get_item(int start, int end){
        MyList<T> b;
        while (start < 0) start += size;
        while (end < 0) end += size;
        try {
            if(start >= size || end >= size) throw 0;
            if (start == end) {
                b.size = 1;
                b.a[0] = a[start];
            }
            else if (start < end){
                b.size = end-start+1;
                for (int i = start;i <= end;++i) {
                    b.a[i-start] = a[i];
                }
            }
            else {
                b.clean();
            }
        }
        catch(int){
            cout << "out of range!" << endl;
            b.clean();
        }
        return b;
    }//return elements from start to end
    int count(const T &item){
        int num = 0;
        for (int i = 0;i < size;++i) {
            if(a[i] == item) ++num;
        }
        return num;
    }//return the number of items in the list which is the same as the given one
    void remove(const T &item){
        int i;
        T * b = new T [size];
        for (i = 0;i < size;++i) {
            if (a[i] == item){
                break;
            }
            b[i] = a[i];
        }
        if (i == size) {
            delete [] b;
            return;
        }
        for (;i<size-1;++i){
            b[i] = a[i+1];
        }
        --size;
        delete [] a;
        a = b;
    }//delete the element it found first which is the same as the given one
    
    
    friend MyList operator + (const MyList &l1, const MyList &l2){
        MyList<T> result = l1;
        int total = l1.size+l2.size;
        while (result.size < total) result.double_space();
        for (int i = 0;i < l2.size;++i) {
            result.a[i+l1.size] = l2.a[i];
        }
        return result;
    }//merge the two lists
    friend MyList operator + (const MyList &l1, const T &item){
        MyList<T> result = l1;
        result.push(item);
        return result;
    }//similar to push which will create a new list instead of change any one
    MyList &operator = (const MyList &l){
        delete [] a;
        size = l.size;
        a = new T [size];
        for (int i = 0;i < size;++i) {
            a[i] = l.a[i];
        }
        return *this;
    }
    MyList &operator += (const T &item){
        push(item);
        return *this;
    }//similar to push
    MyList &operator += (const MyList &l){
        for (int i = 0;i < l.size;++i) push(l.a[i]);
        return *this;
    }//add a list behind the present list
    T &operator [](int index){
        try{
            if (index < -size) throw 0;
            while (index < 0) index += size;
            if (index >= size) throw 0.0;
            return a[index];
        }
        catch(int){
            cout << "illegal input" << endl;
            return a[0];
        }
        catch(double){
            cout << "out of range" << endl;
            return a[0];
        }
    }//return the element at the position of index
    friend ostream & operator<<(ostream &os, const MyList &obj){
        os << '[';
        int i;
        for (i = 0;i < obj.size - 1;++i){
            os << obj.a[i] << ", ";
        }
        for (;i<obj.size;++i)
            os << obj.a[i];
        os << ']';
        return os;
    }//if T can be cout, cout the list
    // [1, 2, 5, 4, 1]
    
    void sort(bool less=true){
        try{
            if (size == 0) throw 0;
            quickSort(a,0,size-1);
            if (!less) reverse();
        }
        catch(int) {
            cout << "No element to be sorted" << endl;
        }
    }//sort the list when T template supported for comparing
    // if less = true, the list is sorted from small to large; otherwise, reversed
    void reverse(){
        T * b = new T [size];
        for (int i = 0;i < size;++i){
            b[i] = a[size - 1 - i];
        }
        delete [] a;
        a = b;
    }//reverse the element in the list
    
    ~MyList(){delete [] a;}
};

int main(){
    MyList<int> a, b;
    int i;
    for (i=0; i<5; ++i)
        a.push(i);
    // a = [0, 1, 2, 3, 4]
    a[3] = 15; // a = [0, 1, 2, 15, 4]
    a.sort(); // a = [0, 1, 2, 4, 15]
    a.reverse(); // a = [15, 4, 2, 1, 0]
    a += 12; // a = [15, 4, 2, 1, 0, 12]
    for (i=0; i<a.get_size(); ++i)
        cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *若start > end，返回空数组
    b = a.get_item(3, -1); // b = [1, 0, 12]
    a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
    for (i=0; i<a.get_size(); ++i)
        cout<<a.get_item(i)<<endl;
    cout<<a.count(5)<<endl;
    b.clean(); // b = []
    cout<<b.get_size()<<endl;
    a.erase(2, 5); // a = [15, 4, 0, 12]
    b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
    b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
    b.remove(4); // b = [15, 0, 116, ...]
    cout << a[-1] << endl;
    cout<<b<<endl;
    MyList<double> c(0, 3.14);
    for (i=0; i<100; ++i)
        c.push(1.1*i);
    cout<<c.get_item(100, 105)<<endl;
    
    return 0;
}
