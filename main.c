#include"connector.h"

unsigned char k, h;

int main()
{
	srand((unsigned)time(NULL));
	
	printf("Enter K: ");
	scanf("%hhu", &k);
	printf("Enter H: ");
	scanf("%hhu", &h);

	return 0;
}