#include <stdio.h>

void num(long int n){
	long int i = 1, j;
	while(i*(i+3) / 2 < n) i++;
	printf("%ld\n", i); //ka� tane oldu�u
	for(j=1;j<i;j++){
		printf("%ld ", j); //��gensel say� bi�imindekiler
	}
	printf("%ld", n - i*(i-1) / 2); //kalan k�s�m
}

int main(){
	long int n;
	scanf("%ld", &n);
	num(n);
	return 0;
}
