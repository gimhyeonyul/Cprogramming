
//git add ".\C-programming(선복근)\ShoppingMalls3.c"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN 50
#define MAX_PRODUCTS 5

typedef struct item {
	int id;
	char name[50];
	double price;
	double total_sales;
} ITEM;
static void drain_newlines(void) {
	int c;
	// 남아 있는 연속된 개행들을 모두 제거
	while ((c = getchar()) != '\n' && c != EOF) { /* skip */ }
	
}

int print_menu(void) {
	int menu = 0;
	printf("원하는 메뉴를 선택하시오.\n");
	printf("(1. 입고, 2. 판매, 3. 개별현황. 4. 전체현황, 5. 종료)\n");
	if (scanf("%d", &menu) != 1)
		return -1;
	if (menu < 1 || menu > 5)
		return -1;
	return menu;
}

void input_received_items(ITEM* received, int size, int quantity, int* r_count) {
	*r_count = 0;
	printf("입고 메뉴 실행: 상품 ID, 이름, 입고량, 판매 가격을 %d개 이하로 입력하세요.\n", quantity);
	while (1) {
		
		printf("상품 ID: ");
		scanf("%d", &((received+*r_count)->id));// (received + count)->id;
		printf("상품 이름: ");
		scanf("%s", received[*r_count].name); //이름은 자체가 배열이므로 & 필요 없음
		printf("입고량: ");
		scanf("%lf", &received[*r_count].price);
		printf("판매 가격: ");
		scanf("%lf", &received[*r_count].total_sales);
		(*r_count)++;
		if (*r_count >= quantity) {
			printf("최대 입력 개수에 도달했습니다.\n");
			break;
		}
		printf("총 %d개의 상품이 입력되었습니다..\n", *r_count);
	}
}

void input_saled_items(ITEM* saled, ITEM* received, int quantity, int* saled_count) {
	*saled_count = 0;
	while (1) {
		int index;
		printf("상품 ID(0부터 4)를 입력하여 판매된 상품을 기록하세요.\n");
		scanf("%d", &index);
		if (received[index].id == -1) {
			printf("해당 ID의 상품이 존재하지 않습니다.\n");
			return;
		}
		printf("판매된 상품 수량을 입력하세요: ");
		scanf("%lf", &saled[index].total_sales);
		(*saled_count)++;
		if (*saled_count >= quantity) {
			printf("최대 입력 개수에 도달했습니다.\n");
			break;
		}
	}
}

void show_individual_status(ITEM* received, ITEM* saled, int size) {
	printf("개별 현황 출력: \n");
	printf("보고 싶은 상품 정보를 ID로 입력하세요 (0부터 4까지)");
	int index;
	char ch;
	scanf("%d", &index);
	while ((ch = getchar()) != EOF) {
		if (received[index].id == -1) {
			printf("해당 ID의 상품이 존재하지 않습니다. \n");
			return;
		}
		else {
			printf("해당 ID: [%d]의 상품 정보\n", index);
			printf("상품명: %s, 입고량: %lf, 판매량: %lf, 판매가격: %.2lf\n", (received + index)->name, (received + index)->price, (saled + index)->total_sales, (received + index)->total_sales);
			printf("종료하시려면 ctrl+z 클릭");
		}
	}
}

double compute_total_sales_rate(ITEM* saled, ITEM* received, int saled_count, int r_count) {
	double rate;
	double s_total = 0.0;
	double r_total = 0.0;
	for (int i = 0; i < saled_count; i++) {
		s_total += saled[i].total_sales;
	}
	for (int i = 0; i < r_count; i++) {
		r_total += received[i].price;
	}
	rate = ((double)s_total / r_total) * 100;
	return rate;
}
int main(void) {
	int quantity;
	int products = 0;

	int r_count;
	int saled_count;
	double rated_sales;



	

	char product_names[MAX_PRODUCTS][MAX_NAME_LEN];
	ITEM sales_items[MAX_PRODUCTS] = { 0 };
	ITEM receive_items[MAX_PRODUCTS] = { 0 };

	
	printf("상품 개수를 입력하여주십시오.(1~%d)사이의 값 한정", MAX_PRODUCTS);
	if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > MAX_PRODUCTS) {
		fprintf(stderr, "잘못된 입력입니다. 프로그램을 종료합니다.\n");
		return 1;
	}
	

	while (1) {
		int menu = print_menu();
		if (menu == -1) {
			fprintf(stderr, "잘못된 입력입니다(1~4)중 입력해주세요.\n");
			continue;
		}

		switch (menu) {
		case 1:
			input_received_items(receive_items, MAX_PRODUCTS, quantity, &r_count);
			break;
		case 2:
			input_saled_items(sales_items, receive_items, quantity, &saled_count);
			break;
		case 3:
			show_individual_status(receive_items, sales_items, MAX_PRODUCTS);
			break;
		case 4:
			rated_sales = compute_total_sales_rate(sales_items, receive_items, saled_count, r_count);
			printf("전체 현황 출력: 총 판매율은 %.2lf입니다.\n", rated_sales);
			break;
		case 5:
			return 0;
		default:
			fprintf(stderr, "잘못된 입력입니다(1~4)중 입력해주세요.\n");
			break;
		}
	}
	return 0;
}