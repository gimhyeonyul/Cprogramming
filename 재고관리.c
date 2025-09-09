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
	printf("상품 개수를 입력하여주십시오.(1~%d)사이의 값 한정", MAX_SIZE);
	scanf("%d", &quantity);

	icq = realloc(icq, quantity * sizeof(int));
	sq = realloc(sq, quantity * sizeof(int));
	stocks = realloc(stocks, quantity * sizeof(int));

	for (int i = 0; i < quantity; i++) {
		printf("입고수량을 하나씩 입력하십시오.");
		scanf("%d", &products);
		icq[i] = products;
	}
	for (int i = 0; i < quantity; i++) {
		printf("판매수량을 하나씩 입력하십시오.");
		printf("%d보다 작아야합니다.", icq[i]);
		scanf("%d", &sales);
		sq[i] = sales;
	}
	for (int i = 0; i < quantity; i++) {
		stocks[i] = icq[i] - sq[i];
	}
	printf("ID를 입력하시오 (%d 이내의 값을 입력해주세요.)", quantity);
	scanf("%d", &id);
	
	if (id < 0 || id >= quantity) {
		printf("해당 ID는 상품개수를 초과할수 없습니다.");
	}
	else {
		printf("ID에 해당하는 제품의 재고 수량:%d\n", stocks[id]);
	}
	for (int i = 0; i < quantity; i++) {
		printf("모든 상품의 재고 출력: %d\n", stocks[i]);
	}

	free(icq);
	free(sq);
	free(stocks);

	return 0;
}