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
template<class T> class MyList;
template<class T>  MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2); 
template<class T>  MyList<T> operator + (const MyList<T> &l1, const T &item);
template<class T>  ostream & operator<< (ostream &os, const MyList<T> &obj);
template<class T>
class MyList{

private:
	T *a;
	int size;
	void double_space();
	int index;
public:
	
	MyList(){
		index = 0;
		size = 100;
		a = new T [size];
	}
	MyList(int num, const T &item);
	MyList(const MyList &l);
    MyList(T* arr, int len);

	void push(const T &item);
	T pop();
	void insert(int place, const T &item);
	void clean();
	int get_size();
	void erase(int start, int end); 
	T get_item(int i);
	MyList get_item(int start, int end);
	int count(const T &item);
	void remove(const T &item);


	friend MyList operator + <>(const MyList<T> &l1, const MyList<T> &l2); 
    friend MyList operator + <>(const MyList<T> &l1, const T &item); 
	MyList &operator = (const MyList &l);
	MyList &operator += (const T &item);
	MyList &operator += (const MyList &l);
	T &operator [](int index);
	friend ostream & operator<< <>(ostream &os, const MyList &obj);

	void sort(bool less=true);

	void reverse();

	~MyList(){delete [] a;}
};
template <class T> //double the space
void MyList<T>::double_space(){
    T *b;
	b = new T [size];
	int i;
	for (i=0; i<size; ++i) {
		b[i]=a[i];
	}
	delete [] a;
 	a =	new T[2*size];
 	for (i=0; i<size; ++i) {
 		a[i] = b[i];
 	}
 	delete [] b;
	size = size * 2;
}
template <class T>  //put num items into the list
MyList<T>::MyList(int num, const T &item){
	int i;
	index = num;
	size = num;
	a = new T [size];
	for (i = 0; i < num; ++i) {
		a[i] = item;
	}
} 
template <class T>  //copy another list
MyList<T>::MyList(const MyList &l){
	int i = 0;
	index = l.index;
	size = l.size;
	a = new T [size];
	for (i=0; i<index; ++i) {
		a[i] = l.a[i];
	}	
}
template <class T>  //construct the list by the first len numbers in the arr list
MyList<T>::MyList(T* arr, int len){
	int i;
	index = len;
	for (i=0; i<len; ++i) {
		a[i] = *(arr+i);
	}
    size = len;
}
template <class T>//add item
void MyList<T>::push(const T &item){
	if (index <= size - 1) {
		
		a[index] = item;
		++index;
	}
	if (index == size ) {
	    double_space();
	    
		a[index] = item;
		++index;
	}
}
template <class T>//delete the last element and return it
T MyList<T>::pop(){
	try 
	{
	if (index == 0) throw 1;
	--index;
	return a[index];
    }
    catch (int err) {
    	cout << "The list doesn't have any elements.";
    	exit(-1);
    }
}
template <class T>//insert the item in position "place"
void MyList<T>::insert(int place, const T &item){
	int i;
	try 
	{ 
	if (place >= index-1) throw 1;
	if (index <= size - 1) {
		++index;
		for (i = index-1; i> place; --i) {
			a[i] = a[i-1];
		}
		a[place] = item;
	}
	if (index == size ) {
		double_space();
		++index;
		for (i = index-1; i> place; --i) {
			a[i] = a[i-1];
		}
		a[place] = item;		
	}
    }
	catch (int err)
	{
		cout << "The index is out of range." ;
		exit(-1);
	}
	//cout << "insert" << index << endl;
}
template <class T>//clean the list
void MyList<T>::clean(){
	index = 0;
}
template <class T>//return the number of elements in the list
int MyList<T>::get_size(){
	return index;
}
template <class T>//delete a sublist (from start to end) 
void MyList<T>::erase(int start, int end){
	int i;
	if (start<0) start=index+start;
	if (end<0) end=index+end;
	try 
	{
	if (start >= index) throw 1;
	if (end >= index) throw 2;
	for (i=start; i<index-(end-start+1); ++i){
		a[i] = a[i+end-start+1];
	}
	index = index-(end-start+1);
    }
    catch (int err)
    {
    	if (err == 1) cout << "Start number is larger than size.";
    	if (err == 2) cout << "End number is larger than size.";
    	exit(-1);
    }
}
template <class T>//return the ith element
T MyList<T>::get_item(int i){
	try 
	{
	if (i > index-1) throw 1;
	return a[i];
    }
    catch (int err)
    {
    	cout << "The index is out of range.";
    	exit(-1);
    }
}
template <class T>//return a sublist (from start to end) accept negative numbers
MyList<T> MyList<T>::get_item(int start, int end){
	MyList res,res2;
	if (start<0) start=index+start;
	if (end<0) end=index+end;
	try 
	{
	if (start >= index) throw 1;
	if (end >= index) throw 2;
	if (start > end) {
		res2.size = 0;
		res2.index = 0;
	}
	int i,k=0;
	T *b;
	b = new T [end-start+1];
	for (i = start; i <= end; ++i){
		b[k] = a[i];
		++k;
	}
	res.size=end-start+1;
	res.index=end-start+1;
    for (i = 0; i <= (res.index)-1; ++i){
    	res.a[i] = b[i];
    }
    delete [] b;
	return res;
    }
    catch (int err)
    {
        if (err == 1) cout << "Start number is larger than size.";
    	if (err == 2) cout << "End number is larger than size.";
    	exit(-1);
    }
}
template <class T>//return the number of elements which are the same as item
int MyList<T>::count(const T &item){
	int i=0,count=0;
	for(i = 0; i < index; ++i){
		if (a[i] == item) ++count;
	}
	return count;
}
template <class T>//delete the first element in MyList which eqauls to item。
void MyList<T>::remove(const T &item){
	int i;
	for (i = 0; i < index; ++i){
		if (a[i] == item) {
			erase(i,i);
			break;
		}
	}
	//cout << index << endl;
}
template <class T>//merge two MyList
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2){
	MyList<T> res;
	int index1 = l1.index;
	int index2 = l2.index;
	int i=0,k=0;
	while (res.size < index1+index2){
		res.double_space();
	}
	for (i = 0 ; i <= index1-1; ++i) {
		res.a[i] = l1.a[k];
		++k;
	} 
	k=0;
	for (i = index1 ; i <= index1+index2-1; ++i) {
		res.a[i] = l2.a[k];
		++k;
	} 
	//cout << "in" << endl;
	//for (i = 0; i < index1+index2; ++i){
	//	cout << res.a[i] << endl;
	//}
	//cout << endl;
	res.index=index1+index2;
	return res;
}
template <class T>//almost the same as push(T item)，but no modification in l1，return a new list
MyList<T> operator + (const MyList<T> &l1, const T &item){
	MyList<T> res(l1);
	res.push(item);
	return res;
}
template <class T>//equal to
MyList<T> &MyList<T>::operator = (const MyList<T> &l){
	if (this == &l) return *this;
	delete [] a;
	size = l.size;
	index = l.index;
	a = new T [size];
	int i = 0;
	for (i = 0; i < index; ++i){
		a[i] = l.a[i];
	    //cout << l.a[i] << "ppp" << endl;
		//cout << a[i] <<"sss"<< endl;
	}

	return *this;	
}
template <class T>//same as push(T item)	
MyList<T> &MyList<T>::operator += (const T &item){
	push(item);
	return *this;
}
template <class T>//add new MyList into old MyList	
MyList<T> &MyList<T>::operator += (const MyList &l){
	while (index + l.index  > size ) double_space();
    int i,k=0;
	for (i = index; i < index+l.index; ++i ){
	    a[i] = l.a[k];
		++k; 
	}
	index = index + l.index;
	return *this;
}
template <class T>//return ith element
T &MyList<T>::operator [](int i){
	try 
	{
	if (i >= index-1) throw 1;
	return a[i];
    }
    catch (int err)
    {
    	cout << "The index is out of range.";
    	exit(-1);
    }
}

template <class T>
ostream &operator<< (ostream &os, const MyList<T> &obj)//cout the list just like in python, for example：[1, 2, 5, 4, 1]
{
    int i;
    //cout << "index" << ' ' << obj.index << endl;
	os << "[";
    for (i = 0; i < obj.index; ++i){
    	if (i<obj.index-1) os << obj.a[i] << ' ';
        if (i==obj.index-1) os << obj.a[i];
	}
	os << "]";
    return os;
}
template <class T>
void quicksort(T arr[], int low, int high)
    {
		int i = low;
		int j = high;
		T y;
		T z = arr[(low + high) / 2];
		do 
		{
			while (arr[i] < z) i++;
			while (arr[j] > z) j--;
			if (i <= j)
			{
				y = arr[i];
				arr[i] = arr[j];
				arr[j] = y;
				i++;
				j--;
			}
		} while(i <= j);
		if(low < j)
			quicksort(arr, low, j);
		if(i < high)
			quicksort(arr, i, high);
    }

//merge sort 
template <class T>
void MyList<T>::sort(bool less)
{
    if(less)
    {
    	quicksort(a, 0, index-1);
	}
	else
	{
		quicksort(a, 0, index-1);
		this->reverse();
	}
}

template <class T>
void MyList<T>::reverse()//reverse MyList
{
    int i=0, n = index;
    T tmp;
	for (i = 0; i < n/2; ++i) {
		tmp = a[i];
		a[i] = a[n-i-1];
		a[n-i-1]=tmp;
	}
}
int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]

	a.sort(1); // a = [0, 1, 2, 4, 15]

	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]

    b = a.get_item(4, -3); // b = [] *if start > end，return empty list 

	b = a.get_item(3, -1); // b = [1, 0, 12] 

	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 1, 0, 12]
	b = a + a; // b = [15, 4, 1, 0, 12, 15, 4, 1, 0, 12]
	b.insert(3, 116); // b = [15, 4, 1, 116, 0, 12, 15, 4, 1, 0, 12]
	b.remove(4); // b = [15, 1, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	return 0;
}




