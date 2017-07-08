#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define DATA_FILE	"database.cdata"
#define ID_FILE		"id.cdata"
#define CAT_FILE	"category.cdata"
#define CATID_FILE	"catid.cdata"
#define MAX_SIZE	51
#define AND	&&
#define OR	||
#define WORK	printf("YES");

/*
REMINDER
EKRAN MA BY� CZYSZCZONY NA POCZ�TKU WYWO�YWANYCH FUNKCJI DO WPROWADZANIA, WYSZUKIWANIA DANYCH
DLA PORZ�DKU I USYSTEMATYZOWANIA
*/

struct record{		//Deklaracja podstawowej struktury bazy

	int ID;
	char title[MAX_SIZE];		
	char autor[MAX_SIZE];
	char signature[MAX_SIZE];
};

struct category{	//Deklaracja struktury sygnatur i ich numeracji
	
	char fullname[MAX_SIZE];
	char shortname[MAX_SIZE];
	int counter;
};

char charConvert(int n) //Funkcja rzutuj�ca int na char
{
	switch(n)
	{
			case 0:
			return '0';
		
			case 1:
			return '1';
			
			case 2:
			return '2';
			
			case 3:
			return '3';
			
			case 4:
			return '4';
			
			case 5:
			return '5';
			
			case 6:
			return '6';
			
			case 7:
			return '7';
			
			case 8:
			return '8';
			
			case 9:
			return '9';
			
			default:
			printf("%i", n);
	}
}

void resetID()	//Procedura resetuj�ca numer ID w pliku ID.cdata
{
	FILE *ID = fopen(ID_FILE , "w");
	fprintf(ID, "0");
	fclose(ID);	
}

int getID() //Funkcja pobieraj�ca numer ID z pliku, zwracaj�ca warto�� obecnego ID
{
	auto int n;
	
	FILE *ID = fopen(ID_FILE , "r"); //Pobieranie ID
	fscanf(ID, "%i", &n);
	fclose(ID);

return n;
}

void addID() //Funkcja inkrementuj�ca ID o 1
{
	auto int n;
	
	FILE *ID = fopen(ID_FILE , "r"); //Pobieranie ID
	fscanf(ID, "%i", &n);
	fclose(ID);
	
	ID = fopen(ID_FILE, "w");	//Nadpisanie ID
	fprintf(ID, "%i", ++n);
	fclose(ID);
}

void resetCAT() //Funkcja resetuj�ca numer CATID w pliku catid.cdata
{
	FILE *ID = fopen(CATID_FILE , "w");
	fprintf(ID, "0");
	fclose(ID);	
}

int getCAT()	//Funkcja zwracaj�ca ilo�� kategorii w pliku catid.cdata
{
	auto int n;
	
	FILE *ID = fopen(CATID_FILE , "r"); //Pobieranie ID
	fscanf(ID, "%i", &n);
	fclose(ID);

return n;
}

void addCAT()	//Funkcja inkrementuj�ca CATID o 1
{
	auto int n;
	
	FILE *ID = fopen(CATID_FILE , "r"); //Pobieranie ID
	fscanf(ID, "%i", &n);
	fclose(ID);
	
	ID = fopen(CATID_FILE, "w");	//Nadpisanie ID
	fprintf(ID, "%i", ++n);
	fclose(ID);
}

void createBaseFile()	//Procedura tworz�ca nowy plik z nag��wkami kolumn USUWA WSZYTKIE DANE
{
	FILE *output = fopen(DATA_FILE, "w"); 
	fprintf(output, "ID TYTUL AUTOR SYGNATURA\n");
	fclose(output);
}

void createCatFile()	//Procedura tworz�ca nowy plik z kategoriami
{
	FILE *output = fopen(CAT_FILE, "w"); 
	fprintf(output, "NAZWA SKROT ILOSC\n");
	fclose(output);
}

void structPrint(struct record data) //Proceruda wy�wietlaj�ca struktur� "rekord" w KONSOLI bez numeru ID
{
	printf("TYTUL: %s\n AUTOR: %s\n  SYGNATURA: %s\n\n", data.title, data.autor, data.signature);
}

void categoryPrint(struct category data)	//Procedura wy�wietlaj�ca srtuktur� kategorii w KONSOLI bez licznika kategorii
{
	printf("NAZWA KATEGORII: %s\n SKROT: %s\n\n", data.fullname, data.shortname);
}

void debugPrint(struct record data)	//Procedura kt�ra s�u�y mi do debugowania silnika wyszukiwania
{
	printf("%i %s %s %s\n", data.ID, data.title, data.autor, data.signature);
}

void fstructPrint(struct record data) //Proceduta zapisuj�ca nowy rekord na ko�cu pliku z numerem ID
{
	addID();
	FILE *output = fopen(DATA_FILE , "r+");

	fseek(output, 0, SEEK_END); //Przesuni�cie kursora na koniec pliku
		
	fprintf(output, "%i %s %s %s\n", getID(), data.title, data.autor, data.signature);
	fclose(output);	
}

void fcategoryPrint(struct category data)	//Procedura zapisuj�ca now� kategori� na ko�cu pliku z domy�lnym licznikiem = 0
{
	FILE *output = fopen(CAT_FILE , "r+");
		
	fseek(output, 0, SEEK_END); //Przesuni�cie kursora na koniec pliku
		
	fprintf(output, "%s %s %i\n", data.fullname, data.shortname, data.counter);
	fclose(output);
	
}

void loadCategories(struct category array[], const int arraySize)	//Wczytuje do schowka (tablica struktur) dane z pliku
{
	FILE *input = fopen(CAT_FILE, "r");
	auto char dump;
	auto int i, j;
	
	for(i = 0; i < arraySize; ++i)	//Czyszczenie tablic znakowych z artefakt�w
		for(j = 0; j < MAX_SIZE; ++j)
			{
				array[i].fullname[j] = '\0';
				array[i].shortname[j] = '\0';
			}
	
	while(dump != '\n')	//Pomini�cie nag��wk�w kategorii
		fscanf(input, "%c", &dump);		
	
	
	for(i = 0; i < arraySize; ++i)	//Wype�nianie tablic
	{	
		for(j = 0 ;; ++j) //Pobieranie pe�nej nazwy kategorii
		{
			fscanf(input, "%c", &array[i].fullname[j]);
			if(array[i].fullname[j] == ' ')
				{
					array[i].fullname[j] = '\0';
					break;
				}
		}
		
			for(j = 0 ;; ++j) //Pobieranie skr�towej nazwy kategorii
		{
			fscanf(input, "%c", &array[i].shortname[j]);
			if(array[i].shortname[j] == ' ')
				{
					array[i].shortname[j] = '\0';
					break;
				}
		}
		
		fscanf(input, "%i\n", &array[i].counter); //Pobranie liczby rekord�w danej kategorii

	}	
fclose(input);	
}

void displayCategories()	//Procedura wy�wietlaj�ca wszystkie kategorie w konsoli
{
	auto const int arraySize = getCAT();
	auto struct category array[arraySize];
	
	loadCategories(array, arraySize);	//Wczytanie kategorii
	auto int i;
	
		for(i = 0; i < arraySize; ++i)
		{
			categoryPrint(array[i]);
			printf("\n");

		}
}

void updateCategories(char data[])		//Procedura aktualizuj�ca plik z kategoriami po dodaniu nowego rekordu
{
	auto int i, j;
	auto const int arraySize = getCAT();
	auto struct category array[arraySize];
	
	loadCategories(array, arraySize);
	
	for(i = 0; i < arraySize; ++i)	//Sprawdzanie, czy �a�cuchy shcatname i shortname s� r�wne
	{
		for(j = 0;;)
			{
				if(data[j] == '\0' OR array[i].shortname[j] == '\0')
					break;
				else if(data[j] == array[i].shortname[j])
					{
						++j;
						continue;
					}
				else break;			
			}
		if(data[j] == '\0' AND array[i].shortname[j] == '\0')
			{
				++array[i].counter;
				break;
			}		
	}
	
	createCatFile();		//Nadpisywanie pliku	
	for(i = 0; i < arraySize; ++i)
	fcategoryPrint(array[i]);
}

void getSignature(char shcatname[])	//Funkcja zwracaj�ca sygnatur� do nowego rekordu lub tablic� pust� w przypadku nie znalezienia podanej kategorii
{
	auto int i, j;
	auto const int arraySize = getCAT();
	auto struct category array[arraySize];
	auto char signatureID[] = "00000";
	
	loadCategories(array, arraySize);	//Wczytanie kategorii
	
	for(i = 0; i < arraySize; ++i)	//Sprawdzanie, czy �a�cuchy shcatname i shortname s� r�wne
	{
		for(j = 0;;)
			{
				if(shcatname[j] == '\0' OR array[i].shortname[j] == '\0')
					break;
				else if(shcatname[j] == array[i].shortname[j])
					{
						++j;
						continue;
					}
				else break;			
			}
		if(shcatname[j] == '\0' AND array[i].shortname[j] == '\0') //Konkatenacja shcatname i sygnatury z�o�onej z cyfr    DZIA�A !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				signatureID[0] = charConvert( (int) ++array[i].counter / 10000 );	//Inkrementacja ma na celu poprawn� numeracje zapisu w bazie
				signatureID[1] = charConvert( (int) array[i].counter / 1000	% 10);
				signatureID[2] = charConvert( (int) array[i].counter / 100 % 100);
				signatureID[3] = charConvert( (int) array[i].counter / 10 % 1000);
				signatureID[4] = charConvert( (int) array[i].counter % 10 );
				
				shcatname[j++] = signatureID[0];
				shcatname[j++] = signatureID[1];
				shcatname[j++] = signatureID[2];					//P�tle s� dla s�abych...
				shcatname[j++] = signatureID[3];
				shcatname[j++] = signatureID[4];	
				
				return;
			}			
	}
	
shcatname[0] = '\0';	//Je�eli p�tla nie zosta�a wcze�niej zako�czona (nie znaleziono kategorii) funkcja "zwraca" znak pusty 			
}

void loadDatabase(struct record array[], const int arraySize) //Wczytuje do schowka (tablica struktur) dane z pliku
{
	FILE *input = fopen(DATA_FILE, "r");
	auto char dump;
	auto int i, j;
	
	for(i = 0; i < arraySize; ++i)	//Czyszczenie tablic znakowych z artefakt�w
		for(j = 0; j < MAX_SIZE; ++j)
			{
				array[i].title[j] = '\0';
				array[i].autor[j] = '\0';
				array[i].signature[j] = '\0';
			}
			
	while(dump != '\n')	//Pomini�cie nag��wk�w bazy
		fscanf(input, "%c", &dump);
	
	for(i = 0; i < arraySize; ++i)	//Wype�nianie tablic
	{	
		fscanf(input, "%i%c", &array[i].ID, &dump); //Pobranie numeru ID
	
		for(j = 0 ;; ++j) //Pobieranie tytu�u
		{
			fscanf(input, "%c", &array[i].title[j]);
			if(array[i].title[j] == ' ')
				{
					array[i].title[j] = '\0';
					break;
				}
		}
		
			for(j = 0 ;; ++j) //Pobieranie autora
		{
			fscanf(input, "%c", &array[i].autor[j]);
			if(array[i].autor[j] == ' ')
				{
					array[i].autor[j] = '\0';
					break;
				}
		}
		
			for(j = 0 ;; ++j) //Pobieranie sygnatury
		{
			fscanf(input, "%c", &array[i].signature[j]);
			if(array[i].signature[j] == '\n')
				{
					array[i].signature[j] = '\0';
					break;
				}
		}
	}
fclose(input);	
}

void displayAll()	//Wy�wietlanie wszystkich rekord�w w bazie	SORTUJ WED�UG TYTU��W
{
	getchar();
	system("cls");
	
	const int arraySize = getID();
	auto struct record array[arraySize];
	
	loadDatabase(array, arraySize); //Wczytanie bazy
	auto int i;
	
	for(i = 0; i < arraySize; ++i)
		{
			structPrint(array[i]);
			printf("\n");

		}

system("pause"); 
system("cls");
}

void addEntry() //Procedura pobieraj�ca nowy wpis i przekazuj�ca go dalej do funkcji fstructPrint		
{
	getchar();
	auto char select;
	auto int i;
	auto struct record temp;
	auto char shcatname[MAX_SIZE], copy[MAX_SIZE];	//Deklaracja tablicy COPY u�atwi mi p�niej zwi�kszenie liczby rekord�w z dan� kategori� w pliku.
	
	for(i = 0; i < MAX_SIZE; ++i)	//Czyszczenie tablic z artefakt�w
	{
		temp.signature[i] = '\0';
		temp.autor[i] = '\0';
		temp.signature[i] = '\0';	
		shcatname[i] = '\0';
		copy[i] = '\0';
	}
	
	system("cls");
	printf("Podaj skrot kategorii dla nowego rekordu\n\n");
	displayCategories();
		
	for(i = 0;; ++i)	//Wprowadzenie kr�tkiej nazwy kategorii
	{
		shcatname[i] = getchar();
		if(shcatname[i] == ' ')
			shcatname[i] = '_';
				else if(shcatname[i] == '\n')
					break;
	}
	shcatname[i] = '\0';
	
	for(i = 0;; ++i)	//Kopia tablicy shcatname
	{
		copy[i] = shcatname[i];
			if(copy[i] == '\0')
				break;
	}
	
	
	getSignature(shcatname);
	if(shcatname[0] == '\0')
	{
		system("cls");
		printf("Nie ma takiej kategorii!\n");
		return;
	}
			
	system("cls");
	printf("Podaj tytul utworu: ");		//Wczytywanie tytu�u
	for(i = 0;; ++i)
	{
		temp.title[i] = getchar();
		if(temp.title[i] == ' ')
			temp.title[i] = '_';
				else if(temp.title[i] == '\n')
					break;
	}
	temp.title[i] = '\0';
	
		printf("Podaj autora utworu: ");		//Wczytywanie autora
	for(i = 0;; ++i)
	{
		temp.autor[i] = getchar();
		if(temp.autor[i] == ' ')
			temp.autor[i] = '_';
				else if(temp.autor[i] == '\n')
					break;
	}
	temp.autor[i] = '\0';
	system("cls");
		
	for(i = 0; shcatname[i] != '\0'; ++i)	//Wczytanie sygnatury
		temp.signature[i] = shcatname[i];
	
	printf("Czy chcesz dodac rekord o tych danych? T/N\n\n");
	structPrint(temp);
	for(;;)
	{
		scanf("%c", &select);
			if(select == 'T' OR select == 't')
				{
					system("cls");
					fstructPrint(temp);
					updateCategories(copy);
					printf("Dodano nowy rekord!\n");
					getchar();
					break;
				}
			else if(select == 'N' OR select == 'n')
				{
					system("cls");
					printf("Anulowano operacje\n");
					getchar();
					break;
				}			
	}		
}

void addCategory()	//Procedura dodaj�ca now� kategori�
{
	getchar();
	auto char select;
	auto int i;
	auto struct category temp;
	
	temp.counter = 0;	//Ustawienie pocz�tkowej warto�ci do sygnatury
	
	for(i = 0; i < MAX_SIZE; ++i)	//Czyszczenie tablic z artefakt�w
	{	
		temp.fullname[i] = '\0';
		temp.shortname[i] = '\0';
	}
			
	system("cls");
	printf("Podaj nazwe kategorii: ");	//Wczytywanie nazwy nowej kategorii
	
	for(i = 0;; ++i)
	{
		temp.fullname[i] = getchar();
		if(temp.fullname[i] == ' ')
			temp.fullname[i] = '_';
				else if(temp.fullname[i] == '\n')
					break;
	}
	temp.fullname[i] = '\0';
	
	printf("Podaj skrocona nazwe kategorii: ");	//Wczytywanie nazwy nowej kategorii
	
	for(i = 0;; ++i)
	{
		temp.shortname[i] = getchar();
		if(temp.shortname[i] == ' ')
			temp.shortname[i] = '_';
				else if(temp.shortname[i] == '\n')
					break;
	}
	temp.shortname[i] = '\0';
	system("cls");
	
	printf("Czy chcesz dodac kategorie o tych danych? T/N\n\n");	//Zatwierdzanie wyboru 
	categoryPrint(temp);
	for(;;)
	{
		scanf("%c", &select);
			if(select == 'T' OR select == 't')
				{
					system("cls");
					fcategoryPrint(temp);
					printf("Dodano nowa kategorie!\n");
					getchar();
					addCAT();
					break;
				}
			else if(select == 'N' OR select == 'n')
				{
					system("cls");
					printf("Anulowano operacje\n");
					getchar();
					break;
				}			
	}			
		
		
		
}

void sortByTitle(struct record array[], const int arraySize)	//Funckja sortuj�ca tablice rekord�w alfabetycznie wzgl�dem tytu��w
{

}

void searchMenu() //Podmenu z opcjami wyszukiwania
{
					auto char menuDigit = '\0'; //Zmienna znakowa do obs�ugi podmenu
					system("cls");
					
					printf("Opcje wyszukiwania\n\n");
					for(;;) //P�tla menu
					{
													printf("1. Wyswietl wszystkie rekordy\n"); //Odno�nik do procedury "displayAll"
													printf(" 2. Wyszkukaj tytul\n");
													printf("  3. Wyszukaj autora\n");
													printf("   4. Wyszukaj sygnature\n");
													printf("    5. Wyswietl rekordy z kategorii...\n");
													printf("     6. Cofnij...\n"); //Powr�t do menu g��wnego
													
													menuDigit = getchar();	//Wyb�r opcji z menu i przypisanie jej do zmiennej
													
													switch(menuDigit)	
													{
														case '1':
															{
																displayAll();
																return;
																break;
															}
															
															case '6':
																{
																				getchar();
																				return;
																				break;
																}
															default:
																{		
																							system("cls");
																							printf("Podano zly numer!\n");
																							break;
																}
															
													}													
					}
}	

