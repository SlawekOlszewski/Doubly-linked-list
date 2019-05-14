#include <iostream>
#include <windows.h>


using namespace std;





struct element {
	int value;
	element *next = NULL;
	element *previous = NULL;
};


void show(element* first) {
	element* temporary;
	cout << "Lista ";
	while(first != NULL) {
		cout << " " << first->value;
		temporary = first;
		first = first->next;
	}
	cout << endl;
}

bool addBegining(int value, element* &first) {
	element* toAdd = new element;
	if(first == NULL) {
		toAdd->value = value;
		toAdd->next = NULL;
		toAdd->previous = NULL;
		first = toAdd;
		return true;
	} else {
		toAdd->value = value;
		toAdd->next = *&first;
		first->previous = *&toAdd;
		toAdd->previous = NULL;
		first = toAdd;
		return true;
	}
	return false;
}
bool addEnd(int value, element* &last) {
	element* toAdd = new element;
	element* temporary = last;
	if(last == NULL) {
		toAdd->value = value;
		toAdd->next = NULL;
		toAdd->previous = NULL;
		last = toAdd;
		return true;
	}
	while(temporary->next != NULL) {
		temporary = temporary->next;
	}
	temporary->next = toAdd;
	toAdd->value = value;
	toAdd->previous = temporary;
	return true;
}

bool delBegining(element* &first) {
	first = first->next;
	delete first->previous;
	first->previous = NULL;
	return true;
}
bool delEnd(element* &first) {
	element* temporary = first;
	while(temporary->next->next != NULL)
		temporary = temporary->next;
	temporary->next = NULL;
	return true;
}
int search(int value,element* &first) {
	element* temporary = first;
	int position=1;
	while(temporary->next != NULL) {
		if(temporary->value == value) {
			return position;
		} else {
			temporary = temporary->next;
			position++;
		}
	}
	if(temporary->value ==value)
		return position;
	else
		return -1;
}
bool delAtribute(int value, element* &first) {
	element* temporary = first;
	if(temporary->value == value) {
		first = first->next;
		first->previous = NULL;
		return true;
	}
	while(temporary->next->next != NULL) {
		if(temporary->next->value == value) {
			temporary->next = temporary->next->next;
			temporary->next->previous = *&temporary;
			return true;
		} else {
			temporary = temporary->next;
		}
	}
	if(temporary->next->next == NULL) {
		if(temporary->next->value == value) {
			temporary->next = NULL;
			return true;
		}
	} else
		return false;
}

bool addAfter(int position, int add, element* &first, int nElements) {
	element* toAdd = new element;
	element* temporary = first;
	position = position -1;
	if(position > nElements || position < 0) {
		cout << "Podano wartosc z poza zakresu listy" << endl;
		return false;
	} else if(position == nElements) {
		addEnd(add, first);
		return true;
	} else if(position == 0) {
		toAdd->value = add;
		toAdd->previous = *&temporary;
		toAdd->next = temporary->next;
		temporary->next = toAdd;
		return true;
	} else {
		for(int i=0; i < position; i++)
			temporary = temporary->next;
		toAdd->value = add;
		toAdd->previous = *&temporary;
		toAdd->next = temporary->next;
		temporary->next = toAdd;
		return true;
	}

}

void sortowanie1(element* first,int nElements) {
	element* temporary;

	for (int i=0; i<nElements-1; i++) {
		for (int j=0; j<nElements; j++) {
			if ((first->value)>(first->next->value)) {
				swap((first->value),(first->next->value));
			}
		}
		first = first->next;
	}
}

void sortowanie2(element* first,int nElements) {
	element* temporary;

	for (int i=0; i<nElements-1; i++) {
		for (int j=0; j<nElements; j++) {
			if ((first->value)<(first->next->value)) {
				swap((first->value),(first->next->value));
			}
		}
		first = first->next;
	}

}

void freeMemory(element *first, int nElements) {
	while(first->next != NULL) {
		first = first->next;
	}
	for(int i=0; i< nElements+1; i++) {
		if(first->previous != NULL) {
			first = first->previous;
			delete first->next;
			first->next = NULL;
		}
	}
}

int main() {

	element* list = NULL;

	int menu = 0, submenu1, x,y, nElements=0;
	while(menu!=9) {
		cout << "1.Dodawanie/usuwanie pierwszego prawego/pierwszego lewego" << endl;
		cout << "2.Dodawanie elementu za elementem wskazanym" << endl;
		cout << "3.Usuwanie wskazanego elementu" << endl;
		cout << "4.Wyszukiwanie elementu o zadanej wartosci atrybutu" << endl;
		cout << "5.Wypisanie elementow listy" << endl;
		cout << "6.Sortowanie listy metoda babelkowa ze zmiana kierunku przegladania" << endl;
		cout << "7.Zwalnianie pamieci zajmowanej przez liste" << endl;
		cout << "8.Wyswietl liczbe elementow listy" << endl;
		cout << "9.Koniec programu" << endl;
		cin >> menu;
		system("cls");
		switch(menu) {
			case 1:
				cout << "1.Dodanie pierwszego lewego elementu" << endl;
				cout << "2.Dodanie pierwszego prawego elementu" << endl;
				cout << "3.Usuwanie pierwszego lewego elementu" << endl;
				cout << "4.Usuwanie pierwszego prawego elementu"  << endl;
				cin >> submenu1;
				system("cls");
				switch(submenu1) {
					case 1:
						cout << "Podaj wartosc jaka chcesz wpisac: ";
						cin >> x;
						addBegining(x,list);
						break;
					case 2:
						cout << "Podaj wartosc jaka chcesz wpisac: ";
						cin >> x;
						addEnd(x,list);
						break;
					case 3:
						delBegining(list);
						break;
					case 4:
						delEnd(list);
						break;
				}
				nElements++;
				break;
			case 2 :
				system("cls");
				cout << "Podaj za ktorym z kolei elementem chcesz wstawic: "; //CO JEZELI JEST KILKA ELEMENTOW O TEJ SAMEJ WARTOSCI???????-wstawi wtedy za pierwszym znalezionym, czy to poprawne?
				cin >> x;
				cout << "Podaj wartosc jaka chcesz wpisac: ";
				cin >> y;
				if(addAfter(x, y, list, nElements))
					nElements++;
				break;
			case 3:
				system("cls");
				cout << "Podaj wartosc elementu do usuniecia: ";
				cin >> x;
				if(delAtribute(x,list)) {
					cout << "Usunieto" << endl;
					nElements--;
					Sleep(1500);
				} else {
					cout << "Nie znaleziono elementu o takiej wartosci" << endl;
					Sleep(1500);
				}
				break;
			case 4:
				system("cls");
				cout << "Podaj wartosc szuaknego elementu: ";
				cin >> x;
				if(search(x, list)==-1)
					cout << "Element o wartosci atrybutu "<< x << " nie istnieje" << endl;
				else
					cout << "Istnieje element o wartosci atrybutu rownej "<< x <<", znajduje sie on na "<< search(x,list) << " pozycji" << endl;
				break;
			case 5:
				show(list);
				break;
			case 6:
				system("cls");
				cout << "1.Sortowanie od najmniejszego do najwiekszego" << endl;
				cout << "2.Sortowanie od najwiekszego do najmniejszego"  << endl;
				cin>>x;
				switch(x) {
					case 1:
						for(int i=0; i<nElements; i++) {
							sortowanie1(list,nElements);
						}
						break;
					case 2:
						for(int i=0; i<nElements; i++) {
							sortowanie2(list,nElements);
						}
						break;
				}
				break;
			case 7:
				freeMemory(list, nElements);
				break;
			case 8:
				cout << nElements << endl;
				break;
			case 9:
				exit(0);
				break;
		}
	}
	return 0;
}
