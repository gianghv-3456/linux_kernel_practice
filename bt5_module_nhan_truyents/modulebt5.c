#include <linux/module.h> 
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define ROWS 3
#define COLS 3

#define DRIVER_AUTHOR "GIANG HOANG VAN"
#define DRIVER_DESC "bai tap lap trinh nhan linux"

int matrix[ROWS][COLS] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

static int N = 5; 
static int M = 2;

module_param(N, int, S_IRUGO);
module_param(M, int, S_IRUGO);

MODULE_PARM_DESC(N, "Giá trị N");
MODULE_PARM_DESC(M, "Giá trị M");

int smallThanN(void) {
    int i, j, count = 0;
    for(i = 0; i < ROWS; i++) {
    	for(j = 0; j < COLS; j++) {
    		if(matrix[i][j] < N) {
    			count++;
    		}
    	}
    }
    return count;
}

int divisibleByN(void) {
    int i, j, count = 0;
    for(i = 0; i < ROWS; i++) {
    	for(j = 0; j < COLS; j++) {
    		if(matrix[i][j] % N == 0) {
    			count++;
    		}
    	}
    }
    return count;
}
bool isPrime(int num) {
    if (num <= 1)
        return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

int countPrimes(void) {
    int i, j, count = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (isPrime(matrix[i][j]) && matrix[i][j] >= N)
                count++;
        }
    }
    return count;
}



int factorial(void) {
    int fact = 1;
    for (int i = 1; i <= N; i++) {
        fact *= i;
    }
    return fact;
}

int countPrimesMtoN(void) {
    int i, count = 0;
    for (i = M; i <= N; i++) {
        if(isPrime(i)) {
        	count++;
        }
    }
    return count;
}

static int __init matrix_module_init(void) {
    printk(KERN_INFO "Matrix: ");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printk(KERN_INFO "%d ", matrix[i][j]);
        }
        printk(KERN_INFO "\n");
    }
    printk(KERN_INFO "Số phần tử nhỏ hơn N: %d\n", smallThanN());
    printk(KERN_INFO "Số phần tử chia hết cho N: %d\n", divisibleByN());
    printk(KERN_INFO "Số phần tử là nguyên tố >= N: %d\n", countPrimes());
    printk(KERN_INFO "Giai thừa N: %d\n", factorial());
    printk(KERN_INFO "Số phần tử là nguyên tố trong khoảng [M, N]: %d\n", countPrimesMtoN());
    return 0;
}

static void __exit matrix_module_exit(void) {
    printk(KERN_INFO "Module exit\n");
}

module_init(matrix_module_init);
module_exit(matrix_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);