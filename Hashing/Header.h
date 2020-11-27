#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;

template<class HashedObj>
class HashTable
{
public:
	explicit HashTable(const HashedObj & notFound, int size = 101);
	HashTable(const HashTable & rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), array(rhs.array), currentSize(rhs.currentSize){}

	const HashedObj & find(const HashedObj & x) const;

	void makeEmpty();
	void insert(const HashedObj & x);
	void remove(const HashedObj & x);
	int create(int size);
	void print();

	const HashTable & operator=(const HashTable & rhs);

	enum EntryType {ACTIVE, EMPTY, DELETED};

private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY) : element(e), info(i) {}
	};

	vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPos) const;
	int findPos(const HashedObj & x) const;
	void rehash();
	int nextPrime(int size);
	int hash(const string & key, int tableSize) const;
	int hash(int x, int tableSize) const;
	int hash2(int x) const;
	int findR(int size) const;
};

template<class HashedObj>
HashTable<HashedObj>::
HashTable(const HashedObj & notFound, int size)
: ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
	makeEmpty();
}

template<class HashedObj>
int HashTable<HashedObj>::nextPrime(int size)
{
	int i = 2;
	while (size % i != 0 && size >= i) i++;
	if (i == size) return i;
	else{
		i = size + 1;
		bool check = false;
		while (true) {
			for (int j = 2; j <= i; j++){
				if (i % j == 0 && j < i) break;
				else if (i % j == 0 && j == i) check = true;
			}
			if (check) break;
			i++;
		}
		return i;
	}
}

template<class HashedObj>
int HashTable<HashedObj>::hash(const string & key, int tableSize) const
{
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
		hashVal += key[i];

	return hashVal % tableSize;
}

template<class HashedObj>
int HashTable<HashedObj>::hash(int x, int tableSize) const
{
	if (x < 0) x = -x;
	return x % tableSize;
}

template<class HashedObj>
int HashTable<HashedObj>::hash2(int x) const
{
	int r = findR(array.size());
	return r - (x % r);
}

template<class HashedObj>
int HashTable<HashedObj>::findR(int size) const
{
	int r = size - 1;
	bool chk;
	for (; r >= 2; r--) {
		chk = true;
		for (int j = 2; j < r; j++) {
			if (r % j == 0) {
				chk = false;
				break;
			}
		}
		if (chk) break;
	}
	return r;
}

template <class HashedObj>
int HashTable<HashedObj>::create(int size)
{
	array.resize(nextPrime(size));
	makeEmpty();
	return nextPrime(size);
}

template<class HashedObj>
void HashTable<HashedObj>::print()
{
	cout << "\t------------------------\n";
	cout << "\t" << setw(6) << "Index\t" << setw(7) << "Element" << setw(9) << "Info\n";
	for (int i = 0; i<array.size(); i++)
	{
		string info = array[i].info == 0 ? "ACTIVE" : array[i].info == 1 ? "EMPTY" : "DELETED";
		cout << "\t------------------------\n";
		cout << "\t" << setw(3) << i << "\t" << setw(5) << array[i].element<< "\t" << setw(8) << info << "\n";
	}
	cout << "\t------------------------\n";
	cout << "\t currentSize = " << currentSize << endl;
}

template<class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
	currentSize = 0;
	for (int i = 0; i < array.size(); i++)
		array[i].info = EMPTY;
}

template<class HashedObj>
const HashedObj & HashTable<HashedObj>::
find(const HashedObj & x) const {
	int currentPos = findPos(x);
	if (isActive(currentPos))
		return array[currentPos].element;
	else return ITEM_NOT_FOUND;
}

template<class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj & x) const {
	int collisionNum = 0;
	int currentPos = hash(x, array.size());

	while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
		currentPos = hash(x, array.size()) + (++collisionNum * hash2(x));

		if (currentPos >= array.size())
			currentPos %= array.size();
	}
	return currentPos;
}

template<class HashedObj> 
bool HashTable<HashedObj>::isActive(int currentPos) const
{
	return array[currentPos].info == ACTIVE;
}

template<class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj & x)
{
	int currentPos = findPos(x);
	if (isActive(currentPos)) {
		array[currentPos].info = DELETED;
		currentSize--;
	}
}

template<class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x) 
{
	int currentPos = findPos(x);
	if (isActive(currentPos)) return;

	array[currentPos] = HashEntry(x, ACTIVE);
	if (++currentSize > array.size() * 75 / 100)
		rehash();
}

template<class HashedObj>
const HashTable<HashedObj> & HashTable<HashedObj>::
operator=(const HashTable<HashedObj> & rhs)
{
	if (this != &rhs)
	{
		array = rhs.array;
		currentSize = rhs.currentSize;
	}
	return *this;
}

template<class HashedObj>
void HashTable<HashedObj>::rehash()
{
	vector<HashEntry> oldArray = array;

	array.resize(nextPrime(2 * oldArray.size()));
	makeEmpty();

	for (int i = 0; i < oldArray.size(); i++)
	if (oldArray[i].info == ACTIVE)
		insert(oldArray[i].element);
}