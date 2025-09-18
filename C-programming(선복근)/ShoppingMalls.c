#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

//void swap(int* a, int* b) {
//	int temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}
//git add ".\C-programming(������)\ShoppingMalls.c" staging����

void compute_stock(int* stocks, int* icq, int* sq, int n)
{
	for (int i = 0; i < n; i++) {
		stocks[i] = icq[i] - sq[i];
	}
}
void fill_id(int* id, int n) {
	for (int i = 0; i < n; i++) {
		id[i] = i + 1;
	}
}
void minmax_with_id(int* sq, int* id, int n, int* min, int* max, int* min_id, int* max_id) {
	*min = sq[0];
	*max = sq[0];
	*min_id = id[0];
	*max_id = id[0];
	for (int j = 1; j < n; j++) {
		if (*min > sq[j]) {//�ּҰ� ���ϴ� �ڵ�
			*min = sq[j];
			*min_id = id[j];
		}
		if (*max < sq[j]) {//�ִ밪 ���ϴ� �ڵ�
			*max = sq[j];
			*max_id = id[j];
		}
	}
}
void print_low_stock(int* stocks, int* id, int n) {
	for (int i = 0; i < n; i++) {
		if (stocks[i] <= 2) {
			printf("��ǰID %d: ������%d\n", id[i], stocks[i]);
		}
	}
}
float sales_rate(int total_icq, int total_sq) {
	return ((float)total_sq / total_icq) * 100;
}
int main(void) {
	int quantity;
	int products;
	int sales;
	
	int total_sq = 0;
	int total_icq = 0;
	int min, max;
	int temp1, temp2;
	
	

	int* icq = NULL;
	int* sq = NULL;
	int* stocks = NULL;
	int* id = NULL;

	icq = malloc(MAX_SIZE * sizeof(int));//incoming quantity
	sq = malloc(MAX_SIZE * sizeof(int)); //saled quantity
	stocks = malloc(MAX_SIZE * sizeof(int));
	id = malloc(MAX_SIZE * sizeof(int));
	printf("��ǰ ������ �Է��Ͽ��ֽʽÿ�.(1~%d)������ �� ����", MAX_SIZE);
	if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > MAX_SIZE) {
		fprintf(stderr, "�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n");
		free(icq);
		free(sq);
		free(stocks);
		free(id);
		return 1;
	}
	

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
	compute_stock(stocks, icq, sq, quantity);
	fill_id(id, quantity);
	minmax_with_id(sq, id, quantity, &min, &max, &temp1, &temp2);
	float rate = sales_rate(total_icq, total_sq);
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
	printf("�� �Ǹŷ�: %d\n�Ǹ���: %.2f\n", total_sq, rate);
	printf("ID: %d, �ִ� �Ǹŷ�: %d\n", temp2, max);
	printf("ID: %d, �ּ��Ǹŷ�: %d\n", temp1, min);
	print_low_stock(stocks, id, quantity);
	/*for(int i = 0; i < quantity; i++) {
		printf("�Ǹŷ� ����: %d", sq[i]);
	}*/
	
	free(icq);
	free(sq);
	free(stocks);
	free(id);

	return 0;
}