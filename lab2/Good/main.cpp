#include <iostream>
#define SIZE 50000

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


int main(int argc, const char * argv[]) {
    unsigned int state_1 = 0x07;
    unsigned int state_2 = 0x07;
    unsigned int state_3 = 0x07;
    int a[SIZE];
//    for (int i = 0; i < SIZE; i++) {
//        a[i] = LFSR_7(&state_1);
//        std::cout << a[i];
//    }
    for (int i = 0; i < SIZE; i++) {
        if (LFSR_7(&state_3) == 1) {
            a[i] = LFSR_3(&state_1);
        } else {
            a[i] = LFSR_5(&state_2);
        }
        std::cout << a[i];
    }
//    int a[SIZE] = {0, 0};

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
        std::cout << "\nNo period. :-(";
    }
    return 0;
}
