#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
�ki boyutta en yak�n iki noktay� bulma, O(n*(logn)^2): Elimizdeki noktalar� x kordinatlar�na g�re s�ral�yoruz. Sonra divide and conquer
mant���yla n nokta varsa ilk n/2 sine yani soluna bir recursive �a�r�da, sa��na ise di�er recursive �a�r�da bakacaz. Base caseler ise n'in
2 ve 3 oldu�u durum i�in ge�erli. Neden bunlar? ��nk� elimizde tek nokta kalmas�n� istemiyoruz. Sadece 2 i�in base case olsayd� n = 3 i�in 
solu iki sa�� 1 diye ay�r�rd�k. Sonu� olarak sa� taraftan ne d�n�cek...

�imdi bu yakla��mda s�k�nt� �urada: Noktalar� iki ayr� k�sma ay�rd�k ve bunlar� ayr� ayr� inceledik. Sol k�s�mda minimum uzakl�k d1 ��km�� 
olsun, sa�da ise d2. Bunlardan minimum olan�na d diyip d�nd�rd�k diyelim. Biri sa�da biri solda bulunan iki nokta aras� mesafe d'den daha
k���k olabilir ama biz bunu hi� �l�memi� olucaz. Bunu �l�ebilmek i�in fonksiyona combine k�sm�n� ekledik.

Combine i�in mant�k �u: Bu �artlarda d'den k���k mesafeye sahip iki nokta varsa bu noktalar ay�rd���m�z noktan�n yani mid'deki noktan�n x'inin
en fazla d solunda veya en fazla d sa��nda olmal�. Bu kapsam�n d���nda ise iki noktan�n x leri fark� d den b�y�k olaca��ndan de�erlendirmeye 
gerek kalmaz. Yani yaln�zca bu kapsamdaki noktalar� al�caz ve bir diziye kaydedicez. 

Sonras�nda bir geometri ger�e�inden faydalan�caz. Varsayal�m ki sa� ve sol k�s�mdan minimum mesafe olarak d yi elde ettik. Bu sebeple combine
k�sm� i�in mid deki noktan�n d solu ve d sa�� i�indeki noktalar� bi diziye kaydettik. Bu noktalar�n y kordinatlar�na da ayn� i�lemi yaparsak,
yani d mesafesine g�re bakarsak g�r�cez ki kenar uzunlu�u d olan ve �st �ste veya yan yana olan iki karede en fazla 6 nokta bulunur. Karelerin
k��elerine noktalar� yerle�tir. 6 nokta eder. 7. nokta nerede olursa olsun di�er noktalarla aras�ndaki mesafe d den k���k olur. Bu da bi 
�eli�ki olu�turur. ��nk� herbir kare bir b�lgeye ait. Recursive �a�r�larda bu noktalar aras�ndaki mesafe �l��l�rd� ve d oldu�undan k���k 
��kard�.

�imdi bu durumda combine a�amas�nda y lere g�re s�ralama yaparsak her bir nokta i�in y kordinat�na g�re en fazla kendisinden yukardaki 6 nokta
ile aras�ndaki mesafe d den k���k ��kma aday� olurdu. Bunun uygulamas�n� close_strip_2 fonksiyonunda g�rebilirsin. Asl�nda close_strip 
fonksiyounda yap�lan�n �nceki ile hi�bir fark� yok sadece daha temiz duruyor. strip_2 de her tur n kar��la�t�rma var gibi d���nebilirsin ama
y ye g�re s�ral� ve d mesafesini a�t��� ilk anda ��kacak ve i art�cak yani en fazla 6 kar��la�t�rma ve hesap olacak. Ki zaten j=i+1 atams� var.
kendisinin hemen �st�ndeki noktadan ba�l�yor. Bo�a d�nme ihtimali yok normal strip ile ayn� fonksiyon.


Analysis: T(n) = 2T(n/2) + O(nlogn) ba��nt�s� var. Her bir �a�r�da y lere g�re s�ralama olaca��ndan nlogn lik i� yap�l�r. Y�kseklik logn olur ve
her bir seviyede yap�lan i� e�ittir. nlogn*logn yani O(n*(logn)^2) olur.
*/

void merge(long long left, long long mid, long long right, long long x[], long long y[]){
	long long n, m, i, j, k;
	n = mid - left + 1;
	m = right - mid;
	int L[n][2], R[m][2];
	
	for(i=0;i<n;i++){
		L[i][0] = x[left + i];
		L[i][1] = y[left + i];
	}
	
	for(i=0;i<m;i++){
		R[i][0] = x[mid + 1 + i];
		R[i][1] = y[mid + 1 + i];
	}
	
	i=0, j=0, k=left;
	while(i < n && j < m && L[n-1][0] > R[j][0]){
		if(L[i][0] > R[j][0]){
			x[k] = R[j][0];
			y[k] = R[j][1];
			j++;
		}
		else{
			x[k] = L[i][0];
			y[k] = L[i][1];
	 		i++;
	 	}
	 	k++;
	}
	
	while(i < n){
		x[k] = L[i][0];
		y[k] = L[i][1];
		i++;
		k++;
	}
	
	while(j < m){
		x[k] = R[j][0];
		y[k] = R[j][1];
		j++;
		k++;
	}
}

void merge_sort(long long left, long long right, long long x[], long long y[]){
	long long mid;
	if(left < right){
		mid = left + (right - left) / 2;
		
		merge_sort(left, mid, x, y);
		merge_sort(mid + 1, right, x, y);
		
		merge(left, mid, right, x, y);
	}
}

double dist(long long x1, long long y1, long long x2, long long y2){
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//O(n^2): y ye g�re s�ralama yapmad�k o sebeple y lerine g�re d den k���k mesafedeki noktalar, en fazla 6 tane olduklar�n� bilsek de, kar���k
//durumdalar yani her bir noktaya bakmal�y�z.

double close_strip_1(long long x[], long long y[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=left;i<=right;i++){
		if(llabs(x[mid] - x[i]) < d){
			strip_x[j] = x[i];
			strip_y[j] = y[i];
			j++;
		}
	}
	
	n = j;
	
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(strip_y[j] - strip_y[i] < min){
				d = dist(strip_x[j], strip_y[j], strip_x[i], strip_y[i]);
				if(min > d) min = d;
			}
		}
	}
	return min;
}

//O(n*logn): y  ye g�re s�ralad�k. Bu sebeple i�erdeki d�ng�de y koordinat� �u anki noktan�nkinden daha b�y�k noktalara bak�yoruz. d mesafede
//en fazla 6 tane olaca��ndan i�erdeki d�ng� her bir turda en fazla 6 kez d�n�yor. 6 dan az say�da ise daha az d�ner ama sonu�ta sabit say�da.
//Bir kere ��kt� m� i artar yani ileriki tura ge�eriz. Zaten ��kt�ysa d mesafesini a�t�k demektir ��nk� s�ralad�k. Yani bu k�s�m O(n) oldu.

double close_strip_2(long long x[], long long y[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=left;i<=right;i++){
		if(llabs(x[mid] - x[i]) < d){
			strip_x[j] = x[i];
			strip_y[j] = y[i];
			j++;
		}
	}
	
	n = j;
	merge_sort(0, n-1, strip_y, strip_x);
	
	for(i=0;i<n-1;i++){
		j=i+1;
		while(j < n && strip_y[j] - strip_y[i] < min){
			d = dist(strip_x[j], strip_y[j], strip_x[i], strip_y[i]);
			if(min > d) min = d;
			j++;
		}
	}
	return min;
}

double close_strip(long long x[], long long y[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=left;i<=right;i++){
		if(llabs(x[mid] - x[i]) < d){
			strip_x[j] = x[i];
			strip_y[j] = y[i];
			j++;
		}
	}
	
	n = j;
	merge_sort(0, n-1, strip_y, strip_x);
	
	for(i=0;i<n;i++){
		for(j=1;j<7;j++){
			if(i+j < n && strip_y[i+j] - strip_y[i] < min){
				d = dist(strip_x[i+j], strip_y[i+j], strip_x[i], strip_y[i]);
				if(min > d) min = d;
			}
		}
	}
	return min;
}

double close(long long x[], long long y[], long long left, long long right){
	double d, d1, d2;
	long long mid;
	
	//base case
	if(right - left == 1) return dist(x[left], y[left], x[left+1], y[left+1]);
	if(right - left == 2){
		d = dist(x[left], y[left], x[left+1], y[left+1]);
		d1 = dist(x[left], y[left], x[left+2], y[left+2]);
		if(d > d1) d = d1;
		d1 = dist(x[left+1], y[left+1], x[left+2], y[left+2]);
		if(d > d1) d = d1;
		return d;
	}
	
	//divide
	mid = (right - left) / 2 + left;
	
	d1 = close(x, y, left, mid);
	d2 = close(x, y, mid+1, right);
	
	if(d1 > d2) d = d2;
	else d = d1;
	
	//combine
	d1 = close_strip(x, y, d, left, right, mid);
	if(d > d1) d = d1;

	return d;
}

int main(){
	long long x[100000], y[100000], n, i;

	scanf("%lld", &n);
	
	for(i=0;i<n;i++) scanf("%lld %lld", &x[i], &y[i]);
	
	merge_sort(0, n-1, x, y);
	
	printf("%.4lf", close(x, y, 0, n-1));
	
	return 0;
}
