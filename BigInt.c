#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"

char* initializeBigInt() {
    char* arr = (char*)malloc(1001*sizeof(char));
    for(int i = 0; i < 1000; i++) {
        arr[i] = 0;
    }
    arr[1000] = '\0';
    return arr;
}

static char* removeLeadingZeros(char* res) {
	int nonz = 0, newlen = 0, i = 0;
	for(nonz = 0; nonz < strlen(res); nonz++) {
		if(res[nonz] != 48) { 
			break;	
		}
	}
	if(nonz == 0) { 
		return res;
	}
	newlen = strlen(res) - nonz;
	for(i = 0; i < newlen; i++) { 
		res[i] = res[i+nonz];
	}
	res[i] = '\0';
	if(res[0] == '\0') {
		free(res);
		res = (char*)calloc(2,sizeof(char));
		res[0] = 48;
		res[1] = '\0';	
	}
	return res;
}

static int isZero(const char* BigInt){
	int i = 0, len = strlen(BigInt);
	while(i < len) {
		if(BigInt[i] == 48) { 
			++i;
		}
		else { 
			break;
		}		
	}
	if(BigInt[i] == '\0') { 
		return 1;
	} 
	return 0;
}

static char* BigInt_Subtraction(const char* BigInt1, const char* BigInt2) {
	int len1 = strlen(BigInt1) - 1;
	int len2 = strlen(BigInt2) - 1;
	int top = 0, bottom = 0, k = len1, i;
	int taken = 0;
	char* res = (char*)calloc(k+2, sizeof(char));
	for(i = 0; i <= k; i++) { 
		res[i] = 48;
    }
	res[i] = '\0';
	while(len2 >= 0) {
		top = BigInt1[len1] - 48;
		bottom = BigInt2[len2] - 48;
		if(taken > 0) {
			if(taken == 1) {
				top -= 1;
			}
            else {	
				top = 9 + BigInt1[len1] - 48 ;
			}
			--taken;		
		}
		if(top < bottom) {
			do {
				++taken;
			}
            while(BigInt1[len1 - taken] == 48 && (len1 - taken) > 0);
			top +=10;		
		}
		res[k] = 48+ top - bottom;
		--len1;
        --len2;
        --k;
	}
	while(len1 >= 0) {
		if(taken >  0) {
			res[k] = BigInt1[len1] - 1; 
			if(BigInt1[len1] == 48) { 
				res[k] = 57;
            }
			--taken;
		}
        else {
			res[k] = BigInt1[len1];		
		}
		--len1;
        --k;		
	}
	return res;
}

char* BigInt_Sub(const char* BigInt1, const char* BigInt2) {
	int bigger = compareBigInt(BigInt1, BigInt2);
	if(bigger == -1) {
		char* res = BigInt_Sub(BigInt2, BigInt1);
		return removeLeadingZeros(res);
	}
	char* res = BigInt_Subtraction(BigInt1, BigInt2);
	return removeLeadingZeros(res);
}

int compareBigInt(const char* BigInt1, const char* BigInt2) {
    int len1 = strlen(BigInt1) - 1;
    int len2 = strlen(BigInt2) - 1;
    if(len1 > len2) {
        return 1;
    }
    if(len1 < len2) {
        return -1;
    }
    if(len1 == len2) {
        for(int i = 0; i != '\0'; i++) {
            int diff = BigInt1[i] - BigInt2[i];
            if(diff > 0) {
                return 1;
            }
            else if(diff < 0) {
                return -1;
            }
            else if(diff == 0) {
                return 0;
            }
        }
    }
}

static void BigInt_Addition(const char* BigInt1, const char* BigInt2, char* res) {
    int len1 = strlen(BigInt1) - 1;
    int len2 = strlen(BigInt2) - 1;
    int sum = 0, carry = 0, k = len1 + 1;
    for(int i = 0; i <= k; i++) {
        res[i] = '0';
    }
    while(len2 >= 0) {
        sum = BigInt1[len1] + BigInt2[len2] + carry - 96;
        res[k] = 48 + sum % 10;
        carry = sum / 10;
        --len1;
        --len2;
        --k;
    }
    while(len1 >= 0) {
        sum = BigInt1[len1] + carry - 48;
        res[k] = 48 + sum % 10;
        carry = sum / 10;
        --len1;
        --k;
    }
    if(carry) {
        res[k] = 48 + carry;
    }
}

char* BigInt_Add(const char* BigInt1, const char* BigInt2) {
    int bigger = compareBigInt(BigInt1, BigInt2);
    if(bigger == -1) {
        char* res = (char*)calloc(strlen(BigInt2) + 2, sizeof(char));
        BigInt_Addition(BigInt2, BigInt1, res);
        return removeLeadingZeros(res);
    }
    else { 
        char* res = (char*)calloc(strlen(BigInt1) + 2, sizeof(char));
        BigInt_Addition(BigInt1, BigInt2, res);
        return removeLeadingZeros(res);
    }
}

static void BigInt_Multiplication(const char* BigInt1, const char* BigInt2, char* res) {
	int len1 = strlen(BigInt1);
	int len2 = strlen(BigInt2);
	int sum = 0, carry = 0;
	int l3 = len1 + len2;
	int ptr1 = 1;
	int ptr2;
	for(int i = 0; i < l3; i++) {
		res[i] = '0';		
	}
	for(int i = len2 - 1; i >= 0; i--) {
		sum = 0;
		carry = 0;
		ptr2 = l3 - ptr1;
		for(int j = len1 - 1; j >= 0; j--) {
			sum = (BigInt1[j] - '0') * (BigInt2[i]-'0') + (res[ptr2] - '0') + carry;
			res[ptr2] = 48 + sum % 10;
			carry = sum/10;
			--ptr2;		
		}
		if(carry) {
			res[ptr2] += carry;		
		}
		++ptr1;		
	}
}

char* BigInt_Multiply(const char* BigInt1, const char* BigInt2) {			
	if(!isZero(BigInt1) && !isZero(BigInt2)){
		int bigger = compareBigInt(BigInt1, BigInt2);
		char* res = (char*)calloc(strlen(BigInt1) + strlen(BigInt2) + 1, sizeof(char));
		if(bigger >= 0) {
			BigInt_Multiplication(BigInt1, BigInt2, res);
		}
        else {
			BigInt_Multiplication(BigInt2, BigInt1, res);
		}
		return removeLeadingZeros(res);
	}
	char* res = (char*)malloc(2*sizeof(char));
	strcpy(res, "0");
	return res;
}

char* BigInt_fibonacci(unsigned int n) {
	unsigned int i;	
	char *res1 = (char*)malloc(2 * sizeof(char));
	strcpy(res1, "0");
	if(n == 0) { 
		return res1;
    }
	char *res2 = (char*)malloc(2 * sizeof(char));
	strcpy(res2, "1");
	char* temp = NULL;
	for(i = 2; i <= n; i++) {
		temp = BigInt_Add(res1, res2);
		free(res1);
		res1 = res2;
		res2 = temp;
	}
	free(res1);
	return res2;
}

char* BigInt_factorial(unsigned int n) {
	char* res = (char*)calloc(2, sizeof(char));
	strcpy(res, "1");	
	if(n == 0 || n== 1) {
		return res;
	}
	char* num = (char*)calloc(2,sizeof(char));
	char* temp = NULL;
	strcpy(num, "1");
    for(int i = 2; i <= n; i++) { 
		temp = BigInt_Add(num, "1");
		free(num);
		num = temp;
		temp = BigInt_Multiply(num, res);
		free(res);
		res = temp;	
	}
	free(num);
	return removeLeadingZeros(res);
}

char* BigInt_Pow(const char* BigInt1, unsigned int n) {
	if(isZero(BigInt1)) {
		char* res = (char*)malloc(sizeof(char)*2);
		strcpy(res, "0");
		return res;	
	}
	char* res = (char*)malloc(sizeof(char)*2);
	strcpy(res,"1");
	char* x = (char*)malloc(sizeof(char)*(strlen(BigInt1)+1));
	strcpy(x,BigInt1);
	char* temp;
	while(n > 0) {
		if(n & 1) {
			temp = BigInt_Multiply(res, x);
			free(res);
			res = temp;		
		}	
		n = n >> 1;
		temp = BigInt_Multiply(x,x);
		free(x);
		x = temp;
	}
	free(x);
	return res;
}

char* BigInt_Mod(const char* BigInt1, const char* BigInt2) {
	int comp = compareBigInt(BigInt1,BigInt2);
	int l1 = strlen(BigInt1);
	int l2 = strlen(BigInt2);
	int i;	
	if(isZero(BigInt1) || comp == 0) {
		char* res = (char*)calloc(2,sizeof(char));
		strcpy(res,"0");
		return res;
	}
	if(comp == -1) {	
		char* res = (char*)calloc(l1+1,sizeof(char));
		strcpy(res,BigInt1);
		return res;
	}
	int diff = l1-l2;
	if(BigInt1[0] <= BigInt2[0]) { 
		--diff;
	}
	if(diff == 0) {
		char* temp = BigInt_Sub(BigInt1,BigInt2);
		char* t2 = temp;
		char* res = BigInt_Mod(temp, BigInt2);
		free(t2);
		return res;
	}
	char* ni1 = (char*)malloc(sizeof(char)*(l1 + 1));
	strcpy(ni1, BigInt1);
	char* ni2 = (char*)malloc(sizeof(char)*(l2 + diff + 2));
	for(i = 0; i < l2; i++) { 
		ni2[i] = BigInt2[i];
	}
	for(i = 0; i < diff; i++) { 
		ni2[l2+i] = 48;
	}
	ni2[l2+i] = '\0';
	while(compareBigInt(ni1,ni2) > 0) {
		char* temp = BigInt_Sub(ni1,ni2);
		char* t2 = ni1;
		ni1 = temp;
		free(t2);
	}
	free(ni2);
	if(compareBigInt(ni1,BigInt2) <= 0) { 
		return ni1;
	}
	char* temp = ni1;
	char* res = BigInt_Mod(ni1, BigInt2);
	free(temp);
	return res;
}

char* BigInt_GCD(const char* BigInt1, const char* BigInt2) {
	if(strcmp(BigInt1,"0") == 0 && strcmp(BigInt2,"0") == 0) {
		char* res = (char*)calloc(2,sizeof(char));
		res[0] = '0';
		res[1] = '\0';	
		return res;
	}
	if(strcmp(BigInt1,"0") == 0) {
		char* res = (char*)calloc(strlen(BigInt2) + 1, sizeof(char));
		int i = 0;		
		for(i = 0; i < strlen(BigInt2); i++) { 
			res[i] = BigInt2[i];
		}
		res[i] = '\0';	
		return res;
	}
	if(strcmp(BigInt2,"0") == 0) {
		char* res = (char*)calloc(strlen(BigInt1) + 1,sizeof(char));
		int i = 0;		
		for(i = 0; i < strlen(BigInt1); i++) { 
			res[i] = BigInt1[i];
		}
		res[i] = '\0';	
		return res;	
	}
	char* temp = BigInt_Mod(BigInt1, BigInt2);
	char* res =  BigInt_GCD(BigInt2, temp);
	free(temp);
	return res;	
}
