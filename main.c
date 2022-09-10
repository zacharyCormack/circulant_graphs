#include"connector.h"

unsigned char *p;
const char t_block[] = {11, 5, 5, -2, 0};
tckt_ t[2], *t_set;
block *tst;

void p_ct(connector *_c)
{
	for (char *c = _c->parts; *c; c++)
		printf("%+-5hhd", *c);
}

int main()
{
	srand((unsigned)time(NULL));
	
	// space for K, H and stack output adress
	p = malloc(2 + sizeof(connector *));

	printf("Enter K: ");
	scanf("%hhu", p);
	printf("Enter H: ");
	scanf("%hhu", p+1);
	
	// space for stack output, address stored in p
	*(connector **)(p+2) = malloc(sizeof(connector)+(++*p));

	// ticket address stored in t_set, ticket copied to t
	// so that pointer may be freed
	t_set = set(p);
	*t = *t_set;
	free(t_set);
	memset(t+1, 0, sizeof(tckt_));
	
	// find a block, then find a connector
	search(stack(t));

	p_ct(*(connector **)(p+2));

	free(*(connector **)(p+2));
	free(p);

	return 0;
}
