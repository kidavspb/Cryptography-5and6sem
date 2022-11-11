#include <iostream>
#include <math.h>
//#include <tgmath.h>
#include "tests.hpp"
#define SIZE 400

//#include "sts-2.1.2/include/stat_fncs.h"
//#include "sts-2.1.2/include/externs.h"

int LFSR_3(unsigned int* S) {  //x^3 + x + 1
    *S = ((((*S >> 1) ^ *S ) & 0x1 ) << 2) | (*S >> 1);
    return *S & 0x1;
}
int LFSR_5(unsigned int* S) {  //x^5 + x^2 + 1
    *S = ((((*S >> 2) ^ *S ) & 0x1 ) << 4) | (*S >> 1);
    return *S & 0x1;
}
int LFSR_7(unsigned int* S) {  //x^7 + x + 1
    *S = ((((*S >> 1) ^ *S ) & 0x1 ) << 6) | (*S >> 1);
    return *S & 0x1;
}

void period_counter(int a[]) {
    bool b = true;
    int T = 1;
    for (T = 1; T < SIZE-1; T++) {
        if (a[T]!=a[0]) {
            continue;
        }
        b = true;
        for (int i=0; i < SIZE-T; i++) {
            if (a[T+i]!=a[i]) {
                b = false;
                break;
            }
        }
        if (b == true) {
            break;
        }
    }
    if (b == true) {
        std::cout << "\nPeriod is " << T << "\n";
    } else {
        std::cout << "\nNo period. :-(\n";
    }
}

void frequency_test(int a[]) {
    float sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += 2*a[i]-1;
//        sum += a[i];
    }
    sum /= sqrt(2*SIZE);
//    sum /= sqrt(2);
//    float fx = (2/sqrt(SIZE))*(sum-SIZE/2);
    float p_value = erfc(sum);
    
//    if (-3 < fx && fx < 3) {
    if (p_value > 0.001) {
        printf("✅ Частотный тест пройден");
    } else {
        printf("❌ Частотный тест не пройден");
    }
//    printf(" (%.1f)\n", fx);
}
void series_test(int a[]) {
    int count_0 = 0;
    int count_1 = 0;
    int count_00 = 0;
    int count_01 = 0;
    int count_10 = 0;
    int count_11 = 0;
    int count_000 = 0;
    int count_001 = 0;
    int count_010 = 0;
    int count_011 = 0;
    int count_100 = 0;
    int count_101 = 0;
    int count_110 = 0;
    int count_111 = 0;
    for (int i = 0; i < SIZE-1; i++) {
        if (a[i] == 0) {
            count_0++;
            if (a[i+1] == 0) {
                count_00++;
                if (a[i+2] == 0) {
                    count_000++;
                } else if (a[i+2] == 1) {
                    count_001++;
                }
            } else if (a[i+1] == 1) {
                count_01++;
                if (a[i+2] == 0) {
                    count_010++;
                } else if (a[i+2] == 1) {
                    count_011++;
                }
            }
        } else if (a[i] == 1) {
            count_1++;
            if (a[i+1] == 0) {
                count_10++;
                if (a[i+2] == 0) {
                    count_100++;
                } else if (a[i+2] == 1) {
                    count_101++;
                }
            } else if (a[i+1] == 1) {
                count_11++;
                if (a[i+2] == 0) {
                    count_110++;
                } else if (a[i+2] == 1) {
                    count_111++;
                }
            }
        }
    }
    printf("\n0 = %.1f%%\n1 = %.1f%%\n", (float)count_0/SIZE*100, (float)count_1/SIZE*100);
    printf("\n00 = %.1f%%\n01 = %.1f%%\n10 = %.1f%%\n11 = %.1f%%\n", (float)count_00/SIZE*100, (float)count_01/SIZE*100, (float)count_10/SIZE*100, (float)count_11/SIZE*100);
    printf("\n000 = %.1f%%\n001 = %.1f%%\n010 = %.1f%%\n011 = %.1f%%\n100 = %.1f%%\n101 = %.1f%%\n110 = %.1f%%\n111 = %.1f%%\n", (float)count_000/SIZE*100, (float)count_001/SIZE*100, (float)count_010/SIZE*100, (float)count_011/SIZE*100, (float)count_100/SIZE*100, (float)count_101/SIZE*100, (float)count_110/SIZE*100, (float)count_111/SIZE*100);
}

void stat_properties(int a[]) {
    Frequency(SIZE, a);
    LongestRunOfOnes(SIZE, a);
    Runs(SIZE, a);
    Serial(11, SIZE, a);
//    Universal(SIZE, a);
    LinearComplexity(11, SIZE, a);
//    frequency_test(a);
    series_test(a);
}

int main(int argc, const char * argv[]) {
    unsigned int state_1 = 0x05;
    unsigned int state_2 = 0x15;
    unsigned int state_3 = 0x42;
    int a[SIZE];
//    for (int i = 0; i < SIZE; i++) {
//        int bit1 = LFSR_3(&state_1);
//        int bit2 = LFSR_5(&state_2);
//        int bit3 = LFSR_7(&state_3);
////        a[i] = (bit1&bit2)^(bit2&bit3)^bit3;
//        a[i] = (bit1&bit2)^(bit2&bit3)^bit3;
//        std::cout << a[i];
//    }
//    for (int i = 0; i < SIZE; i++) {
//        if (LFSR_7(&state_3) == 1) {
//            a[i] = LFSR_3(&state_1);
//        } else {
//            a[i] = LFSR_5(&state_2);
//        }
//        std::cout << a[i];
//    }
//    for (int i = 0; i < SIZE; i++) {
//        a[i] = LFSR_7(&state_1);
//        std::cout << a[i];
//    }
    int was0 = 0;
    int was1 = 0;
    for (int i = 0; i < SIZE; i++) {
        if (LFSR_7(&state_3) == 0) {
//            LFSR_5(&state_2);
            was0 = LFSR_3(&state_1);
//            a[i] = was0;
        } else {
//            LFSR_3(&state_1);
            was1 = LFSR_5(&state_2);
//            a[i] = was1^was0;
        }
        a[i] = was0^was1;
        std::cout << a[i];
    }
//    int f1 = LFSR_3(&state_1);
//    int s2 = LFSR_5(&state_2);
//    int t3 = LFSR_7(&state_3);
//    for (int i = 0; i < SIZE; i++) {
//        if (f1+s2+t3 >= 2) {
//            if (f1 == 1) {
//                f1 = LFSR_3(&state_1);
//            }
//            if (s2 == 1) {
//                s2 = LFSR_5(&state_2);
//            }
//            if (t3 == 1) {
//                t3 = LFSR_7(&state_3);
//            }
//            a[i] = 1;
//        } else {
//            if (f1 == 0) {
//                f1 = LFSR_3(&state_1);
//            }
//            if (s2 == 0) {
//                s2 = LFSR_5(&state_2);
//            }
//            if (t3 == 0) {
//                t3 = LFSR_7(&state_3);
//            }
//            a[i] = 0;
//        }
//        std::cout << a[i];
//    }
//    for (int i = 0; i < SIZE; i++) {
//        a[i] = LFSR_7(&state_1);
//        std::cout << a[i];
//    }
    period_counter(a);
    stat_properties(a);
}

