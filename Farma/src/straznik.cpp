
#include <stdlib.h>
#include <stdio.h>


bool weryfikacja_argumentow(int argc, char* argv[]) {
	if(argc!=3)
	{
		printf("Błędna liczba argumentów");
		return false;
	}

	int watki = atoi(argv[1]);
	int pola = atoi(argv[2]);
  if(pola>6)
  {
    printf("Maksymalna liczba pol: 6 \n");
    return false;
  }

	if (watki > 10){
				printf("Maksymalna liczba wątków 10");
				return false;
	}
	return true;
}
