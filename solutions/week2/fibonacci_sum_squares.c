#include <stdio.h>
#include <stdlib.h>

long int fibonacci_sum(long long int n){
	long int a=0, b=1, c, sum=1, i, pisano = 60;
	n = n % pisano;
	if(n <= 1) return n;
	for(i=0;i<n-1;i++){
		c = (a+b) % 10;
		a = b;
		b = c;
		sum += (c*c) % 10;
	}
	return sum % 10;
}

int main(){
	long int n;
	scanf("%ld", &n);
	printf("%ld", fibonacci_sum(n));
	return 0;
}
