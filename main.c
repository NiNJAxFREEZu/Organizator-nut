#include <stdio.h>
#include "funkcje.h"

void checkFiles(bool display) //Procedura sprawdzaj¹ca czy pliki s¹ poprawne
{
	printf("Nacisnij enter...");	//Obejœcie tego cholernego znaku nowego wiersza na przy czwórce...
	getchar();
	system("cls");
	
	auto fpos_t length;
	auto char check;
	
	FILE *output = fopen(DATA_FILE, "r");	//Sprawdzanie pliku bazy danych
	fseek(output, 0, SEEK_END); //Sprawdzanie rozmiaru pliku
	fgetpos(output, &length);
	fseek(output, 0, SEEK_SET);
	
	if(length <= 2 OR output == NULL) //Sprawdzanie poprawnoœci pliku
	{
		createBaseFile();
		printf("Baza danych jest pusta/uszkodzona, utworzono nowy plik\n");
	}
	fclose(output);
	
	output = fopen(CAT_FILE, "r");	//Sprawdzenie pliku z kategoriami
	
		if(output == NULL)
			{
				printf("Plik z kategoriami jest pusty, utworzono nowy plik\n");
				createCatFile();
			}

	fclose(output);
	
	output = fopen(ID_FILE, "r");	//Sprawdzanie pliku z numerem ID
	
		if(output == NULL)
		{
			printf("Nie znaleziono pliku indetyfikacyjnego, plik ten zostal utworzony\n");
			resetID();
		}
	fclose(output);
	
	output = fopen(CATID_FILE, "r");	//Sprawdzanie pliku z numerem ID kategorii
	
	if(output == NULL)
		{
			printf("Nie znaleziono pliku z licznikiem kategorii, plik ten zostal utworzony\n");
			resetCAT();
		}
	fclose(output);	
	
	
	if(display == true)		//Wyœwietlanie iloœci rekordów/kategorii
	{
		if(getID() == 1)	//Gramatyka, ehhhhh....
		printf("%i REKORD\n", getID());
		else if(getID() <= 4 AND getID() > 1)
		printf("%i REKORDY\n", getID());
		else printf("%i REKORDOW\n", getID());
	
	
		if(getCAT() == 1)	//Gramatyka, ehhhhh....
		printf("%i KATEGORIA\n", getCAT());
		else if(getCAT() <= 4 AND getCAT() > 1)
		printf("%i KATEGORIE\n", getCAT());
		else printf("%i KATEGORII\n", getCAT());
	
	}
			
}

int main(void)
{	
	bool display = false; //Zmienna logiczna dziêki której nie wyœwietlam iloœci rekordów i kategorii na pocz¹tku programu
	checkFiles(display);
	
	display = true;	//Przy nastêpnum wywo³aniu checkFile wyœwietlimy iloœæ rekordów/kategorii
	char menuDigit = '\0', select;	//Deklaracja zmiennych znakowych do obs³ugi menu g³ównego
	
	printf("Witaj w programie\n\n");
	for(;;) //G³ówne menu
	{
		printf("Wybierz numer operacji:\n\n");	//Nag³ówek
		printf("1. Dodaj nowy rekord...\n");	//Dodawanie nowego rekordu
		printf(" 2. Dodaj nowa kategorie...\n");
		printf("  3. Wyszukiwanie rekordow...\n");
		printf("   4. Wyswietl ilosc rekordow/kategorii\n");	//Sprawdzanie spoójnosci pliku i ilosci rekordów oraz kategorii
		printf("    5. Reset bazy danych\n");	//Utworzenie trzech plików od nowa
		printf("     6. Wyjscie\n");	//Zgaduje, ¿e chodzi o wyjœcie z programu
		
		menuDigit = getchar();
		switch(menuDigit)
		{
			case '1':	
				{
					if( getCAT() == 0 )	//Sprawdzanie, czy istnieje zadeklarowana kategoria rekordu
						{
							getchar();
							system("cls");
							printf("Przed dodaniem pierwszego rekordu, musisz dodac kategorie!\n");
							break;
						}
					addEntry();
					break;
				}
			case '2':
				{
					addCategory();
					break;	
				}
			case '3':
				{
					getchar();
					searchMenu();
					break;
				}
			case '4':
				{
					checkFiles(display);
					break;
				}
			case '5':
				{
					getchar();	//Kolejny taktyczny dodge tego cholernego \n
					system("cls");
					printf("Jestes pewien? Usunie to wszystkie dane w bazie i zapisane kategorie T/N ");
					
					for(;;)
					{
					select = getchar();
						if(select == 'T' OR select == 't')
							{
								createBaseFile();
								createCatFile();
								resetID();
								resetCAT();
								system("cls");
								printf("Baza danych zostala zresetowana\n");
								break;
							}
						else if(select == 'N' OR select == 'n')
							{
								system("cls");
								printf("Anulowano reset\n");
								break;
							}	
					}
				getchar();	//Tak, zgad³eœ...
				continue;
				}
			case '6':
				{
					return 0;
					break;
				}
			default:
				{
					system("cls");
					printf("Podano zly numer\n");
					break;
				}
		}
		
	}

return 0;	
}
