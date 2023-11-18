#include <bits/stdc++.h>
#include <string>
#include <unordered_map>

using namespace std;
//stl vecto
template <class T>
class rit
{
	T *curr;
	public:
		T* &getcurr() {return curr;}
		rit(T *c=0) {curr=c;}
		rit<T> &operator=(rit<T> ri) {curr=ri.gercurr();}
		T& operator*() {return *curr;}
		rit<T> operator++(int) {return curr--;}
		rit<T> operator++() {return --curr;}
		bool operator!=(rit<T> ri) {return curr!=ri.getcurr();}
};

template <class T> 
class VECTOR
{
	int n,cap;  //n-size, cap=capacity
	T *buf;
	void expand(int new_cap)
	{
		if(new_cap<cap) return;
		T *tem=buf;
		cap=new_cap;
		buf=new T[cap];
		for(int i=0;i<n;i++) buf[i]=tem[i];
		if(tem) delete []tem;
	}
	public:
		VECTOR() {n=cap=0;buf=NULL;}
		VECTOR(int num,T x=0)          //tao vector co num so x
		{
			n=cap=0; buf=NULL;
			expand(num);
			n=num;
			for(int i=0;i<n;i++) buf[i]=x;
		}
		~VECTOR() {if(buf) delete []buf;}
		int size() {return n;}
		int empty() {return n==0;}
		void push_back(T x)
		{
			if(n==cap) expand(cap*2+1);
			buf[n++]=x;
		}
		T &back() {return buf[n-1];}
		void pop_back() {n--;}
		T &front() {return buf[0];}
		T &operator[] (int k) {return buf[k];}
		void resize(int new_size,T x=0)
		{
			if(cap<new_size) expand(new_size);
			for(int i=n;i<new_size;i++) buf[i]=x;
			n=new_size;
		}
		typedef T* iterator;
		iterator begin() {return buf;}
		iterator end() {return buf+n;}
		void erase(iterator it)
		{
			for(iterator it1=it;it1!=end();it1++) *it1=*(it1+1);
			n--;
		}
		void insert(iterator &it,T x)
		{
			if(n==cap) {int k=it-buf; expand(2*cap+1); it=buf+k;}
			for(iterator it1=buf+(n-1);it1>=it;it1--) *(it1+1)=*it1;
			*it=x;
			it+=1;
			n++;		
		}
		typedef rit<T> reverse_iterator;
		reverse_iterator rbegin() {return buf+(n-1);}
		reverse_iterator rend() {return buf-1;}
};


template <class T>
struct node
{
    T character;
    int frequency;
    node *left, *right;
    node(T ch, int freq, node<T> *r = nullptr, node<T> *l = nullptr)
    {
        character = ch;
        frequency = freq;
        right = r;
        left = l;
    }
};

template <class T>
struct compare
{
    bool operator()(const node<T> *a, const node<T> *b)
    {
        return a->frequency > b->frequency;
    }
};

template <class T>
void encode(node<T> *root, string str, unordered_map<T, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right)
    {
        huffmanCode[root->character] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

template <class T>
void decode(node<T> *root, int &index, string str)
{
    if (root == nullptr)
        return;
    if (!root->left && !root->right)
    {
        cout << root->character;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

template <class T>
void huffmanTree(const string &text)
{
    unordered_map<T, int> freq;
    for (auto ch : text)
    {
        freq[ch]++;
    }

    priority_queue<node<T> *, vector<node<T>*>, compare<T>> nuts;
    for (auto pair : freq)
    {
        nuts.push(new node<T>(pair.first, pair.second));
    }

    while (nuts.size() != 1)
    {
        node<T> *left = nuts.top();
        nuts.pop();
        node<T> *right = nuts.top();
        nuts.pop();

        node<T> *internalNode = new node<T>('\0', left->frequency + right->frequency, right, left);
        nuts.push(internalNode);
    }

    node<T> *root = nuts.top();

    unordered_map<T, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Ma Huffman la:" << endl;
    for (auto pair : huffmanCode)
    {
        cout << pair.first << " " << pair.second << endl;
    }

    string str = "";
    for (char ch : text)
    {
        str += huffmanCode[ch];
    }

    cout << "Chuoi da ma hoa la: " << str << endl;

    int index = -1;
    cout << "Chuoi da giai ma la: ";
    while (index < (int)str.size() - 2)
    {
        decode(root, index, str);
    }
}
int main()
{
    string text;
    cout << "Nhap ma muon nen: ";
    cin.ignore();
    getline(cin, text);
    huffmanTree<char>(text);

    return 0;
}
