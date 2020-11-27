#include"Header.h"

string line(50, '=');
int menu();
int main() {
	HashTable<int> a(-999);

	int ch, size, x;
	bool create = false;
	do {
		ch = menu();
		if (ch == 1) {
			if (!create) {
				cout << line << endl;
				cout << "\t\tCreate mode" << endl;
				cout << line << endl;
				cout << "Enter Table size : ";
				cin >> size;
				size = a.create(size);
				create = true;
				cout << "Create successful table size is " << size << "." << endl;
				// system("pause");
			}
			else {
				cout << "Hash table already created." << endl;
				// system("pause");
			}
		}
		else if (ch == 2) {
			if (create) {
				cout << line << endl;
				cout << "\t\tInsert mode" << endl;
				cout << line << endl;
				cout << "Enter element : ";
				cin >> x;
				a.insert(x);
				cout << "Insert " << x << " successful." << endl;
				// system("pause");
			}
			else {
				cout << "Hash table has not created yet." << endl;
				// system("pause");
			}
			
		}
		else if (ch == 3) {
			if (create) {
				// system("cls");
				cout << line << endl;
				cout << "\t\tHash table" << endl;
				cout << line << endl;
				a.print();
				cout << line << endl;
				// system("pause");
			}
			else {
				cout << "Hash table has not created yet." << endl;
				// system("pause");
			}
		}
		else if (ch == 4) {
			if (create) {
				cout << line << endl;
				cout << "\t\tFind mode" << endl;
				cout << line << endl;
				cout << "Enter element : ";
				cin >> x;
				x = a.find(x);
				if (x != -999)
					cout << "Data found." << endl;
				else
					cout << "Data not found." << endl;
				// system("pause");
			}
			else {
				cout << "Hash table has not created yet." << endl;
				// system("pause");
			}
		}
		else if (ch == 5) {
			if (create) {
				cout << line << endl;
				cout << "\t\tRemove mode" << endl;
				cout << line << endl;
				cout << "Enter element : ";
				cin >> x;
				if (a.find(x) != -999) {
					a.remove(x);
					cout << "Remove " << x << " successful." << endl;
				}	
				else
					cout << "Data not found." << endl;
				// system("pause");
			}
			else {
				cout << "Hash table has not created yet." << endl;
				// system("pause");
			}
		}
	} while (ch != 6);
	cout << "Exit program." << endl;

	return 0;
}

int menu() {
	int ch;
	// system("cls");
	cout << line << endl;
	cout << "\t   Assignment Hashing" << endl;
	cout << line << endl;
	cout << " 1. Create Hash table" << endl;
	cout << " 2. Insert" << endl;
	cout << " 3. Print" << endl;
	cout << " 4. Find" << endl;
	cout << " 5. Remove" << endl;
	cout << " 6. Quit" << endl;
	cout << line << endl;
	cout << "Enter choice : ";
	cin >> ch;
	return ch;
}