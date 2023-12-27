#include <stdio.h>
#include <stdlib.h>

// Ana mant�k �u: money change de oldu�u gibi 1'den n'e kadar t�m say�lar i�in kendinden �nceki ihtimallerin her birine bak�p minimumu
// se�iyoruz. Mesela n = 8 i�in arr = {0,0,1,1,2,3,2,3,4} olur. ��nk� mesela i = 8 i�in �u ger�ekle�ir: 3'e b�l�nmez yani ilk ko�ulu atlar,
// 2'e b�l�n�r ve �u anki arr[8], arr[4] + 1'den b�y�k, yani arr[8] = arr[4] + 1 olacak ��nk� arr[4] �zerine bir i�lem daha yapm�� olduk.
// en son ko�ul da arr[8], arr[7] + 1'den b�y�k de�il yani girmeden atlar.


long long prim(long long n, long long *arr){
	long long i, j;
	for(i=2;i<=n;i++){
		arr[i] = n+1; // sonsuza e�itlemek i�in kulland�k
		if(i % 3 == 0 && arr[i] > arr[i/3] + 1) arr[i] = arr[i/3] + 1;
		if(i % 2 == 0 && arr[i] > arr[i/2] + 1) arr[i] = arr[i/2] + 1;
		if(arr[i] > arr[i-1] + 1) arr[i] = arr[i-1] + 1;
	}
	
	return arr[n];
}

void print_n(long long n, long long* arr){
	long long i = n, j=0, *temp;
	
	temp = (long long*) malloc((n+1) * sizeof(long long));	
		
	while(i != 1){
		if(i % 3 == 0 && arr[i] == arr[i/3] + 1){
			temp[j++] = i;
			i /= 3;
		}
		else if(i % 2 == 0 && arr[i] == arr[i/2] + 1){
			temp[j++] = i;
			i /= 2;
		}
		else{
			temp[j++] = i;
			i--;
		}
	}
	
	temp[j] = 1;
	for(i=1;i<=n;i++) printf("%lld ", i);
//	for(i=j;i>=0;i--) printf("%lld ", temp[i]);
}

int main(){
	long long n, *arr;
	
	scanf("%lld", &n);
	
	arr = (long long*) malloc((n+1) * sizeof(long long));	
	
	arr[1] = 0;
	
	printf("%lld\n", prim(n, arr));
	
	print_n(n, arr);
	
	return 0;
}
