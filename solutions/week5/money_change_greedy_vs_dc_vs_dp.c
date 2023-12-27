#include <stdio.h>

/*
you are given an array called coins which have the number of different coins in an increasing order. And also you are given the sum that you 
need to make with those coins. The goal is to find the minimum number of coins you can use to achive the sum. Assume that you have infinite
supply of each coin...
*/

/*
greedy approach: sum'� a�mad��� s�rece elimizdeki en b�y�k coin i kullan. A�t�ktan sonra bir k���k coin e ge�. G�rd���n gibi bir se�im yapt�k.
Ama bu yakla��m �yle g�r�nse de her zaman do�ru sonucu vermiyor. Mesela coins = {1,5,6}, sum = 10 olsun. �nce 6 y� deniycez, 6 dan yaln�zca bir
tane var sonra 5'e ge�icez ancak sum �u anda 4 oldu�u i�in 1 e ge�icez ve 1 den 4 tane al�p bitiricez. Toplamda 5 coin kulland�k ancak 2 tane 5
ile halledebilirdik.
*/

int greedy(int coins[], int n, int sum){
	int i = n-1, count = 0;
	
	while(sum > 0 && i >= 0){
		count += sum / coins[i];
		sum = sum % coins[i];
		i--;
	}
	
	return count;
}

//recursive approach: Olabilecek t�m se�enekleri deniyor. Mesela sum = 11, coins = {1,5,6} olsun. hem 6,5'i hem 5,6 y� hesaplar. O y�zden kesin
//do�ru sonu� verir ama gereksiz yere tekrardan ayn� hesaplamalar� yapar. naive approach gibi bi�ey yani. karma��kl�k �stel olur.

int recursive(int coins[], int n, int sum){
	int i, min_num_coins = sum / coins[0] + 1, num_coins;
	
	if(sum == 0) return 0;
	
	for(i=n-1;i>=0;i--){
		if(sum >= coins[i]){
			num_coins = recursive(coins, n, sum - coins[i]);
			if(num_coins + 1 < min_num_coins) min_num_coins = num_coins + 1;
		}
	}
	
	return min_num_coins;
}

/*
dynamic programming approach: Hesaplad���m�z sonu�lar� kaydederek tekradan ayn� hesaplamalar� yapmamam�z� sa�l�yor. �stenen sum kadarl�k bir
dizi olu�turuyoz. Mesela sum 9'sa index'i 9'a kadar 10 elemanl� bir dizi. Her bir index sum'�n o de�eri i�in minimum coin say�s�n� tutuyor. 
Mesela coins = {1,5,6} i�in min_num_coins[10] dizisi {0,1,2,3,4,1,1,2,3,4} elemanlar�ndan olu�acak. ��nk� sum = 0 i�in 0, 1 i�in 1, 2 i�in 2 ...
5 i�in ise �nce min_num_coins[5-1] + 1' e bakacak ��nk� sum = 4'e ��kard���m�z 1'i eklersek sum = 5'i elde ederiz. Buradan num_coins = 5 gelir. 
Sonra min_num_coins[5-5] + 1'e bakar ��nk� sum = 0'a ��kard���m�z 5'i eklersek sum = 5'i elde ederiz. Burdan num_coins = 1 gelir. G�rd���n gibi 
recursive'de min_num_coins[5-1]'i bulmak i�in 4 �a�r� daha yapmam�z gerekmi�ken burada tek ad�mda i�i hallediyoruz.
Karma��kl�k sum*n olur. �nan�lmaz bir iyile�tirme...
*/

int dynamic(int coins[], int n, int sum){
	int i, min_num_coins[sum+1], m, num_coins;
	
	min_num_coins[0] = 0;
	for(m=1;m<=sum;m++){
		min_num_coins[m] = min_num_coins[m-1] + coins[n-1]; //sonsuz bir say� olmas�n� sa�l�yoruz.
		for(i=0;i<n;i++){
			if(m >= coins[i]){
				num_coins = min_num_coins[m-coins[i]] + 1;
				if(num_coins < min_num_coins[m]){
					min_num_coins[m] = num_coins;
				}
			}
		}
	}
	return min_num_coins[sum];
}

int main(){
	int n = 3, coins[10] = {2,4,8};
	
	printf("%d", greedy(coins, n, 15));
	printf("\n%d", recursive(coins, n, 15));
	printf("\n%d", dynamic(coins, n, 997));
	
	return 0;
}
