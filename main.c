#include"connector.h"

unsigned char *p;
const char t_block[] = {11, 5, 5, -2, 0};
tckt_ t[2], *t_set;
block *tst;

void p_bk(block *_b)
{
	printf("%hhu: ", _b->step);
	for (char *c = _b->parts; *c; c++)
		printf("%+-5hhd", *c);
}

int main()
{
	srand((unsigned)time(NULL));
	
	p = malloc(2 + sizeof(block *));

	printf("Enter K: ");
	scanf("%hhu", p);
	printf("Enter H: ");
	scanf("%hhu", p+1);
	
	*(block **)(p+2) = malloc(sizeof(block)+(++*p));

	t_set = set(p);
	*t = *t_set;
	free(t_set);
	memset(t+1, 0, sizeof(tckt_));
	
	search(stack(t));

	// to do: read connector detected

	p_bk(*(block **)(p+2));

	free(*(block **)(p+2));
	free(p);

	return 0;
}
