#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

//void swap(int* a, int* b) {
//	int temp;
//	temp = *a;
//	*a = *b;
//	*b = temp;
//}
//git add ".\C-programming(선복근)\ShoppingMalls.c" staging형식

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
		if (*min > sq[j]) {//최소값 구하는 코드
			*min = sq[j];
			*min_id = id[j];
		}
		if (*max < sq[j]) {//최대값 구하는 코드
			*max = sq[j];
			*max_id = id[j];
		}
	}
}
void print_low_stock(int* stocks, int* id, int n) {
	for (int i = 0; i < n; i++) {
		if (stocks[i] <= 2) {
			printf("상품ID %d: 재고부족%d\n", id[i], stocks[i]);
		}
	}
}
float sales_rate(int total_icq, int total_sq) {
	return ((float)total_sq / total_icq) * 100;
}
int print_menu(void) {
	int menu = 0;
	printf("원하는 메뉴를 선택하시오.\n");
	printf("(1.입고, 2.판매, 3.상품현황, 4.종료)\n");
	if(scanf("%d", &menu) != 1)
		return -1;
	if (menu < 1 || menu > 4) 
		return -1;
	return menu;
}
void action_receive(int* icq,int* total_icq,int* id, int n, int products) {
	int choice;
	printf("입고수량 입력: 전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택\n");
	scanf("%d", &choice);
	if (choice == 1) {
		for(int i = 0; i < n; i++){
			printf("입고수량을 하나씩 입력하십시오.\n");
			scanf("%d", &products);
			*total_icq += products;
			icq[i] = products;
		}
	}
	else if (choice == 2) {
		for (int i = 0; i < n; i++) {
			id[i] = i + 1;
		}
		int id_input = 0;
		printf("개별 상품의 아이디를 입력하시오 1부터 %d까지.\n", n);
		scanf("%d", &id_input);
		printf("해당 상품의 입고수량을 입력하시오.\n");
		scanf("%d", &products);
		icq[id_input - 1] = products;
		printf("입고수량: %d", icq[id_input - 1]);
	}
	else {
		fprintf(stderr, "잘못된 선택입니다(1)또는(2).\n");
	}
}
void action_sales(int* sq, int* icq, int* id,int* total_sq,int n, int products) {
	int choice;
	printf("판매수량 입력: 전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택\n");
	scanf("%d", &choice);
	if (choice == 1) {
		for (int i = 0; i < n; i++) {
			printf("판매수량을 하나씩 입력하십시오.");
			printf("%d보다 작아야합니다.", icq[i]);
			scanf("%d", &products);
			*total_sq += products;
			sq[i] = products;
		}
	}
	else if (choice == 2) {
		for (int i = 0; i < n; i++) {
			id[i] = i + 1;
		}
		int id_input = 0;
		printf("개별 상품의 아이디를 입력하시오 1부터 %d까지.\n", n);
		scanf("%d", &id_input);
		printf("해당 상품의 판매수량을 입력하시오.\n");
		scanf("%d", &products);
		sq[id_input - 1] = products;
		printf("판매수량: %d", sq[id_input - 1]);
	}
	else {
		fprintf(stderr, "잘못된 선택입니다(1)또는(2).\n");
	}
}
void action_status(int* icq, int* sq, int* stocks, int* id,
	int n, int total_icq, int total_sq) {
	int min, max, temp1, temp2;
	compute_stock(stocks, icq, sq, n);
	for (int i = 0; i < n; i++) {
		printf("모든 상품의 재고 출력: %d\n", stocks[i]);
	}
	float rate = sales_rate(total_icq, total_sq);
	printf("총 판매량: %d\n판매율: %.2f\n", total_sq, rate);
	minmax_with_id(sq, id, n, &min, &max, &temp1, &temp2);
	printf("ID: %d, 최대 판매량: %d\n", temp2, max);
	printf("ID: %d, 최소판매량: %d\n", temp1, min);
	print_low_stock(stocks, id, n);
}



int main(void) {
	int quantity;
	int products = 0;
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
	printf("상품 개수를 입력하여주십시오.(1~%d)사이의 값 한정", MAX_SIZE);
	if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > MAX_SIZE) {
		fprintf(stderr, "잘못된 입력입니다. 프로그램을 종료합니다.\n");
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
	fill_id(id, quantity);
	for (;;) {
		int menu = print_menu();
		if(menu == -1){
			fprintf(stderr, "잘못된 입력입니다(1~4)중 입력해주세요.\n");
			continue;
		}

		switch (menu) {
		case 1:
			action_receive(icq,&total_icq,id, quantity, products);
			break;
		case 2:
			action_sales(sq, icq, id, &total_sq, quantity, products);
			break;
		case 3:
			action_status(icq, sq, stocks, id,
				quantity, total_icq, total_sq);
			break;
		case 4:
			return 0;
		default:
			fprintf(stderr, "잘못된 입력입니다(1~4)중 입력해주세요.\n");
			break;
		}
	}

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
	fill_id(id, quantity);
	/*for (int i = 0; i < quantity - 1; i++) {
		int most = i;
		for (int j = i + 1; j < quantity; j++) {
			if (sq[most] < sq[j]) {
				most = j;
			}
		}
		swap(&sq[i], &sq[most]);
	}*/
	
	/*for(int i = 0; i < quantity; i++) {
		printf("판매량 순위: %d", sq[i]);
	}*/
	
	free(icq);
	free(sq);
	free(stocks);
	free(id);

	return 0;
}