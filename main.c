#include"connector.h"

unsigned char *p;
tckt_ t[2], *t_set;

void p_bk(block _b)
{
	printf("%hhu: %s\n", _b.step, (char *)_b.parts);
}

int main()
{
	srand((unsigned)time(NULL));
	
	p = malloc(2 + sizeof(block *));

	printf("Enter K: ");
	scanf("%hhu", p);
	printf("Enter H: ");
	scanf("%hhu", p+1);
	
	*(block **)(p+2) = malloc(sizeof(block));

	t_set = set(p);
	*t = *t_set;
	memset(t+1, 0, sizeof(tckt_));
	free(t_set);
	
	stack(t);

	block *out = *(block **)(p+2);

	do p_bk(*out);
	while (++out->step);

	free(*(block **)(p+2));
	free(p);

	return 0;
}
