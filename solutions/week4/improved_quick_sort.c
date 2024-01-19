#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long rand_pivot(long long first, long long last){
	return (rand() % (last - first + 1)) + first;
}

//�� b�l�m var: ilk k�s�m k���kler, sonra e�itler sonra b�y�kler. Ve bunlar�n sa��nda hi� bak�lmam�� elemanlar. E�er yeni bak�lan eleman
//e�itse k n�n tuttu�u say�yla swap yeterli ve sadece k y� art�r�r�z. ��nk� ikinci k�s�m bir artt�.
//b�y�kse j yi art�rmak yeterli, 3. k�s�m bir artar sadece. 
//k���kse i�ler de�i�ir. E�er ki j, k dan farkl�ysa �nce k ve i nin tuttuklar� swap edilir, sonra i ve j ninkiler. E�er j, k ile e�itse
//i ve k i�in swap yapmamak laz�m. ��nk� sonras�nda yapaca��m�z i-j swap'� ile ba�lad���m�z yere geri d�nm�� oluruz. Ama j ve k n�n
//durumundan ba��ms�z k art�m� olmal� ��nk� 1. k�s�m bir artt�, ikinci k�s�m bir sa�a kayar. 
//Ayr�ca j, k sorunu yaln�zca dizideki max eleman pivot se�ilirse ve bu max elemandan birden fazla varsa ya�an�yor... 
	
void pivot(long long* arr, long long first, long long last, long long* m1, long long* m2){
	long long i, j, k, temp, pivot_ind;
	
	pivot_ind = rand_pivot(first, last);
	
	temp = arr[pivot_ind];
	arr[pivot_ind] = arr[first];
	arr[first] = temp;
	
	i = first + 1; // i, pivotdan k���klerin oldu�u k�sm�n bir sa��n� yani e�itlerin ilkini tutar.
	k = first + 1; // k ise e�itlerin oldu�u k�sm�n bir sa��n� yani b�y�klerin ilkini tutar.
	 
	for(j=first+1;j<=last;j++){
		if(arr[first] > arr[j]){
			if(j != k){
				temp = arr[k];
				arr[k] = arr[i];
				arr[i] = temp;	
			}
			
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		
			i++;
			k++;
		}
		else if(arr[first] == arr[j]){
			temp = arr[j];
			arr[j] = arr[k];
			arr[k] = temp;
			k++;
		}
	}
	
	temp = arr[first];
	arr[first] = arr[i-1];
	arr[i-1] = temp;
	
	*m1 = i-1;
	*m2 = k;
}

void quick_sort(long long* arr, long long n, long long first, long long last){
	long long m1, m2;
	if(first < last){
		pivot(arr, first, last, &m1, &m2);
		quick_sort(arr, n, first, m1);
		quick_sort(arr, n, m2, last);
	}
}


int main(){
	long long *arr, n, i;
	
	srand(time(0));
	scanf("%lld", &n);
	
	arr = (long long*) malloc(n * sizeof(long long));
	
	for(i=0;i<n;i++){
		scanf("%lld", &arr[i]);
	}
	
	quick_sort(arr, n, 0, n-1);
	for(i=0;i<n;i++) printf("%lld ", arr[i]);
	
	return 0;
}
