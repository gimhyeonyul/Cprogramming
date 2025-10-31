// 한번에 주석: Ctrl+K, Ctrl+C
// 주석 해제   : Ctrl+K, Ctrl+U
// git add ".\C-programming(선복근)\ShoppingMalls4.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PRODUCTS 5

typedef struct item {
    int    id;                          // 상품 ID (정수)
    char   name[MAX_NAME_LEN];          // 상품명
    double price;                       // 판매 가격 (단가)
    double stocked;                     // 입고(재고) 총량
    double sold;                        // 판매 총량
} ITEM;

static void drain_newlines(void) {
    int c;
    // 남아 있는 연속된 개행들을 모두 제거
    while ((c = getchar()) != '\n' && c != EOF) { /* skip */ }

}

static int find_index_by_id(const ITEM* arr, int n, int id) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id) return i;
    }
    return -1;
}

static void init_items(ITEM* arr, int n) { //구조체 배열은 자동으로 0이 아니다
    for (int i = 0; i < n; i++) {          //(ITEM items[MAX_PRODUCTS];)는 초기화되지 않습니다.
        arr[i].id = -1;              // 비어있음 센티넬
        arr[i].name[0] = '\0';
        arr[i].price = 0.0;
        arr[i].stocked = 0.0;
        arr[i].sold = 0.0;
    }
}

static int print_menu(void) {
    int menu = 0;
    printf("\n원하는 메뉴를 선택하시오.\n");
    printf("(1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 종료)\n");
    printf("메뉴: ");
    if (scanf("%d", &menu) != 1) {
        // 잘못된 입력 버퍼 비우기
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
        return -1;
    }
    if (menu < 1 || menu > 5) return -1;
    return menu;
}

// 입고 입력: ID 음수 입력 시 종료. 최대 quantity개
static void input_received_items(ITEM* received, int quantity, int* r_count) {
    *r_count = 0;
    printf("\n[입고] 상품 ID(정수, 음수 입력 시 종료), 이름, 입고량, 판매가격(단가)을 입력.\n");
    printf("최대 %d개까지 입력 가능합니다.\n", quantity);
    int ch;
	drain_newlines(); // 남아있는 개행 제거
    for (int i = 0; i < quantity; i++) {
        int id;
        printf("\n상품 ID: ");
        int r = scanf("%d", &id);
        if (id < 0) {
            printf("입고 입력 종료.\n");
            break;
        }
        if (r != 1) {
			drain_newlines();
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            i--; // 같은 슬롯 다시 시도
            continue;
        }
        
        if (find_index_by_id(received, quantity, id) != -1) {
            printf("이미 존재하는 ID입니다, 업데이트 할 입력값을 기입하시오.\n");
            received[i].id = id;
        }
        received[i].id = id;

        printf("상품 이름(공백 없이): ");
        if (scanf("%49s", received[i].name) != 1) { //scanf()는 입력받은 항목의 개수(number of successfully assigned items)를 반환합니다.
			drain_newlines();
            printf("입력 오류. 다시 시도.\n");
            i--;
            continue;
        }

        printf("입고량(실수): ");
        if (scanf("%lf", &received[i].stocked) != 1 || received[i].stocked < 0) {
			drain_newlines();
            printf("입력 오류. 다시 시도.\n");
            i--;
            continue;
        }

        printf("판매 가격(단가, 실수): ");
        if (scanf("%lf", &received[i].price) != 1 || received[i].price < 0) {
            drain_newlines();
            printf("입력 오류. 다시 시도.\n");
            i--;
            continue;
        }

		
        (*r_count)++;

        printf("현재 입력된 상품 수: %d\n", *r_count);
    }
}

// 판매 입력: 존재하는 ID를 골라 판매수량을 누적
static void input_saled_items(ITEM* received, int quantity, int* saled_count) {
    *saled_count = 0;
    printf("\n[판매] 상품 ID(정수)를 입력하면 판매 수량을 누적합니다. 음수 입력 시 종료.\n");
    // 현황 리스트
    for (int i = 0; i < quantity; i++) {
        if (received[i].id != -1) { //-1은 프로그래머가 직접 정한 "비어 있음" 또는 "삭제됨"의 신호
            printf("ID:%d, 상품명:%s, 재고(입고):%.2f, 판매누적:%.2f, 단가:%.2f\n",
                received[i].id, received[i].name, received[i].stocked, received[i].sold, received[i].price);
        }
    }

    while(1) {
        int id;
        printf("\n판매할 상품 ID: (음수 입력시 종료)");
        if (scanf("%d", &id) != 1) {
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("입력 오류. 다시 시도.\n");
            continue;
        }
        if (id < 0) {
            printf("판매 입력 종료.\n");
            break;
        }
        
        int idx = find_index_by_id(received, quantity, id);
        if (idx == -1) {
            printf("해당 ID의 상품이 존재하지 않습니다.\n");
            continue;
        }

        double qty;
        printf("판매 수량: ");
        if (scanf("%lf", &qty) != 1 || qty <= 0) {
            drain_newlines();
            printf("수량 입력 오류. 다시 시도.\n");
            continue;
        }
        if (received[idx].sold + qty > received[idx].stocked) {
            printf("재고량 부족: 현재 판매 누적 %2f, 입고량 %.2f\n", received[idx].sold, received[idx].stocked);
            continue;
        }

        received[idx].sold += qty;
        (*saled_count)++;
        printf("판매 기록 완료. (ID:%d) 누적 판매: %.2f\n", id, received[idx].sold);
        if(*saled_count >= quantity) {
            printf("최대 판매 기록 개수에 도달했습니다.\n");
            break;
		}
    }
}

static void show_individual_status(ITEM* received, int quantity) {
    printf("\n[개별 현황] 보고 싶은 상품 ID 입력: ");
    int id;
    if (scanf("%d", &id) != 1) {
        drain_newlines();
        printf("입력 오류.\n");
        return;
    }
    int idx = find_index_by_id(received, quantity, id);
    if (idx == -1) {
        printf("해당 ID의 상품이 존재하지 않습니다.\n");
        return;
    }
    ITEM* p = &received[idx]; //“received(ITEM) 배열의 idx번째 요소의 주소를 가리키는 포인터 p를 만든다.”
                              // 그래서 p는 ITEM 구조체 한 개를 가리키는 포인터 변수가 됩니다.
							  // 포인터 이름은 p로 짧게 썼지만, 가리키는 대상은 received[idx]라는 ITEM 구조체 한 개입니다.
                              // 즉“자료형이 같다(둘 다 ITEM* 타입)”지만 역할이 다릅니다.
    double revenue = p->sold * p->price;
    printf("ID:%d | 상품명:%s | 입고량:%.2f | 판매량:%.2f | 판매가격:%.2f | 매출:%.2f\n",
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
            printf("ID:%d | %s | 입고:%.2f | 판매:%.2f | 단가:%.2f | 매출:%.2f\n",
                arr[i].id, arr[i].name, arr[i].stocked, arr[i].sold, arr[i].price, revenue);
        }
    }
    return total_revenue;
}
static void show_overall_status(const ITEM* arr, int n) {
    printf("\n[전체 현황]\n");
    double total_revenue = 0.0;
	total_revenue = compute_revenue(arr, n);
    double rate = compute_total_sales_rate(arr, n);
    printf("총 판매율: %.2f%%, 총 매출: %.2f\n", rate, total_revenue);
}

int main(void) {
    int quantity;
    int r_count = 0;
    int saled_count = 0;

    ITEM items[MAX_PRODUCTS];
    init_items(items, MAX_PRODUCTS);

    printf("상품 개수를 입력하십시오 (1~%d): ", MAX_PRODUCTS);
    if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > MAX_PRODUCTS) {
        fprintf(stderr, "잘못된 입력입니다. 프로그램을 종료합니다.\n");
        return 1;
    }

    while (1) {
        int menu = print_menu();
        if (menu == -1) {
            fprintf(stderr, "잘못된 입력입니다(1~5 중 입력).\n");
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
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            fprintf(stderr, "잘못된 입력입니다(1~5 중 입력).\n");
            break;
        }
    }
    // return 0; // 도달하지 않음
}
