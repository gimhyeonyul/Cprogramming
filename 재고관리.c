#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int main(void) {
	int quantity;
	int products;
	int sales;
	int id;

	int *icq = NULL;
	int *sq = NULL;
	int *stocks = NULL;

	icq = malloc(MAX_SIZE * sizeof(int));//incoming quantity
	sq = malloc(MAX_SIZE * sizeof(int)); //saled quantity
	stocks = malloc(MAX_SIZE * sizeof(int));
	printf("��ǰ ������ �Է��Ͽ��ֽʽÿ�.(1~%d)������ �� ����", MAX_SIZE);
	scanf("%d", &quantity);

	icq = realloc(icq, quantity * sizeof(int));
	sq = realloc(sq, quantity * sizeof(int));
	stocks = realloc(stocks, quantity * sizeof(int));

	for (int i = 0; i < quantity; i++) {
		printf("�԰������ �ϳ��� �Է��Ͻʽÿ�.");
		scanf("%d", &products);
		icq[i] = products;
	}
	for (int i = 0; i < quantity; i++) {
		printf("�Ǹż����� �ϳ��� �Է��Ͻʽÿ�.");
		printf("%d���� �۾ƾ��մϴ�.", icq[i]);
		scanf("%d", &sales);
		sq[i] = sales;
	}
	for (int i = 0; i < quantity; i++) {
		stocks[i] = icq[i] - sq[i];
	}
	printf("ID�� �Է��Ͻÿ� (%d �̳��� ���� �Է����ּ���.)", quantity);
	scanf("%d", &id);
	
	if (id < 0 || id >= quantity) {
		printf("�ش� ID�� ��ǰ������ �ʰ��Ҽ� �����ϴ�.");
	}
	else {
		printf("ID�� �ش��ϴ� ��ǰ�� ��� ����:%d\n", stocks[id]);
	}
	for (int i = 0; i < quantity; i++) {
		printf("��� ��ǰ�� ��� ���: %d\n", stocks[i]);
	}

	free(icq);
	free(sq);
	free(stocks);

	return 0;
}