#include <linux/module.h> 
#include <linux/fs.h>

#define DRIVER_AUTHOR "GIANG HOANG VAN"
#define DRIVER_DESC "bai tap lap trinh nhan linux"

#define ROWS 3
#define COLS 3

int matrix1[ROWS][COLS] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int matrix2[ROWS][COLS] = {
    {3, 6, 7},
    {8, 3, 4},
    {2, 8, 5}
};

int c[ROWS][COLS]= {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};
int d[ROWS][COLS]= {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

int minMatrix(void) {
    int i, j, min = matrix1[0][0];
    for(i = 0; i < ROWS; i++) {
    	for(j = 0; j < COLS; j++) {
    		if(matrix1[i][j] < min) {
    			min = matrix1[i][j];
    		}
    	}
    }
    return min;
}

int maxMatrix(void) {
    int i, j, max = matrix1[0][0];
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (matrix1[i][j] > max)
                max = matrix1[i][j];
        }
    }
    return max;
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

int countPrimes(int matrix[][COLS]) {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (isPrime(matrix1[i][j]))
                count++;
        }
    }
    return count;
}



void sumMatrix(void) {
    int i, j;
    for(i = 0; i < ROWS; i++) {
    	for(j = 0; j < COLS; j++) {
    		c[i][j] = matrix1[i][j] + matrix2[i][j];
    	}
    }
}

void mulMatrix(void) {
   int i, j, k;
   for(i = 0; i < ROWS; i++) {
   	for(j = 0; j < COLS; j++) {
   	    d[i][j] = 0; 
   	    for(k = 0; k < COLS; k++) {
   		d[i][j] += matrix1[i][k] * matrix2[k][j]; 
   	    }
   	}
   }
}

static int __init matrix_module_init(void) {
    printk(KERN_INFO "Matrix1: ");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printk(KERN_INFO "%d ", matrix1[i][j]);
        }
        printk(KERN_INFO "\n");
    }
    printk(KERN_INFO "Matrix2: ");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printk(KERN_INFO "%d ", matrix2[i][j]);
        }
        printk(KERN_INFO "\n");
    }
    printk(KERN_INFO "Min element of matrix1: %d\n", minMatrix());
    printk(KERN_INFO "Max element of matrix1: %d\n", maxMatrix());
    printk(KERN_INFO "Number of primes in matrix1: %d\n", countPrimes(matrix1));
    sumMatrix();
    printk(KERN_INFO "Sum of matrices: \n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printk(KERN_INFO "%d ", c[i][j]);
        }
        printk(KERN_INFO "\n");
    }
    mulMatrix();
    printk(KERN_INFO "Product of matrices: \n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printk(KERN_INFO "%d ", d[i][j]);
        }
        printk(KERN_INFO "\n");
    }
    return 0;
}

static void __exit matrix_module_exit(void) {
    printk(KERN_INFO "Matrix module exit\n");
}

module_init(matrix_module_init);
module_exit(matrix_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);