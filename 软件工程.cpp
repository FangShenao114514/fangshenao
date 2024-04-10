#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ����1��max֮����������
int random_int(int max) {
    return rand() % max + 1;
}

// ���ɼӷ�����ʽ
void generate_addition(int max) {
    int num1 = random_int(max);
    int num2 = random_int(max - num1);
    printf("%d + %d = \n", num1, num2);
}

// ���ɼ�������ʽ
void generate_subtraction(int max) {
    int num1 = random_int(max);
    int num2 = random_int(num1);
    printf("%d - %d = \n", num1, num2);
}

// ���ɳ˷�����ʽ
void generate_multiplication(int max) {
    int num1 = random_int(max);
    int num2 = random_int(max / num1);
    printf("%d * %d = \n", num1, num2);
}

// ���ɳ�������ʽ
void generate_division(int max) {
    int num1 = random_int(max);
    int num2 = random_int(max / num1);
    printf("%d / %d = \n", num1 * num2, num1);
}

// �����������ʽ
void generate_expression(int grade, int num_questions) {
    for (int i = 0; i < num_questions; i++) {
        switch (grade) {
        case 1:
            generate_addition(20);
            break;
        case 2:
            if (random_int(2) == 1)
                generate_addition(50);
            else
                generate_subtraction(50);
            break;
        case 3:
            switch (random_int(3)) {
            case 1:
                generate_addition(1000);
                break;
            case 2:
                generate_subtraction(1000);
                break;
            case 3:
                generate_multiplication(1000);
                break;
            }
            break;
        default:
            if (random_int(2) == 1) {
                generate_addition(1000);
            }
            else {
                int operation = random_int(4);
                switch (operation) {
                case 1:
                    generate_subtraction(1000);
                    break;
                case 2:
                    generate_multiplication(1000);
                    break;
                case 3:
                    generate_division(1000);
                    break;
                default:
                    generate_addition(1000);
                    break;
                }
            }
            break;
        }
    }
}

int main() {
    srand(time(NULL)); // �������������
    int grade, num_questions;
    printf("�������꼶��1��6����");
    if (scanf_s("%d", &grade) != 1 || grade < 1 || grade > 6) {
        printf("����������1��6֮������֣�\n");
        return 1;
    }
    printf("��������Ŀ������");
    if (scanf_s("%d", &num_questions) != 1 || num_questions <= 0) {
        printf("�������������0����Ŀ������\n");
        return 1;
    }

    printf("���ɵ���Ŀ���£�\n");
    generate_expression(grade, num_questions);

    return 0;
}
