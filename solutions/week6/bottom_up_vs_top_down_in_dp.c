#include <stdio.h>
#include <stdlib.h>

//Dp i�in optimal ��z�m ve daha k���k boyutlardaki optimal ��z�mler aras�nda ba�lant� kurduktan sonra iki se�enek kal�yor. Anlad���m kadar�yla
//ikisi aras�ndaki tercih sana kal�yor �ok kesin �izgiler yok gibi hangisini kullanaca��na dair.

//bottom up (tabulation): iterative �ekilde base caseden ba�lay�p istenen duruma kadar devam ettirirsin. 

//top down (memoization): recursive �ekilde istenen durumdan ba�layarak sub problemlere ve base case'e do�ru ilerlersin. Bunu yaparken ayn� input
//i�in ayn� sonucu tekrar tekrar hesaplamamak i�in bunlar� bir array veya dictte tutars�n ve ayn� input istenirse do�rudan cevab� d�nd�r�rs�n.

//karma��kl�k olarak ikisi ayn� ancak memoizationda recursive �a�r� maliyeti var.

//memoizationda de�erleri tutmak i�in pitonda kodluyosan dict en mant�kl�s�. Burda indexe g�re tuttum.

long long bottom_up_fibo(long long n){
	long long arr[n+1], i;
	
	arr[0] = 0, arr[1] = 1;
	
	for(i=2;i<=n;i++){
		arr[i] = arr[i-1] + arr[i-2];
	}
	
	return arr[n];
}

long long top_down_fibo(long long n, long long* memo){
	if(n == 0 || memo[n] != 0) return memo[n];
	
	memo[n] = top_down_fibo(n-1, memo) + top_down_fibo(n-2, memo);
	
	return memo[n];
}

int main(){
	long long n, *memo;
	
	scanf("%lld", &n);
	
	memo = (long long*) calloc((n+1), sizeof(long long));
	
	memo[1] = 1;
	
	printf("%lld", bottom_up_fibo(n));
	
	printf("\n%lld", top_down_fibo(n, memo));
	
	return 0;
}
