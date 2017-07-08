#include <stdio.h>
#include "funkcje.h"

void checkFiles(bool display) //Procedura sprawdzaj�ca czy pliki s� poprawne
{
	printf("Nacisnij enter...");	//Obej�cie tego cholernego znaku nowego wiersza na przy czw�rce...
	getchar();
	system("cls");
	
	auto fpos_t length;
	auto char check;
	
	FILE *output = fopen(DATA_FILE, "r");	//Sprawdzanie pliku bazy danych
	fseek(output, 0, SEEK_END); //Sprawdzanie rozmiaru pliku
	fgetpos(output, &length);
	fseek(output, 0, SEEK_SET);
	
	if(length <= 2 OR output == NULL) //Sprawdzanie poprawno�ci pliku
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
	
	
	if(display == true)		//Wy�wietlanie ilo�ci rekord�w/kategorii
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
	bool display = false; //Zmienna logiczna dzi�ki kt�rej nie wy�wietlam ilo�ci rekord�w i kategorii na pocz�tku programu
	checkFiles(display);
	
	display = true;	//Przy nast�pnum wywo�aniu checkFile wy�wietlimy ilo�� rekord�w/kategorii
	char menuDigit = '\0', select;	//Deklaracja zmiennych znakowych do obs�ugi menu g��wnego
	
	printf("Witaj w programie\n\n");
	for(;;) //G��wne menu
	{
		printf("Wybierz numer operacji:\n\n");	//Nag��wek
		printf("1. Dodaj nowy rekord...\n");	//Dodawanie nowego rekordu
		printf(" 2. Dodaj nowa kategorie...\n");
		printf("  3. Wyszukiwanie rekordow...\n");
		printf("   4. Wyswietl ilosc rekordow/kategorii\n");	//Sprawdzanie spo�jnosci pliku i ilosci rekord�w oraz kategorii
		printf("    5. Reset bazy danych\n");	//Utworzenie trzech plik�w od nowa
		printf("     6. Wyjscie\n");	//Zgaduje, �e chodzi o wyj�cie z programu
		
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
				getchar();	//Tak, zgad�e�...
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
