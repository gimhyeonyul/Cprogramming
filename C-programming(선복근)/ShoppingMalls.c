#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

//void swap(int* a, int* b) {
//	int temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}

int main(void) {
	int quantity;
	int products;
	int sales;
	
	int total_sq = 0;
	int total_icq = 0;
	int min, max;
	
	

	int* icq = NULL;
	int* sq = NULL;
	int* stocks = NULL;
	int* id = NULL;

	icq = malloc(MAX_SIZE * sizeof(int));//incoming quantity
	sq = malloc(MAX_SIZE * sizeof(int)); //saled quantity
	stocks = malloc(MAX_SIZE * sizeof(int));
	id = malloc(MAX_SIZE * sizeof(int));
	printf("��ǰ ������ �Է��Ͽ��ֽʽÿ�.(1~%d)������ �� ����", MAX_SIZE);
	scanf("%d", &quantity);

	icq = realloc(icq, quantity * sizeof(int));
	sq = realloc(sq, quantity * sizeof(int));
	stocks = realloc(stocks, quantity * sizeof(int));
	id = realloc(id, quantity * sizeof(int));

	for (int i = 0; i < quantity; i++) {
		printf("�԰������ �ϳ��� �Է��Ͻʽÿ�.");
		scanf("%d", &products);
		icq[i] = products;
		total_icq += icq[i];
	}
	for (int i = 0; i < quantity; i++) {
		printf("�Ǹż����� �ϳ��� �Է��Ͻʽÿ�.");
		printf("%d���� �۾ƾ��մϴ�.", icq[i]);
		scanf("%d", &sales);
		sq[i] = sales;
		total_sq += sq[i];
	}
	for (int i = 0; i < quantity; i++) {
		stocks[i] = icq[i] - sq[i];
	}
	for (int i = 0; i < quantity; i++) {
		id[i] = i+1;
	}
	max = sq[0];
	min = sq[0];
	int temp1 = id[0];
	int temp2 = id[0];
	for (int j = 1; j < quantity; j++) {
		if (min > sq[j]) {//�ּҰ� ���ϴ� �ڵ�
			min = sq[j];
			temp1 = id[j];
		}
		if (max < sq[j]) {//�ִ밪 ���ϴ� �ڵ�
			max = sq[j];
			temp2 = id[j];
		}
	}
	
	/*for (int i = 0; i < quantity - 1; i++) {
		int most = i;
		for (int j = i + 1; j < quantity; j++) {
			if (sq[most] < sq[j]) {
				most = j;
			}
		}
		swap(&sq[i], &sq[most]);
	}*/
	
	for (int i = 0; i < quantity; i++) {
		printf("��� ��ǰ�� ��� ���: %d\n", stocks[i]);
	}
	printf("�� �Ǹŷ�: %d\n�Ǹ���: %.2f\n", total_sq, ((float)total_sq / total_icq)*100);
	printf("ID: %d, �ִ� �Ǹŷ�: %d\n", temp2, max);
	printf("ID: %d, �ּ��Ǹŷ�: %d\n", temp1, min);
	for (int i = 0; i < quantity; i++) {
		if (stocks[i] <= 2) {
			printf("��ǰID %d: ������%d\n", id[i], stocks[i]);
		}
	}
	/*for(int i = 0; i < quantity; i++) {
		printf("�Ǹŷ� ����: %d", sq[i]);
	}*/
	
	free(icq);
	free(sq);
	free(stocks);
	free(id);

	return 0;
}