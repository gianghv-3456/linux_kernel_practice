#include <stdio.h>
#include "hinhVuong.h"
#include "hinhTron.h"
#include "hinhTamGiac.h"

int main(){
	int t;
	double a,b,c,r;
	
	do{
		printf("Menu\n");
		printf("1. Nhap canh va tinh chu vi, dien tich tam giac \n");
		printf("2. Nhap canh va tinh chu vi, dien tich hinh vuong \n");
		printf("3. Nhap canh va tinh chu vi, dien tich hinh tron \n");
		printf("4. Ket thuc \n");
		printf("Chon: ");
		scanf("%d", &t);
		
		switch(t){
			case 1:
                        printf("Nhap canh 1: ");
                        scanf("%lf",&a);
			printf("Nhap canh 2: ");
                        scanf("%lf",&b);
			printf("Nhap canh 3: ");
                        scanf("%lf",&c);
                        printf("Chu vi tam giac: %.2lf\n",chuViTamGiac(a,b,c));
         		printf("Dien tich tam giac: %.2lf\n",dienTichTamGiac(a,b,c));
                        break;
			case 2:
			printf("Nhap canh hinh vuong: ");
			scanf("%lf",&a);
			printf("Chu vi hinh vuong: %.2lf\n",chuViHinhVuong(a));
			printf("Dien tich hinh vuong: %.2lf\n",dienTichHinhVuong(a));	
			break;
			case 3:
                        printf("Nhap ban kinh hinh tron: ");
                        scanf("%lf",&r);
                        printf("Chu vi hinh tron: %.2lf\n",chuViHinhTron(r));
                	printf("Dien tich hinh tron: %.2lf\n",dienTichHinhTron(r));
                        break;
                        case 4:
                        printf("Ket thuc!\n");
                        break;
			default:
			printf("Chon sai. Hay chon lai!");
			break;
		}
	}while (t !=4);

	return 0;
}

