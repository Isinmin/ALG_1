#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <locale>
#include <cstdlib>

#define Test 

using namespace std;

int compare(const void * x1, const void * x2)
{
	return (*(int*)x1 - *(int*)x2);
}// функция сравнения двух элементов

void generateMas(int a[], int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		int c = rand() % size;
		a[i] = c;
	}
}// генерация массива случайных чисел

void insertionSort(int* arr, int n, unsigned int *assig, unsigned int *comparison, int *step) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
#ifdef Test
			(*comparison)++;
#endif
			int tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
#ifdef Test
			*assig += 3;
#endif
		}
	}
}
void mySort(int *a, int n, int state, int mode, unsigned int *assig, unsigned int *comparison, int *step) {

#ifdef Test
	(*comparison)++;               //???
#endif
	if (n <= 1) return;
	if (n <= 8 && mode == 1) {
		if (state == 0) {
			cout << "Сортировка массива вставками:";
			insertionSort(a, n, assig, comparison, step);
		}
		if (state == 1) {
			cout << "Правый подмассив после сортировки вставками: ";
			insertionSort(a, n, assig, comparison, step);
			if (n != 0) {
				for (int i = 0; i < n; i++)
					cout << a[i] << " ";
			}

		}
		if (state == -1)
		{
			cout << "Левый подмассив после сортировки вставками: ";
			insertionSort(a, n, assig, comparison, step);
			for (int i = 0; i < n; i++) {
				cout << a[i] << " ";
			}
		}
		cout << endl;
	}
	if (n <= 8 && mode == 2) {
		return;
	}
	else {
		int x = a[n / 2];

		cout << endl;

		cout << "Шаг №" << *step << endl;

		cout << "Массив: ";
		for (int p = 0; p < n; p++)
			cout << " " << a[p];
		int i = 0;
		int j = n - 1;
		while (1)
		{
			while (a[i] < x)
				i++;
			while (a[j] > x)
				j--;
			if (i <= j)
			{
				if (i < j)
				{
					int tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
				}
				i++;
				j--;
			}
			else
			{
				break;
			}
		}
		(*step)++;
		cout << endl;
		cout << "Опорный элемент: " << x << endl;

		cout << "Левый подмассив:";
		for (int p = 0; p <= j; p++)
			cout << " " << a[p];
		cout << endl;


		cout << "Правый подмассив:";
		for (int p = i; p < n; p++)
			cout << " " << a[p];
		cout << endl;

		mySort(a, j + 1, -1, mode, assig, comparison, step);

		mySort(a + i, n - i, 1, mode, assig, comparison, step);

	}
}

void myBigSort(int *a, int n, int state, int mode, unsigned int *assig, unsigned int *comparison, int *step) {
	if (n <= 1) return;
	if (n <= 8 && mode == 1) {
		if (state == 0) {
			insertionSort(a, n, assig, comparison, step);
		}
		if (state == 1) {
			insertionSort(a, n, assig, comparison, step);
		}
		if (state == -1)
		{
			insertionSort(a, n, assig, comparison, step);
		}
	}
	if (n <= 8 && mode == 2) {
		return;
	}
	else {
		int x = a[n / 2];
		int i = 0;
		int j = n - 1;

#ifdef Test
		*assig += 3;
#endif
		while (1)
		{

			while (a[i] < x)
				i++;
#ifdef Test
			(*comparison)++;
#endif

			while (a[j] > x)
				j--;
#ifdef Test
			(*comparison)++;
#endif
			if (i <= j)

			{
				if (i < j)
				{
#ifdef Test
					(*comparison)++;
#endif
					int tmp = a[i];
					a[i] = a[j];
					a[j] = tmp;
#ifdef Test
					*assig += 3;
#endif
				}
				i++;
				j--;
			}
			else
			{
				break;
			}
		}

		myBigSort(a, j + 1, -1, mode, assig, comparison, step);

		myBigSort(a + i, n - i, 1, mode, assig, comparison, step);
	}
}

int main() {
	setlocale(LC_ALL, "");
	int size = 0, step = 0;
	unsigned int assig = 0, comparison = 0; //присваивания и сравнения
	int mode, fileMode;
	cout << "Выберите вариант окончательной сортировки. " << endl;
	cout << "1 - сортировать по частям" << endl;
	cout << "2 - сортировать весь массив" << endl;
	cin >> mode;
	ifstream fin;
	while (mode != 1 && mode != 2)
	{
		cout << "Такого варианта не существует, попробуйте ещё раз" << endl;
		cin >> mode;
	}
	cout << "Выберите откуда брать входные данные. " << endl;
	cout << "1 - из консоли" << endl;
	cout << "2 - из файла" << endl;
	cin >> fileMode;
	while (fileMode != 1 && fileMode != 2)
	{
		cout << "Такого варианта не существует, попробуйте ещё раз" << endl;
		cin >> fileMode;

	}
	int *arr, *brr;
	if (fileMode == 1)
	{
		cout << "Введите размер массива: ";
		cin >> size;
		while (size <= 0)
		{
			cout << "Неверный ввод, попробуйте ещё раз" << endl;
			cin >> size;
		}
		arr = new int[size];
		brr = new int[size];
		generateMas(arr, size);    //заполнение массива рандомными числами
		memcpy(brr, arr, sizeof(int)*size);
	}
	else
	{
		cout << "Введите путь к файлу" << endl;
		string path;
		cin >> path;

		fin.open(path);

		fin >> size;

		arr = new int[size];
		brr = new int[size];

		for (int i = 0; i < size; i++)
			fin >> arr[i];

		memcpy(brr, arr, sizeof(int)*size);
	}


	double startTime = (double)clock();

	if (size < 100) {
		cout << "Входной массив" << endl;
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << endl << endl;

		mySort(arr, size, 0, mode, &assig, &comparison, &step);

		if (mode == 2) {
			cout << endl;
			cout << "Результат быстрой сортировки:\n";
			for (int i = 0; i < size; i++)
				cout << arr[i] << " ";
			cout << endl;
			cout << "Выполняется сортировка вставками" << endl;
			insertionSort(arr, size, &assig, &comparison, &step);
		}
	}
	else {
		myBigSort(arr, size, 0, mode, &assig, &comparison, &step);

		if (mode == 2) {
			insertionSort(arr, size, &assig, &comparison, &step);
		}
	}

	double endTime = (double)clock();

	cout << endl;

	if (size < 100) {
		cout << "Результат:\n";
		for (int i = 0; i < size; i++)
			cout << arr[i] << " ";
		cout << endl;
	}

	double QstartTime = (double)clock();
	qsort(brr, size, sizeof(int), compare);
	double  QendTime = (double)clock();

	if (size < 100) {
		cout << "Отсортированный библиотечной функцией массив" << endl;
		for (int i = 0; i < size; i++)
			cout << brr[i] << " ";
	}
	cout << endl;

	cout << endl << "Время работы алгоритма = " << (endTime - startTime) / CLOCKS_PER_SEC << " c." << endl;
	cout << "Количество присваиваний = " << assig << " " << "Количество сравнений = " << comparison << endl;
	cout << endl;
	cout << endl << "Время затраченное библиотечной сортировкой составляет:" << (QendTime - QstartTime) / CLOCKS_PER_SEC << " c " << endl;

	int r = memcmp(brr, arr, size * sizeof *arr);
	if (!r) { cout << "Массивы эквивалентны" << endl; }
	else { cout << "Разные массивы, сортирока некорректна" << endl; }

	delete[] arr;
	delete[] brr;

	system("pause>NUL");
	return 0;
}