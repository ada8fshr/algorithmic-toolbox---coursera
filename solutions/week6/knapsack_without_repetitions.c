#include <stdio.h>

/*
Problem: her bir itemdan yaln�zca bir defa kullanma iznimiz var. with ile ayn� onun d���nda... 

with'deki algonun burada patlama sebebi: o algoda her bir a��rl�k i�in her bir item'� gezip W - wi optimal ��z�m�ne i'yi ekleyip hangi i i�in 
bu durum max ona bak�yoduk. Ancak bunu yaparken W - wi optimal ��z�m�nde i. item kullan�lm�� m� bilemeyiz. 

Algorithm: with'deki algo bunda patlad���ndan s�f�rdan yine bir dp algo geli�tirme i�in genel yakla��m� kullan�caz, yani son �r�n� inceleyip
�nceki hesaplamalarla olan ba�lant�s�na bak�caz.

Son �r�nde yani ��kt�da bulunan itemlara S k�mesi diyelim. Bu k�me bize verilen W s�n�r�n� a�mayan en de�erli ��z�m. �imdi bu k�mede bize 
verilen itemlardan sonuncusunun yani n. bulunmad���n� varsay: Bu demektir ki S k�mesi, n item�n da g�zden ge�irilip n. haricinde n-1'i 
kullan�larak W a��rl��� i�in optimal ��z�md�r. �imdi varsayal�m ki n. yani son item, S k�mesinde var: n. item�n a��rl���na wn dersek, bu 
demektir ki W - wn a��rl��� i�in optimal ��z�m S - {n}'dir. Bunun contradiction ile ispat�n� with repetitions i�in yapt�m. G�rd���n gibi 
optimal ��z�m i�in yaln�zca iki ihtimal var. Bu ihtimallerden hangisi daha iyiyse optimal ��z�m odur.

�imdi bu ��kar�m�m�z� genelliycez. Bunun i�in bir g�sterime ihtiya� var: V[i][x]; ilk i item g�zden ge�irilip, x a��rl��� i�in optimal value'yu
ifade etsin. Yukardaki ��kar�ma g�re V[i][x]; i dahil de�ilse V[i-1][x], i dahilse V[i-1][x - wi] + vi ikilisinden hangisi daha optimalse, 
b�y�kse ona e�it. i'nin dahil oldu�u durumdaki V[i-1][x - wi], daha �nce hesaplad���m�z x - wi a��rl���ndaki optimal ��z�m. Yani onun �st�ne wi 
a��rl���ndaki vi de�erindeki i'yi koyarak x a��rl��� i�in optimal ��z�m bu mu yoksa daha �nceden i. item �ncesindeki i-1 item kullanarak 
hesaplad���m�z V[i-1][x] mi diye bak�caz.

Asl�nda g�sterimden matrix kullan�cam�z belli, ama nas�l kullan�caz: matrisin sat�r� o anki x a��rl���n�n ��z�m� i�in kullan�lan eleman say�s�n�
tutuyor. Mesela i = 0 ken hi� eleman olmad���ndan t�m x'ler 0. S�tunlar ise her bir x'i tutuyor. with'deki ��z�m�n tersine bunda d��arda item
i�in olan d�ng� varken i�erde a��rl�klar i�in olan d�ng� var. Sebebi �ok basit: ilk i eleman� kullanarak her bir a��rl�k i�in optimal ��z�m� 
buluyoruz. Bu sayede ayn� elemandan iki kez kullan�lmad���ndan emin oluyoruz. Ayr�ca genelledi�imiz ��z�mde ilk i-1 item kullan�lan ��z�me 
bak�yoruz, yani bir �nceki row �nemli. O rowun tamamen hesaplanm�� olmas� laz�m.

Bahsetti�im iki ihtimali �rneklemek gerekirse mesela w = {1,3,4,5} olsun. W = 8 i�in, son item'a geldi�imizde ya 1 + 3 + 4 = 8'lik ��z�m� ya da
(8 - 5) + 5 = 8'lik ��z�m� kullan�caz. (itemlar s�ral� olmak zorunda de�il g�rmesi kolay olsun diye s�ral� verdim.

Analysis: d��ardaki d�ng�deki toplam n kez olan her bir tur i�in i�erde W kadar d�n�yoruz ve i�erde sabit i� yap�yoruz. Yani O(n*W)... 
(De�ilmi�. �stelmi�. stackoverdan bak...)
*/

long long without_r(long long n, long long* v, long long* w, long long W){
	long long i, j; 
	long long arr[n+1][W+1]; //sat�rlar current W i�in kullan�lan item say�s�n�, s�tunlar her bir W'yu tutuyor.
	
	for(i=0;i<=W;i++) arr[0][i] = 0; //hi� item kullanmazsak her bir W i�in value 0 olur.
	for(i=0;i<=n;i++) arr[i][0] = 0; //kapasite 0'sa item say�s�ndan ba��ms�z sonu� 0 olur.
	
	for(i=1;i<=n;i++){
		for(j=1;j<=W;j++){
			arr[i][j] = arr[i-1][j]; //1. ihtimal, i'nin kullan�lmad���
			if(j >= w[i-1] && arr[i-1][j - w[i-1]] + v[i-1] > arr[i][j]){ //2. ihtimal, i'nin kullan�ld���
				arr[i][j] = arr[i-1][j - w[i-1]] + v[i-1];
			}
		}
	}
	
	//reconstruction: ��z�mde kullan�lan itemlar�n indexlerini yazd�rmak i�in (backtracking technic)
	j = W;
	for(i=n;i>=0;i--){
		if(j >= w[i-1] && arr[i][j] == arr[i-1][j - w[i-1]] + v[i-1]){
			printf("%lld ", i-1);
			j -= w[i-1];
		}
	}
	
	return arr[n][W]; // n item'�n da g�zden ge�irildi�i W a��rl���ndaki optimal ��z�m
}

/*
space optimized version of without repetitions: Bunda O(W)'lik bir yer karma��kl��� var. trick �u: yukardaki algoda g�rece�in gibi d��taki 
d�ng�n�n her turunda yaln�zca bir �stteki rowla ilgileniyoruz. Bu sebeple yaln�zca tek row tutmak yeterli, W+1 tane de s�tun olacak. �lk ba�ta 
t�m diziyi 0'a e�itliycez, bu hi� item kullanmad���m�z durumu g�steriyor. Sonras�nda yaln�zca ilk item� kullanarak hi� item kullanmad���m�z 
duruma g�re g�ncelleme yap�yoruz. Sonra bu tur bitip ikinci itema ge�ince birinci item�n kullan�m�na g�re �ekillenen dizide ikinci itema g�re 
g�ncelleme yap�caz... 

Ayr�ca bunu s�rd�rebilmek i�in j'yi Wdan ba�lat�p azaltarak gidicez. Bundaki sebep, bir tura ba�lad���m�zda �nceki turdaki dizide g�ncelleme
yapt���m�zdan e�er 0 dan ba�lay�p art�r�rsak sonraki j'lerde yeni itema g�re g�ncelledi�imiz bir indexi kullanm�� olucaz. Yani ayn� elemandan
birden fazla kez kullanm�� olucaz. Ama j'yi azaltarak gidersek her bakt���m�z index �nceki turdaki index olacak.  
*/

long long without_r1(long long n, long long* v, long long* w, long long W){
	long long i, j; 
	long long arr[W+1]; 
	
	for(i=0;i<=W;i++) arr[i] = 0;
	
	for(i=0;i<n;i++){
		for(j=W;j>=0;j--){
			if(j >= w[i] && arr[j - w[i]] + v[i] > arr[j]){
				arr[j] = arr[j - w[i]] + v[i];
			}
		}
	}
	
	return arr[W];
}

int main(){
	long long n = 4, v[100] = {30,14,16,9}, w[100] = {6,3,4,2}, W = 10, i;
	
//	scanf("%lld", &W);
//	
//	scanf("%lld", &n);
//	
//	for(i=0;i<n;i++) scanf("%lld %lld", &w[i], &v[i]);
	
	printf("\n%lld", without_r1(n, v, w, W));
	
	return 0;
}
