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
	printf("상품 개수를 입력하여주십시오.(1~%d)사이의 값 한정", MAX_SIZE);
	scanf("%d", &quantity);

	icq = realloc(icq, quantity * sizeof(int));
	sq = realloc(sq, quantity * sizeof(int));
	stocks = realloc(stocks, quantity * sizeof(int));
	id = realloc(id, quantity * sizeof(int));

	for (int i = 0; i < quantity; i++) {
		printf("입고수량을 하나씩 입력하십시오.");
		scanf("%d", &products);
		icq[i] = products;
		total_icq += icq[i];
	}
	for (int i = 0; i < quantity; i++) {
		printf("판매수량을 하나씩 입력하십시오.");
		printf("%d보다 작아야합니다.", icq[i]);
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
		if (min > sq[j]) {//최소값 구하는 코드
			min = sq[j];
			temp1 = id[j];
		}
		if (max < sq[j]) {//최대값 구하는 코드
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
		printf("모든 상품의 재고 출력: %d\n", stocks[i]);
	}
	printf("총 판매량: %d\n판매율: %.2f\n", total_sq, ((float)total_sq / total_icq)*100);
	printf("ID: %d, 최대 판매량: %d\n", temp2, max);
	printf("ID: %d, 최소판매량: %d\n", temp1, min);
	for (int i = 0; i < quantity; i++) {
		if (stocks[i] <= 2) {
			printf("상품ID %d: 재고부족%d\n", id[i], stocks[i]);
		}
	}
	/*for(int i = 0; i < quantity; i++) {
		printf("판매량 순위: %d", sq[i]);
	}*/
	
	free(icq);
	free(sq);
	free(stocks);
	free(id);

	return 0;
}