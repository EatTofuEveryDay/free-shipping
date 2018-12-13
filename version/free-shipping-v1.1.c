#include<math.h> // For sqrt(), fabs(), and floor()
#include<stdio.h> // For printf() and fgets()
#include<stdlib.h> // For abort()
#define Uint unsigned int

// version 1.1

const char charint[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V','W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r','s', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2','3', '4', '5', '6', '7', '8', '9', ' ', '-'};
const int enumA[] = {4,-1,-3,-1,5,0,-2,1,3,0,-1,0,0,0,2,0,1,-2,1,-3,2,-2,0,1,2,-4,4,-1,-3,-1,5,0,-2,1,3,0,-1,0,0,0,2,0,1,-2,1,-3,2,-2,0,1,2,-4,-5,-4,-3,-2,-1,0,1,2,3,4,5,-5,-5};
const double enumB[] = {15.78467153,-20.33898305,17.30449251,-13.860252,10.09813232,13.93939394,-20.33898305,-25.91133005,22.24503765,13.93939394,24.66843501,11.84687015,-28.89561271,17.08836123,-7.200929152,-20.33898305,0,-29.92206032,-8.043478261,-11.4599686,9.650053022,13.93939394,-0.3533568905,-100,4.910714286,-63.84615385,15.78467153,-20.33898305,17.30449251,-13.860252,10.09813232,13.93939394,-20.33898305,-25.91133005,22.24503765,13.93939394,24.66843501,11.84687015,-28.89561271,17.08836123,-7.200929152,-20.33898305,0,-29.92206032,-8.043478261,-11.4599686,9.650053022,13.93939394,-0.3533568905,-100,4.910714286,-63.84615385,0,0,0,0,0,0,0,0,0,0,0,0};

int main(void) {
	// Define
	char lockName1[100];
	char lockName2[100];
	char meter[10];
	char *name1point = lockName1;
	char *name2point = lockName2;
	Uint name1len = 65535;
	Uint name2len = 65535;
	Uint name1[100];
	Uint name2[100];
	double name1enumA;
	double name2enumA;
	double name1enumB;
	double name2enumB;
	double calc1;
	double calc2;
	double calc3;
	double calc4;
	// Increment vars
	Uint i1;
	Uint i2;
	double d;
	printf("Free Shipping - version 1.1");
	while (1) {
		// Accept input
		printf("\nName 1 (female)?");
		if((char)(fgets(name1point, 100, stdin)[0]) == '\n'){
		  abort();
		}
		printf("Name 2 (male)?");
		if((char)(fgets(name2point, 100, stdin)[0]) == '\n'){
		  abort();
		}
		// Map chars into int,
		// So that we can lookup
		// In array.
		for (i1 = 0; i1 < 100; i1++) {
			if (lockName1[i1] == '\n') {
				name1len = i1;
				break;
			} else {
				for (i2 = 0; i2 < 64; i2++) {
					if (lockName1[i1] == charint[i2]) {
						name1[i1] = i2;
						break;
					}
				}
				if (!name1[i1]) {
					abort();
				}
			}
		}
		for (i1 = 0; i1 < 100; i1++) {
			if (lockName2[i1] == '\n') {
				name2len = i1;
				break;
			} else {
				for (i2 = 0; i2 < 64; i2++) {
					if (lockName2[i1] == charint[i2]) {
						name2[i1] = i2;
					}
				}
				if (!name2[i1]) {
					abort();
				}
			}
		}
		// Calculate enumA
		d = 0;
		for (i1 = 0; i1 < name1len; i1++)
		  d = d + enumA[name1[i1]];
		name1enumA = d / name1len;
		d = 0;
		for (i1 = 0; i1 < name2len; i1++) 
		  d = d + enumA[name2[i1]];
		name2enumA = d / name2len;
		// Calculate enumB
		d = 0;
		for (i1 = 0; i1 < name1len; i1++)
			d = d + enumB[name1[i1]];
		name1enumB = d / name1len;
		d = 0;
		for (i1 = 0; i1 < name2len; i1++)
			d = d + enumB[name2[i1]];
		name2enumB = d / name2len;
		// Calculate all
		calc1 = (
              (
                1 - sqrt(
                  fabs(name1enumA - name2enumA) / 10
                )
              )
            ) * 100;
		if (name1enumB == 0.0 || name2enumB == 0.0) {
			calc2 = 0.0;
		} else {
		  if ((name1enumB > 0 && name2enumB > 0) ||
				(name1enumB < 0 && name2enumB < 0)) {
				  if(fabs(name1enumB - name2enumB) == 0.0){
				    calc2 = -100.0;
				  }else{
				    calc2 = (0 - sqrt(1 / fabs(name1enumB - name2enumB))) * 3;
				  }
			} else if (
				(name1enumB > 0 && name2enumB < 0) ||
				(name1enumB < 0 && name2enumB > 0)) {
				calc2 = sqrt(fabs(name1enumB - name2enumB)) * 3;
			} else {
				abort();
			}
		}
		if(((calc1+calc2) == 0.0) || ((calc1+calc2) < 0.0)){
		  calc3 = 0.0;
		  calc4 = 0.0;
		}else if((calc1+calc2 > 100.0)){
		  calc3 = 100.0;
		  calc4 = 100.0;
		}else{
		  calc3 = floor((calc1 + calc2) / 10) + 1;
		  calc4 = (calc1 + calc2);
		}
		printf("\n\n");
		printf("[\u2764-+-\u2764Matchmaking\u2764-+-\u2764]");
		printf("\nFemale: %s", lockName1);
		printf("Male: %s", lockName2);
		printf("Match: %f%%\n", calc4);
		printf("Meter: [");
		for(i2 = 0; i2 < 10; i2++){
		  if(i2 < calc3){
		    printf("█");
		  }else{
		    printf("*");
		  }
		}
		printf("]");
		if(calc4 > 95.0){
		  printf(" (SOUL MATE)");
		}
		printf("\n[\u2764-+-\u2764Matchmaking\u2764-+-\u2764]");
		printf("\n\n");
	}
	// If forever loop ends for
	// whatever reason, end program
	abort();
}
