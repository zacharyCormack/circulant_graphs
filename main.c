#include"connector.h"

unsigned char *p;
const char t_block[] = {11, 5, 5, -2, 0};
tckt_ t[2], *t_set;
block *tst;

void p_bk(block _b)
{
	printf("%hhu: ", _b.step);
	for (char *c = _b.parts; *c != '0'; c++)
		printf("%02hhX", *c);
}

int main()
{
	srand((unsigned)time(NULL));

	tst = malloc(6);
	tst->step = 19;
	strcpy(tst->parts, t_block);
	printf("%s\n", chk_bk(tst) ? "GOOD" : "BAD");
	
	p = malloc(2 + sizeof(block *));

	printf("Enter K: ");
	scanf("%hhu", p);
	printf("Enter H: ");
	scanf("%hhu", p+1);
	
	*(block **)(p+2) = malloc(sizeof(block)+*p);

	printf("Output space: %p\n", *(block **)(p+2));

	t_set = set(p);
	*t = *t_set;
	memset(t+1, 0, sizeof(tckt_));
	free(t_set);
	
	stack(t);

	for (block *i = *(block **)(p+2); i->step; i++)
		p_bk(*i);

	free(*(block **)(p+2));
	free(p);

	return 0;
}
