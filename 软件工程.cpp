#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 生成1到max之间的随机整数
int random_int(int max) {
    return rand() % max + 1;
}

// 生成加法运算式
void generate_addition(int max) {
    int num1 = random_int(max);
    int num2 = random_int(max - num1);
    printf("%d + %d = \n", num1, num2);
}

// 生成减法运算式
void generate_subtraction(int max) {
    int num1 = random_int(max);
    int num2 = random_int(num1);
    printf("%d - %d = \n", num1, num2);
}

// 生成乘法运算式
void generate_multiplication(int max) {
    int num1 = random_int(max);
    int num2 = random_int(max / num1);
    printf("%d * %d = \n", num1, num2);
}

// 生成除法运算式
void generate_division(int max) {
    int num1 = random_int(max);
    int num2 = random_int(max / num1);
    printf("%d / %d = \n", num1 * num2, num1);
}

// 生成随机运算式
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
    srand(time(NULL)); // 设置随机数种子
    int grade, num_questions;
    printf("请输入年级（1到6）：");
    if (scanf_s("%d", &grade) != 1 || grade < 1 || grade > 6) {
        printf("错误：请输入1到6之间的数字！\n");
        return 1;
    }
    printf("请输入题目数量：");
    if (scanf_s("%d", &num_questions) != 1 || num_questions <= 0) {
        printf("错误：请输入大于0的题目数量！\n");
        return 1;
    }

    printf("生成的题目如下：\n");
    generate_expression(grade, num_questions);

    return 0;
}
