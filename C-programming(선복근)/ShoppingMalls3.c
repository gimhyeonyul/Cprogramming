//git add ".\c-programming(������)\shoppingmalls.c"
#include <stdio.h>
#include <stdlib.h>
#define max_size 100
#define MAX_NAME_LEN 50
#define MAX_PRODUCTS 5


static void drain_newlines(void) {
	int c;
	// ���� �ִ� ���ӵ� ������� ��� ����
	while ((c = getchar()) == '\n') { /* skip */ }
	if (c != EOF) ungetc(c, stdin);   // �� ���� �ǵ��� ���� ���� �б� ����
}
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
void print_low_stock(int* stocks, int* id, int n ,char product_names[][MAX_NAME_LEN]) {
	for (int i = 0; i < n; i++) {
		if (stocks[i] <= 2) {
			printf("��ǰid %d ��ǰ��: %s ,������(%d)\n", id[i], product_names[i], stocks[i]);
		}
	}
}
float sales_rate(int total_icq, int total_sq) {
	return ((float)total_sq / total_icq) * 100;
}
int print_menu(void) {
	int menu = 0;
	printf("���ϴ� �޴��� �����Ͻÿ�.\n");
	printf("(1.�԰�, 2.�Ǹ�, 3.��ǰ��Ȳ, 4.��ǰ�� �Է� 5.����)\n");
	if(scanf("%d", &menu) != 1)
		return -1;
	if (menu < 1 || menu > 5) 
		return -1;
	return menu;
}
void action_receive(int* icq,int* total_icq,int* id, int n) {
	int choice;
	int i = 0;
	static int icq_input = 0;
	printf("�԰���� �Է�: ��ü ��ǰ �԰���� �Է� 1, ���� ��ǰ �Է� 2�� ����\n");
	scanf("%d", &choice);
	if (choice == 1) {
		printf("�԰������ �Է��Ͻÿ�. ��: (10 20 30 40 50'\\n')\n");
		while (i < n && scanf("%d", &icq[i]) == 1) {
			*total_icq += icq[i];
			i++;
			if (getchar() == '\n')
				break;
		}
		icq_input = 1;
	}
	else if (choice == 2) {
		if(!icq_input){
			printf("���� ��ü ��ǰ �԰������ �Է��Ͽ��ֽʽÿ�.\n");
			return;
		}
		else {
			for (int i = 0; i < n; i++) {
				id[i] = i + 1;
			}
		}
		int id_input = 0;
		printf("�ñ��Ͻ� ��ǰ�� ���̵� �Է��Ͻÿ� 1���� %d����.\n", n);
		scanf("%d", &id_input);
		printf("�ش� id�� �԰������ %d�Դϴ�. \n", icq[id_input - 1]);
	}
	else {
		fprintf(stderr, "�߸��� �����Դϴ�(1)�Ǵ�(2).\n");
	}
}
void action_sales(int* sq, int* icq, int* id,int* total_sq,int n) {
	static int sales_input = 0;
	int choice;
	int i = 0;
	printf("�Ǹż��� �Է�: ��ü ��ǰ �Ǹż��� �Է� 1, ���� ��ǰ �Է� 2�� ����\n");
	scanf("%d", &choice);
	if (choice == 1) {
		printf("�Ǹż����� �Է��Ͻÿ�. (�԰� ���� �ʰ��ϸ� �ȉϴϴ�) ��: (9 19 29 39 49'\\n')\n");
		while (i < n && scanf("%d", &sq[i]) == 1) {
			*total_sq += sq[i];
			i++;
			if (getchar() == '\n')
				break;
		}
		sales_input = 1;
	}
	else if (choice == 2) {
		if(!sales_input) {
			printf("���� ��ü ��ǰ �Ǹż����� �Է��Ͽ��ֽʽÿ�.\n");
			return;
		}
		else {
			for (int i = 0; i < n; i++) {
				id[i] = i + 1;
			}
		}
		
		int id_input = 0;
		printf("���� ��ǰ�� ���̵� �Է��Ͻÿ� 1���� %d����.\n", n);
		scanf("%d", &id_input);
		printf("�ش� id�� �԰������ %d�Դϴ�. \n", icq[id_input - 1]);
		
	}
	else {
		fprintf(stderr, "�߸��� �����Դϴ�(1)�Ǵ�(2).\n");
	}
}
void action_status(int* icq, int* sq, int* stocks, int* id,
	int n, int total_icq, int total_sq, char product_names[][MAX_NAME_LEN]) {
	int min, max, temp1, temp2;
	compute_stock(stocks, icq, sq, n);
	for (int i = 0; i < n; i++) {
		printf("��� ��ǰ�� ��� ���: %d\n", stocks[i]);
	}
	float rate = sales_rate(total_icq, total_sq);
	printf("�� �Ǹŷ�: %d\n�Ǹ���: %.2f\n", total_sq, rate);
	minmax_with_id(sq, id, n, &min, &max, &temp1, &temp2);
	printf("id: %d, ��ǰ��: %s, �ִ� �Ǹŷ�: %d\n", temp2, product_names[temp2-1], max);
	printf("id: %d, ��ǰ��: %s, �ּ��Ǹŷ�: %d\n", temp1, product_names[temp1-1], min);
	print_low_stock(stocks, id, n, product_names);
}
void action_naming(char product_names[MAX_PRODUCTS][MAX_NAME_LEN]) {
	for (int i = 0; i < MAX_PRODUCTS; i++) {
		printf("ID %d��ǰ���� �Է��Ͻÿ�: (�ִ� %d��) \n", i + 1, MAX_PRODUCTS);
		drain_newlines();
		int products;
		int j = 0;
		while ((products = getchar()) != EOF && products != '\n') {
			if(j < MAX_NAME_LEN - 1) {
				product_names[i][j++] = (char)products;
			}
			product_names[i][j] = '\0';
			if (product_names[i][0] == '\0') {
				fprintf(stderr, "��ǰ���� �Էµ��� �ʾҽ��ϴ�. �ٽ� �Է����ּ���.\n");
				i--;
				continue;
			}
		}
	}
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

	char product_names[max_size][MAX_NAME_LEN]; 

	icq = malloc(max_size * sizeof(int));//incoming quantity
	sq = malloc(max_size * sizeof(int)); //saled quantity
	stocks = malloc(max_size * sizeof(int));
	id = malloc(max_size * sizeof(int));
	printf("��ǰ ������ �Է��Ͽ��ֽʽÿ�.(1~%d)������ �� ����", max_size);
	if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > max_size) {
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
	fill_id(id, quantity);
	while(1) {
		int menu = print_menu();
		if(menu == -1){
			fprintf(stderr, "�߸��� �Է��Դϴ�(1~4)�� �Է����ּ���.\n");
			continue;
		}

		switch (menu) {
		case 1:
			action_receive(icq,&total_icq,id, quantity);
			break;
		case 2:
			action_sales(sq, icq, id, &total_sq, quantity);
			break;
		case 3:
			action_status(icq, sq, stocks, id,
				quantity, total_icq, total_sq, product_names);
			break;
		case 4:
			action_naming(product_names);
			break;
		case 5:
			return 0;
		default:
			fprintf(stderr, "�߸��� �Է��Դϴ�(1~4)�� �Է����ּ���.\n");
			break;
		}
	}
	free(icq);
	free(sq);
	free(stocks);
	free(id);

	return 0;
}