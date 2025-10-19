
//git add ".\C-programming(������)\ShoppingMalls3.c"
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
	// ���� �ִ� ���ӵ� ������� ��� ����
	while ((c = getchar()) != '\n' && c != EOF) { /* skip */ }
	
}

int print_menu(void) {
	int menu = 0;
	printf("���ϴ� �޴��� �����Ͻÿ�.\n");
	printf("(1. �԰�, 2. �Ǹ�, 3. ������Ȳ. 4. ��ü��Ȳ, 5. ����)\n");
	if (scanf("%d", &menu) != 1)
		return -1;
	if (menu < 1 || menu > 5)
		return -1;
	return menu;
}

void input_received_items(ITEM* received, int size, int quantity, int* r_count) {
	*r_count = 0;
	printf("�԰� �޴� ����: ��ǰ ID, �̸�, �԰�, �Ǹ� ������ %d�� ���Ϸ� �Է��ϼ���.\n", quantity);
	while (1) {
		
		printf("��ǰ ID: ");
		scanf("%d", &((received+*r_count)->id));// (received + count)->id;
		printf("��ǰ �̸�: ");
		scanf("%s", received[*r_count].name); //�̸��� ��ü�� �迭�̹Ƿ� & �ʿ� ����
		printf("�԰�: ");
		scanf("%lf", &received[*r_count].price);
		printf("�Ǹ� ����: ");
		scanf("%lf", &received[*r_count].total_sales);
		(*r_count)++;
		if (*r_count >= quantity) {
			printf("�ִ� �Է� ������ �����߽��ϴ�.\n");
			break;
		}
		printf("�� %d���� ��ǰ�� �ԷµǾ����ϴ�..\n", *r_count);
	}
}

void input_saled_items(ITEM* saled, ITEM* received, int quantity, int* saled_count) {
	*saled_count = 0;
	while (1) {
		int index;
		printf("��ǰ ID(0���� 4)�� �Է��Ͽ� �Ǹŵ� ��ǰ�� ����ϼ���.\n");
		scanf("%d", &index);
		if (received[index].id == -1) {
			printf("�ش� ID�� ��ǰ�� �������� �ʽ��ϴ�.\n");
			return;
		}
		printf("�Ǹŵ� ��ǰ ������ �Է��ϼ���: ");
		scanf("%lf", &saled[index].total_sales);
		(*saled_count)++;
		if (*saled_count >= quantity) {
			printf("�ִ� �Է� ������ �����߽��ϴ�.\n");
			break;
		}
	}
}

void show_individual_status(ITEM* received, ITEM* saled, int size) {
	printf("���� ��Ȳ ���: \n");
	printf("���� ���� ��ǰ ������ ID�� �Է��ϼ��� (0���� 4����)");
	int index;
	char ch;
	scanf("%d", &index);
	while ((ch = getchar()) != EOF) {
		if (received[index].id == -1) {
			printf("�ش� ID�� ��ǰ�� �������� �ʽ��ϴ�. \n");
			return;
		}
		else {
			printf("�ش� ID: [%d]�� ��ǰ ����\n", index);
			printf("��ǰ��: %s, �԰�: %lf, �Ǹŷ�: %lf, �ǸŰ���: %.2lf\n", (received + index)->name, (received + index)->price, (saled + index)->total_sales, (received + index)->total_sales);
			printf("�����Ͻ÷��� ctrl+z Ŭ��");
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

	
	printf("��ǰ ������ �Է��Ͽ��ֽʽÿ�.(1~%d)������ �� ����", MAX_PRODUCTS);
	if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > MAX_PRODUCTS) {
		fprintf(stderr, "�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	

	while (1) {
		int menu = print_menu();
		if (menu == -1) {
			fprintf(stderr, "�߸��� �Է��Դϴ�(1~4)�� �Է����ּ���.\n");
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
			printf("��ü ��Ȳ ���: �� �Ǹ����� %.2lf�Դϴ�.\n", rated_sales);
			break;
		case 5:
			return 0;
		default:
			fprintf(stderr, "�߸��� �Է��Դϴ�(1~4)�� �Է����ּ���.\n");
			break;
		}
	}
	return 0;
}