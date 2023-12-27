#include <stdio.h>

/*
Herhangi bir problem i�in bir dp algoritma geli�tirmek i�in problemin ��z�lm��, yani optimal hali i�in yorum yapmak laz�m. ��nk� herhangi 
bir dp algosunun her ad�m�nda optimal hali elde etmek i�in �nceden hesaplad���m�z optimal halleri kullan�caz. Mesela bu problemin ��z�m� 
i�in �unu d���nmelisin: 

W �st s�n�r�n� a�mayan bir a��rl��a sahip olabilecek maksimum de�erde, yani optimal bir ��z�m var elimizde. �imdi ben bu ��z�m�n i�inde nicelik
olarak en az bir tane olan bir par�adan bir adet ��karay�m. Bu par�an�n a��rl��� w[i] olsun. D�n�m noktas�na geldik. Kalan a��rl�k, yani
W - w[i], bu a��rl�k i�in optimal ��z�md�r. Olmad���n� d���nelim: W - w[i] a��rl���nda daha b�y�k de�erde bir ��z�m varsa ve bu ��z�me W 
a��rl��� i�in optimal ��z�m varsayd���m�z ��z�mden ��kard���m�z par�ay� koyarsak W a��rl�kta optimal varsayd���m�z ��z�mden daha b�y�k de�erde
bir ��z�m elde ederiz. ��te bu �eli�ki yarat�r. ��nk� ba�taki W a��rl�ktaki ��z�m�n optimal oldu�unu kabul ettik. Anlayaca��n gibi her bir yeni
a��rl���n optimal ��z�m� i�in �nceden hesaplad��m�z a��rl�klar�n optimal ��z�mlerini kullan�caz. Yani ��yle bir genel form�l yazabiliriz: 
value(W) = value(W - w[i]) + v[i]. A��rl��� W'dan b�y�k olmayan her item i�in bu i�lemi yap�p max olan� value(W)'e at�ycaz. 
  
Analysis: W'ya kadar her bir a��rl�k i�in optimal ��z�m� bulucaz. bunun i�in d�� d�ng�de W kadar d�neriz. Her bir value(W) i�in item say�s�, n, 
kadar tur at�p value(W - w[i]) + v[i] 'nin max olan�n� value(W)'ya at�ycaz. Yani O(n*W)... (De�ilmi�. �stelmi�. stackoverdan bak...)
*/

long long with_r(long long n, long long* v, long long* w, long long W){
	long long arr[W+1], i, j, max;
	arr[0] = 0;
	
	for(i=1;i<=W;i++){
		arr[i] = 0;
		for(j=0;j<n;j++){
			if(i >= w[j]){
				max = arr[i - w[j]] + v[j];
				if(max > arr[i]) arr[i] = max;
			}
		}
	}
	for(i=0;i<=W;i++) printf("%lld ", arr[i]);
	return arr[W];
}

int main(){
	long long n = 4, v[100] = {30,14,16,9}, w[100] = {6,3,4,2}, W = 10, i;
	
//	scanf("%lld", &W);
//	
//	scanf("%lld", &n);
//	
//	for(i=0;i<n;i++) scanf("%lld %lld", &w[i], &v[i]);
	
	printf("\n%lld", with_r(n, v, w, W));
	
	return 0;
}
