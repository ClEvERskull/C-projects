#include "pch.h"
#include <iostream>
#include "Kocka.h"
#include <windows.h> 
using namespace std;
void startScreen();
void mainScreen();
void yourCards();
int moznost;
int hrac;
int zivoty = 7;
int pocet_kariet = 0;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	startScreen();
	mainScreen();
}


void startScreen() {
	do {
		system("cls");
		cout << "------------------ Welcome BITCHES !!!------------------" << endl;
		cout << "Zvol si stranu" << endl;
		cout << "1 - Sheriff" << endl;
		cout << "2 - Bandita" << endl;
		cout << "3 - Help" << endl;
		cin >> moznost;
		switch (moznost) {
		case 1:
			hrac = 1;
			pocet_kariet = 4;
			break;
		case 2:
			hrac = 2;
			pocet_kariet = 5;
			break;
		case 3:
			system("cls");
			cout << "Sheriff ma vyhodu v pouzivani takzvaneho vezenia a preto vie nechat banditu jedno kolo stat a pouzit tak napriklad dva krat utok." << endl;
			cout << "Bandita ma zasa narozdiel od Sheriffa na zaciatku hry 5 karty zatial co Sheriff len 4 a kedze sa neboji o destrukciu mesta ma aj karty ktore mu pomozu odlakat Sheriffa alebo jeho pomocnikov" << endl;
			cout << "Mozme pokracovat?...";
			cin.get(); cin.get();
			break;
		default:
			system("cls");
			cout << "Nespravna volba...skus to este raz...";
			cin.get(); cin.get();
			break;
		}
	} while ((moznost != 1) && (moznost != 2));
}

void mainScreen() {
	system("cls");
	if (hrac == 1) {
		cout << "SHERIFF" << endl;
	}
	else if (hrac == 2) {
		cout << "BANDITA" << endl;
	}
	cout << "Tvoje zdravie : ";
	cout << "[";
	for (int i = 0; i < zivoty; i++) {
		SetConsoleTextAttribute(hConsole, 76);
		cout << "#";
		SetConsoleTextAttribute(hConsole, 7);
	}
	if (zivoty < 7) {
		for (int i = 0; i < 7 - zivoty; i++) {
			cout << " ";
		}
	}
	cout << "]" << endl;
	cout << endl;
	yourCards();
	cin.get(); cin.get();
}

void yourCards() {
	cout << "Tvoje karty : ";
	for (int i = 0; i < pocet_kariet; i++) {
		string karta = 
	}
}