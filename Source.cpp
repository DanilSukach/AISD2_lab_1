#include <iostream>
#include <vector>
#include <time.h>
#include <locale>
using namespace std;

class Set {
	struct TreeNode {
		int data;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int data, TreeNode* left, TreeNode* right) {
			this->data = data;
			this->left = left;
			this->right = right;
		}
	}*root;
	void delete_tree(TreeNode* tmp) {
		if (tmp)
		{
			delete_tree(tmp->left);
			delete_tree(tmp->right);
			delete tmp;
		}
	}
	bool contains_(const TreeNode* tmp, const int key) {
		if (!tmp)  return false;
		if (key == tmp->data)  return true;
		if (key < tmp->data) return contains_(tmp->left, key);
		return contains_(tmp->right, key);
	}
	TreeNode* insert_(const int key, TreeNode* tmp) {
		if (!tmp) return new TreeNode(key, nullptr, nullptr);
		if (key < tmp->data) tmp->left = insert_(key, tmp->left);
		else  tmp->right = insert_(key, tmp->right);
		return tmp;
	}
	void print_(const TreeNode* tmp) {
		if (!tmp) return;
		print_(tmp->left);
		cout << tmp->data << " ";
		print_(tmp->right);
	}
	TreeNode* min(TreeNode* tmp) {
		if (!tmp->left) return tmp;
		return min(tmp->left);
	}
	TreeNode* erase_(TreeNode* tmp, const int key) {
		if (!tmp) return tmp;
		if (key < tmp->data)  tmp->left = erase_(tmp->left, key);
		else if ((key > tmp->data)) tmp->right = erase_(tmp->right, key);
		else {
			if (!tmp->left) return tmp->right;
			if (!tmp->right) return tmp->left;
			tmp->data = min(tmp->right)->data;
			tmp->right = erase_(tmp->right, tmp->data);
		}
		return tmp;
	}

	TreeNode* run_copy(const TreeNode* tmp) {
		if (!tmp) return nullptr;
		TreeNode* root_copy = new TreeNode(tmp->data, nullptr, nullptr);
		root_copy->left = run_copy(tmp->left);
		root_copy->right = run_copy(tmp->right);
		return root_copy;
	}
public:

	TreeNode* get_root() {
		return root;
	}
	Set() { root = nullptr; }
	~Set() {
		delete_tree(root);
	}
	bool contains(const int key) { return contains_(root, key); }
	bool insert(const int key) {
		if (!contains(key)) {
			root = insert_(key, root);
			return true;
		}
		return false;
	}
	void print() { print_(root); }
	

	bool erase(const int key) {
		if (contains(key)) {
			root = erase_(root, key);
			return true;
		}
		return false;
	}

	Set(const Set& obj) {
		if (!obj.root) {
			delete_tree(root);
		}
		else {
			if (!root) {
				root = run_copy(obj.root);
			}
			else {
				delete_tree(root);
				root = run_copy(obj.root);
			}
		}
	}
	Set& operator=(const Set& obj) {
		if (!obj.root) {
			delete_tree(root);
			return *this;
		}
		else {
			if (!root) {
				root = run_copy(obj.root);
			}
			else {
				delete_tree(root);
				root = run_copy(obj.root);
				return *this;
			}
		}
	}
	void inorder_data_getter(const TreeNode* tmp, vector<int>& values) {
		if (!tmp) return;
		inorder_data_getter(tmp->left, values);
		inorder_data_getter(tmp->right, values);
		values.push_back(tmp->data);
	}
	
};

Set intersection( Set& a,  Set& b) {
	Set temp;
	vector<int> v1, v2;
	a.inorder_data_getter(a.get_root(), v1);
	b.inorder_data_getter(b.get_root(), v2);
	for (auto i : v1) {
		for (auto j : v2) {
			if (i == j) {
				temp.insert(i);
			}
		}
	}
	return temp;
}

Set difference( Set& a, Set& b) {
	Set temp = a;
	vector<int> v;
	b.inorder_data_getter(b.get_root(), v);
	for (auto i : v) {
		if (temp.contains(i)) {
			temp.erase(i);
		}
	}
	return temp;
}
size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
double avg(const double* ar) {
	double sum = 0;
	for (size_t i = 0; i < 100; ++i) {
		sum += ar[i];
	}
	return sum / 100;
}

double avg1000(const double* ar) {
	double sum = 0;
	for (size_t i = 0; i < 1000; ++i) {
		sum += ar[i];
	}
	return sum / 1000;
}
void insert_tree(size_t count) {
	double time[100]{};
	for (size_t i = 0; i < 100; ++i) {
		Set tree;
		clock_t begin = clock();
		for (size_t j = 0; j < count; ++j) {
			tree.insert(static_cast<int>(lcg()));
		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее заполнение дерева из " << count << " элементов: " << avg(time) << endl;
}

void insert_vector(size_t count) {
	double time[100]{};
	for (size_t i = 0; i < 100; ++i) {
		vector<size_t> vector;
		clock_t begin = clock();
		for (size_t j = 0; j < count; ++j) {
			vector.push_back(lcg());
		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее время заполнения вектора из " << count << " элементов: " << avg(time) << endl;
}

void search_tree(size_t count) {
	double time[1000]{};
	Set tree;
	for (size_t j = 0; j < count; ++j) {
		tree.insert(static_cast<int>(lcg()));
	}
	for (size_t i = 0; i < 1000; ++i) {
		clock_t begin = clock();
		tree.contains(static_cast<int>(lcg()));
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее время поиска случайного числа в дереве из " << count << " 1000 элементов: " << avg1000(time) << endl;
}
void add_tree(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		Set tree;
		for (size_t j = 0; j < count; ++j) {
			tree.insert(static_cast<int>(lcg()));
		}
		clock_t begin = clock();
		tree.insert(static_cast<int>(lcg()));
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее время добаления случайного числа в дереве из " << count << " элементов: " << avg1000(time) << endl;
}
void erase_tree(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		Set tree;
		for (size_t j = 0; j < count; ++j) {
			tree.insert(static_cast<int>(lcg()));
		}
		clock_t begin = clock();
		tree.erase(static_cast<int>(lcg()));
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее время удаления случайного числа в дереве из " << count << " элементов: " << avg1000(time) << endl;
}

void search_vector(size_t count) {
	double time[1000]{};
	vector<size_t> vector;
	for (size_t j = 0; j < count; ++j) {
		vector.push_back(static_cast<int>(lcg()));
	}
	for (size_t i = 0; i < 1000; ++i) {
		size_t elem = lcg();
		clock_t begin = clock();
		for (auto it = vector.begin(); it != vector.end(); ++it) {
			if (*it == elem) {
				break;
			}
		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее время поиска случайного числа в std::vector<int> из " << count << " элементов: " << avg1000(time) << endl;
}
void add_vector(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		vector<size_t> vector;
		for (size_t j = 0; j < count; ++j) {
			vector.push_back(static_cast<int>(lcg()));
		}
		clock_t begin = clock();
		vector.push_back(lcg());
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее время добаления случайного числа в std::vector<int> из " << count << " элементов: " << avg1000(time) << endl;
}
void erase_vector(size_t count) {
	double time[1000]{};
	for (size_t i = 0; i < 1000; ++i) {
		vector<size_t> vector;
		for (size_t j = 0; j < count; ++j) {
			vector.push_back(static_cast<int>(lcg()));
		}
		size_t elem = lcg();
		clock_t begin = clock();
		for (auto it = vector.begin(); it != vector.end(); ++it) {
			if (*it == elem) {
				vector.emplace(it);
				break;
			}

		}
		clock_t end = clock();
		time[i] = (double(end) - double(begin)) / double(CLOCKS_PER_SEC);
	}
	cout << "Среднее время удаления случайного числа в std::vector<int> из " << count << " элементов: " << avg1000(time) << endl;
}


void menu() {
	cout << "1. Вставить элемент" << endl;
	cout << "2. Удалить элемент" << endl;
	cout << "3. Проверка наличия элемента" << endl;
	cout << "4. Печать содержимого" << endl;
	cout << "5. Оператор присваивания" << endl;
	cout << "6. Пересечение множеств целых чисел" << endl;
	cout << "7. Разность множеств целых чисел" << endl;
	cout << "8. Эксперимент по времени" << endl;
	cout << "0. Выход" << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Set temp;
	while (true) {
		system("cls");
		menu();
		size_t flag_1;
		cin >> flag_1;
		switch (flag_1)
		{
		case 1:
		{
			system("cls");
			int number;
			cout << "Введите число ";
			cin >> number;
			if (temp.insert(number))cout << "Число добавлено" << endl;
			else cout << "Число не получилось добавить" << endl;
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			int number;
			cout << "Введите число ";
			cin >> number;
			if (temp.erase(number))cout << "Число удалено" << endl;
			else cout << "Число не получилось удалить" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			int number;
			cout << "Введите число ";
			cin >> number;
			if (temp.contains(number))cout << "Есть такое число" << endl;
			else cout << "Такого числа нет" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			temp.print();
			cout << endl;
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			Set tmp;
			temp.print();
			cout << endl;
			tmp = temp;
			tmp.print();
			cout << endl;
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			Set a, b, result;
			size_t count;
			cout << "Введите колличество элементов первого множества: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Введите число ";
				cin >> number;
				if (a.insert(number))cout << "Число добавлено" << endl;
				else cout << "Число не получилось добавить" << endl;
			}
			system("cls");
			cout << "Введите колличество элементов второго множества: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Введите число ";
				cin >> number;
				if (b.insert(number)) cout << "Число добавлено" << endl;
				else cout << "Число не получилось добавить" << endl;
			}
			system("cls");
			cout << "Первое множество: ";
			a.print();
			cout << endl;
			cout << "Второе множество: ";
			b.print();
			cout << endl;
			result = intersection(a, b);
			cout << "Пересечение двух множеств: ";
			result.print();
			cout << endl;
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			insert_tree(1000);
			insert_tree(10000);
			insert_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			insert_vector(1000);
			insert_vector(10000);
			insert_vector(100000);
			cout << "-------------------------------------------------------------------" << endl;
			search_tree(1000);
			search_tree(10000);
			search_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			search_vector(1000);
			search_vector(10000);
			search_vector(100000);
			cout << "-------------------------------------------------------------------" << endl;
			add_tree(1000);
			add_tree(10000);
			add_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			add_vector(1000);
			add_vector(10000);
			add_vector(100000);
			cout << "-------------------------------------------------------------------" << endl;
			erase_tree(1000);
			erase_tree(10000);
			erase_tree(100000);
			cout << "-------------------------------------------------------------------" << endl;
			erase_vector(1000);
			erase_vector(10000);
			erase_vector(100000);
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			Set a, b, result;
			size_t count;
			cout << "Введите колличество элементов первого множества: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Введите число ";
				cin >> number;
				if (a.insert(number))cout << "Число добавлено" << endl;
				else cout << "Число не получилось добавить" << endl;
			}
			system("cls");
			cout << "Введите колличество элементов второго множества: ";
			cin >> count;
			for (size_t i = 0; i < count; i++) {
				int number;
				cout << "Введите число ";
				cin >> number;
				if (b.insert(number)) cout << "Число добавлено" << endl;
				else cout << "Число не получилось добавить" << endl;
			}
			system("cls");
			cout << "Первое множество: ";
			a.print();
			cout << endl;
			cout << "Второе множество: ";
			b.print();
			cout << endl;
			result = difference(a, b);
			cout << "Разность двух множеств a/b: ";
			result.print();
			cout << endl;
			result = difference(b, a);
			cout << "Разность двух множеств b/a: ";
			result.print();
			cout << endl;

			cout << endl;
			system("pause");
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	}




}