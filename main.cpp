/*
 * 实现一个list类命名为MyList，其功能与python数组类似。可以用数组实现，也可以用链表实现。
 * 必须使用template <class T>，不允许使用<iostream>以外的库。
 * 需要实现的功能与测试代码见下。请务必搞清楚每一项的意义，比如什么时候需要用友元函数什么时候需要const什么时候需要&。
 * 当某些由用户正常操作可能产生的run time error（如pop一个空数组，或访问一个超出下标的元素），
 * 请使用try-catch-throw处理错误。
 * 以下类定义不保证完全正确，请根据实际需求修改，以实现样例功能为主。
 */

/*
 * 本练习不涉及到虚类和类继承，但是期末考试我就不知道了。如果有时间可以用书上的shape类来练习。
 */

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
    }//数组大小不够的时候将数组大小翻倍的操作。
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
    }//将item重复num次填入数组中。
    MyList(const MyList &l){
        size = l.size;
        a = new T [size];
        for (int i = 0;i < size;++i) a[i] = *(l.a + i);
    }//深复制另外一个MyList。
    MyList(T* arr, int len){
        try{
            int com = sizeof(arr)/sizeof(T);
            if(len > com) throw 0;
            size = len;
            a = new T [size];
            for (int i = 0;i < size;++i) a[i] = arr[i];
        }
        catch (int){
            size = 0;
            a = new T [100];
            cout << "Error! len is greater than the size of array" << endl;
        }
    }//以arr的前len个元素构造数组
    
    void push(const T &item){
        double_space();
        size = size/2 + 1;
        a[size-1] = item;
    }//将item添加在MyList最后。
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
    }//将MyList中最后一个元素删除，并返回这个删除的元素。
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
    }//将item插入到place处。
    void clean(){
        size = 0;
    }//清空数组。
    int get_size(){
        return size;
    }//返回MyList中元素的数量。
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
    }//删除MyList中第start到第end位的元素，包括两边。
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
    }//返回第index个元素。
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
    }//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
    int count(const T &item){
        int num = 0;
        for (int i = 0;i < size;++i) {
            if(a[i] == item) ++num;
        }
        return num;
    }//返回MyList中和item相等的元素的个数。
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
    }//删除MyList中第一个和item相等的元素。
    
    
    friend MyList operator + (const MyList &l1, const MyList &l2){
        MyList<T> result = l1;
        int total = l1.size+l2.size;
        while (result.size < total) result.double_space();
        for (int i = 0;i < l2.size;++i) {
            result.a[i+l1.size] = l2.a[i];
        }
        return result;
    }//合并两个MyList
    friend MyList operator + (const MyList &l1, const T &item){
        MyList<T> result = l1;
        result.push(item);
        return result;
    }//同push(T item)，但不修改l1，返回一个新数组
    MyList &operator = (const MyList &l){
        delete [] a;
        size = l.size;
        a = new T [size];
        for (int i = 0;i < size;++i) {
            a[i] = l.a[i];
        }
        return *this;
    }//赋值
    MyList &operator += (const T &item){
        push(item);
        return *this;
    }//同push(T item)
    MyList &operator += (const MyList &l){
        for (int i = 0;i < l.size;++i) push(l.a[i]);
        return *this;
    }//将一个MyList加入到本个MyList之后。
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
    }//返回第index个元素。
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
    }//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如：
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
    }//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。
    // 若less=true，按照从小到大排列，否则按从大到小排列
    void reverse(){
        T * b = new T [size];
        for (int i = 0;i < size;++i){
            b[i] = a[size - 1 - i];
        }
        delete [] a;
        a = b;
    }//将MyList的元素倒过来。
    
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
