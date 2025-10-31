// �ѹ��� �ּ�: Ctrl+K, Ctrl+C
// �ּ� ����   : Ctrl+K, Ctrl+U
// git add ".\C-programming(������)\ShoppingMalls4.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PRODUCTS 5

typedef struct item {
    int    id;                          // ��ǰ ID (����)
    char   name[MAX_NAME_LEN];          // ��ǰ��
    double price;                       // �Ǹ� ���� (�ܰ�)
    double stocked;                     // �԰�(���) �ѷ�
    double sold;                        // �Ǹ� �ѷ�
} ITEM;

static void drain_newlines(void) {
    int c;
    // ���� �ִ� ���ӵ� ������� ��� ����
    while ((c = getchar()) != '\n' && c != EOF) { /* skip */ }

}

static int find_index_by_id(const ITEM* arr, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id) return i;
    }
    return -1;
}

static void init_items(ITEM* arr, int n) { //����ü �迭�� �ڵ����� 0�� �ƴϴ�
    for (int i = 0; i < n; i++) {          //(ITEM items[MAX_PRODUCTS];)�� �ʱ�ȭ���� �ʽ��ϴ�.
        arr[i].id = -1;              // ������� ��Ƽ��
        arr[i].name[0] = '\0';
        arr[i].price = 0.0;
        arr[i].stocked = 0.0;
        arr[i].sold = 0.0;
    }
}

static int print_menu(void) {
    int menu = 0;
    printf("\n���ϴ� �޴��� �����Ͻÿ�.\n");
    printf("(1. �԰�, 2. �Ǹ�, 3. ������Ȳ, 4. ��ü��Ȳ, 5. ����)\n");
    printf("�޴�: ");
    if (scanf("%d", &menu) != 1) {
        // �߸��� �Է� ���� ����
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    if (menu < 1 || menu > 5) return -1;
    return menu;
}

// �԰� �Է�: ID ���� �Է� �� ����. �ִ� quantity��
static void input_received_items(ITEM* received, int quantity, int* r_count) {
    *r_count = 0;
    printf("\n[�԰�] ��ǰ ID(����, ���� �Է� �� ����), �̸�, �԰�, �ǸŰ���(�ܰ�)�� �Է�.\n");
    printf("�ִ� %d������ �Է� �����մϴ�.\n", quantity);
    int ch;
	drain_newlines(); // �����ִ� ���� ����
    for (int i = 0; i < quantity; i++) {
        int id;
        printf("\n��ǰ ID: ");
        int r = scanf("%d", &id);
        if (id < 0) {
            printf("�԰� �Է� ����.\n");
            break;
        }
        if (r != 1) {
			drain_newlines();
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            i--; // ���� ���� �ٽ� �õ�
            continue;
        }
        
        if (find_index_by_id(received, quantity, id) != -1) {
            printf("�̹� �����ϴ� ID�Դϴ�, ������Ʈ �� �Է°��� �����Ͻÿ�.\n");
            received[i].id = id;
        }
        received[i].id = id;

        printf("��ǰ �̸�(���� ����): ");
        if (scanf("%49s", received[i].name) != 1) { //scanf()�� �Է¹��� �׸��� ����(number of successfully assigned items)�� ��ȯ�մϴ�.
			drain_newlines();
            printf("�Է� ����. �ٽ� �õ�.\n");
            i--;
            continue;
        }

        printf("�԰�(�Ǽ�): ");
        if (scanf("%lf", &received[i].stocked) != 1 || received[i].stocked < 0) {
			drain_newlines();
            printf("�Է� ����. �ٽ� �õ�.\n");
            i--;
            continue;
        }

        printf("�Ǹ� ����(�ܰ�, �Ǽ�): ");
        if (scanf("%lf", &received[i].price) != 1 || received[i].price < 0) {
            drain_newlines();
            printf("�Է� ����. �ٽ� �õ�.\n");
            i--;
            continue;
        }

		
        (*r_count)++;

        printf("���� �Էµ� ��ǰ ��: %d\n", *r_count);
    }
}

// �Ǹ� �Է�: �����ϴ� ID�� ��� �Ǹż����� ����
static void input_saled_items(ITEM* received, int quantity, int* saled_count) {
    *saled_count = 0;
    printf("\n[�Ǹ�] ��ǰ ID(����)�� �Է��ϸ� �Ǹ� ������ �����մϴ�. ���� �Է� �� ����.\n");
    // ��Ȳ ����Ʈ
    for (int i = 0; i < quantity; i++) {
        if (received[i].id != -1) { //-1�� ���α׷��Ӱ� ���� ���� "��� ����" �Ǵ� "������"�� ��ȣ
            printf("ID:%d, ��ǰ��:%s, ���(�԰�):%.2f, �ǸŴ���:%.2f, �ܰ�:%.2f\n",
                received[i].id, received[i].name, received[i].stocked, received[i].sold, received[i].price);
        }
    }

    while(1) {
        int id;
        printf("\n�Ǹ��� ��ǰ ID: (���� �Է½� ����)");
        if (scanf("%d", &id) != 1) {
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("�Է� ����. �ٽ� �õ�.\n");
            continue;
        }
        if (id < 0) {
            printf("�Ǹ� �Է� ����.\n");
            break;
        }
        
        int idx = find_index_by_id(received, quantity, id);
        if (idx == -1) {
            printf("�ش� ID�� ��ǰ�� �������� �ʽ��ϴ�.\n");
            continue;
        }

        double qty;
        printf("�Ǹ� ����: ");
        if (scanf("%lf", &qty) != 1 || qty <= 0) {
            drain_newlines();
            printf("���� �Է� ����. �ٽ� �õ�.\n");
            continue;
        }
        if (received[idx].sold + qty > received[idx].stocked) {
            printf("��� ����: ���� �Ǹ� ���� %2f, �԰� %.2f\n", received[idx].sold, received[idx].stocked);
            continue;
        }

        received[idx].sold += qty;
        (*saled_count)++;
        printf("�Ǹ� ��� �Ϸ�. (ID:%d) ���� �Ǹ�: %.2f\n", id, received[idx].sold);
        if(*saled_count >= quantity) {
            printf("�ִ� �Ǹ� ��� ������ �����߽��ϴ�.\n");
            break;
		}
    }
}

static void show_individual_status(ITEM* received, int quantity) {
    printf("\n[���� ��Ȳ] ���� ���� ��ǰ ID �Է�: ");
    int id;
    if (scanf("%d", &id) != 1) {
        drain_newlines();
        printf("�Է� ����.\n");
        return;
    }
    int idx = find_index_by_id(received, quantity, id);
    if (idx == -1) {
        printf("�ش� ID�� ��ǰ�� �������� �ʽ��ϴ�.\n");
        return;
    }
    ITEM* p = &received[idx]; //��received(ITEM) �迭�� idx��° ����� �ּҸ� ����Ű�� ������ p�� �����.��
                              // �׷��� p�� ITEM ����ü �� ���� ����Ű�� ������ ������ �˴ϴ�.
							  // ������ �̸��� p�� ª�� ������, ����Ű�� ����� received[idx]��� ITEM ����ü �� ���Դϴ�.
                              // ��ڷ����� ����(�� �� ITEM* Ÿ��)������ ������ �ٸ��ϴ�.
    double revenue = p->sold * p->price;
    printf("ID:%d | ��ǰ��:%s | �԰�:%.2f | �Ǹŷ�:%.2f | �ǸŰ���:%.2f | ����:%.2f\n",
        p->id, p->name, p->stocked, p->sold, p->price, revenue);
}

static double compute_total_sales_rate(const ITEM* arr, int n) {
    double total_stocked = 0.0, total_sold = 0.0;
    for (int i = 0; i < n; i++) {
        if (arr[i].id != -1) {
            total_stocked += arr[i].stocked;
            total_sold += arr[i].sold;
        }
    }
    if (total_stocked <= 0.0) return 0.0;
    return (total_sold / total_stocked) * 100.0;
}
static double compute_revenue(const ITEM* arr, int n) {
    double total_revenue = 0.0;
    double revenue = 0.0;
    for (int i = 0; i < n; i++) {
        if (arr[i].id != -1) {
            revenue += arr[i].sold * arr[i].price;
            total_revenue += revenue;
            printf("ID:%d | %s | �԰�:%.2f | �Ǹ�:%.2f | �ܰ�:%.2f | ����:%.2f\n",
                arr[i].id, arr[i].name, arr[i].stocked, arr[i].sold, arr[i].price, revenue);
        }
    }
    return total_revenue;
}
static void show_overall_status(const ITEM* arr, int n) {
    printf("\n[��ü ��Ȳ]\n");
    double total_revenue = 0.0;
	total_revenue = compute_revenue(arr, n);
    double rate = compute_total_sales_rate(arr, n);
    printf("�� �Ǹ���: %.2f%%, �� ����: %.2f\n", rate, total_revenue);
}

int main(void) {
    int quantity;
    int r_count = 0;
    int saled_count = 0;

    ITEM items[MAX_PRODUCTS];
    init_items(items, MAX_PRODUCTS);

    printf("��ǰ ������ �Է��Ͻʽÿ� (1~%d): ", MAX_PRODUCTS);
    if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > MAX_PRODUCTS) {
        fprintf(stderr, "�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n");
        return 1;
    }

    while (1) {
        int menu = print_menu();
        if (menu == -1) {
            fprintf(stderr, "�߸��� �Է��Դϴ�(1~5 �� �Է�).\n");
            continue;
        }

        switch (menu) {
        case 1:
            input_received_items(items, quantity, &r_count);
            break;
        case 2:
            input_saled_items(items, quantity, &saled_count);
            break;
        case 3:
            show_individual_status(items, quantity);
            break;
        case 4:
            show_overall_status(items, quantity);
            break;
        case 5:
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            fprintf(stderr, "�߸��� �Է��Դϴ�(1~5 �� �Է�).\n");
            break;
        }
    }
    // return 0; // �������� ����
}
