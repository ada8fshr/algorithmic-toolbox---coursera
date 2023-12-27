#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
�ki boyutta en yak�n iki noktay� bulma, O(nlogn): K�saca closest_points_1.1 den fark�n� anlat�cam. 1.1'de strip, yani combine k�sm�nda 
elimizdeki x kordinat�na g�re s�ral� noktalardan x'g�re medyan ile fark�n�n mutlak de�eri d den k���k olanlar� se�ip bunlar� y kordinat�na
g�re s�ral�yoduk. Bundaki sebep x'e g�re medyanla aras�nda d'den fazla mesafe varsa �l�meye gerek olmad��� ve e�er d'den az mesafe varsa da
y'ye g�re s�raland�klar� takdirde her bir nokta i�in en fazla 6 aday nokta bulunma durumunu verimli �ekilde kullanmakt�.  

�imdi 1.2'deki as�l olay y kordinat�na g�re s�ralama olay�n� yaln�zca main'de yapman�n yeterli olmas� fikri. Bunu yapmak i�inse bize verilen 
noktalardan bir �ift daha saklamak ve bu ayriyeten saklad���m�z �ifti mainde y kordinat�na g�re s�ralay�p close fonksiyonuna ayr�ca g�ndermek
gerekli. Divide k�sm�nda 1.1 de olmayan bir subroutine var ve as�l can al�c� noktay� bu olu�turuyor. Burada y'ye g�re s�ral� x2 ve y2'yi left
ve right �eklinde b�l�yoruz. Bunu yapmadaki ama� recursive �a�r�lara x1 ve y1'i left ve right diye b�lerken ayn� b�lme i�lemini x2 ve y2 i�in
de yapmak istememiz. 

Bunu yapmad��m�z takdirde ilk iki recursive �a�r�da s�k�nt� olmaz ��nk� combine d���ndaki i�lemleri x2, y2'den ba��ms�z yap�yoruz ancak combine
k�sm�nda b�y�k bir s�k�nt� ��kar. ��nk� x2, y2'dekiler y'ye g�re s�ral� oldu�undan x1'in mid'inden k���klerin hepsinin x2'de midin sa��nda 
oldu�unu d���n. Yani bize verilen noktalar�n ilk yar�s� i�in yapaca��m�z combine i�leminde strip dizisine noktalar�n ilk yar�s�ndaki hi�bir
eleman yerle�emiycek. Olmas� gereken x2 ve y2'dekilerin x1'in midinden k���k e�it olanlar� bir diziye b�y�kleri bir diziye yerle�tirmek ve 
bu dizileri s�ras�yla left k�s�m i�in yap�lan �a�r�ya ve right k�s�m i�in yap�lan �a�r�ya g�ndermek. Bu ay�rma sonras�nda x2 ler s�ras�z olucak
ama x1'in ayr�lm�� k�s�mlar�yla ayn� elemanlardan olu�acak.  

Ayr�ca 1.1'den farkl� olan iki k���k �nemli k�s�m var. Divide'daki 1.1'de olmayan subroutine'de i'yi leftden de�il 0'dan ba�latma sebebi
x2 ve y2'lerin her �a�r� s�ras�nda iki ayr� diziye ayr�lm�� olmas�. Yani at�yorum x2_left 5 elemanl�, x2_right 4 elemanl� birer dizi oluyolar.
Mesela right k�s�m i�in bir �a�r�day�z left=4, right = 7 olsun x2 de gezerken 0-4 aras�nda gezmeliyiz. Di�er t�rl� dizi d���na ��kar�z.
Ayn� sebeple combine k�sm�nda yani close_strip de de 1.1 den farkl� olarak leftden de�il 0'dan ba�l�yoruz.

Analysis: main de n uzunlu�unda iki diziyi s�ralamak sebebiyle O(nlogn) karma��kl�k var. recursive ba��nt� ise T(n) = 2T(n/2) + O(n). ��nk� her
�a�r�da O(n)'lik bir subroutine'imiz var ve �a�r�n�n combine k�sm�nda da O(n) lik bir i�lem yap�yoruz. Ba��nt�dan karma��kl�k O(nlogn) geliyor.
Yani toplam karma��kl�k O(nlogn)...
 
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

double close_strip(long long x1[], long long y1[], long long x2[], long long y2[], double d, long long left, long long right, long long mid){
	long long n = right-left+1, strip_x[n], strip_y[n], i, j=0;
	double min = d;
	
	for(i=0;i<n;i++){
		if(llabs(x1[mid] - x2[i]) < d){
			strip_x[j] = x2[i];
			strip_y[j] = y2[i];
			j++;
		}
	}
	
	n = j;
	
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

double close(long long x1[], long long y1[], long long x2[], long long y2[], long long left, long long right){
	double d, d1, d2;
	long long mid, i, j, k, n = right - left + 1;
	long long x2_left[n], y2_left[n], x2_right[n], y2_right[n]; // y ye g�re s�ral� listedeki elemanlar� x1[mid] 'den b�y�k k���k olmas�na g�re ay�rcaz 
	
	//base case
	if(right - left == 1) return dist(x1[left], y1[left], x1[left+1], y1[left+1]);
	if(right - left == 2){
		d = dist(x1[left], y1[left], x1[left+1], y1[left+1]);
		d1 = dist(x1[left], y1[left], x1[left+2], y1[left+2]);
		if(d > d1) d = d1;
		d1 = dist(x1[left+1], y1[left+1], x1[left+2], y1[left+2]);
		if(d > d1) d = d1;
		return d;
	}
	
	//divide
	mid = (right - left) / 2 + left;
	
	//subroutine - x2 ve y2'yi ay�rmak i�in
	j=0, k=0;
	for(i=0;i<n;i++){
		if(x2[i] <= x1[mid] && j < n/2){
			x2_left[j] = x2[i];
			y2_left[j] = y2[i];
			j++;
		}
		else{
			x2_right[k] = x2[i];
			y2_right[k] = y2[i];
			k++;
		}
	}
	
	d1 = close(x1, y1, x2_left, y2_left, left, mid);
	d2 = close(x1, y1, x2_right, y2_right, mid+1, right);
	
	if(d1 > d2) d = d2;
	else d = d1;
	
	//combine
	d1 = close_strip(x1, y1, x2, y2, d, left, right, mid);
	if(d > d1) d = d1;
	
	return d;
}

int main(){
	long long *x1, *y1, *x2, *y2, n, i;

	scanf("%lld", &n);
	
	x1 = (long long*) malloc(n*sizeof(long long));
	y1 = (long long*) malloc(n*sizeof(long long));
	x2 = (long long*) malloc(n*sizeof(long long));
	y2 = (long long*) malloc(n*sizeof(long long));
	
	for(i=0;i<n;i++){
		scanf("%lld %lld", &x1[i], &y1[i]);
		x2[i] = x1[i];
		y2[i] = y1[i];
	}
	
	merge_sort(0, n-1, x1, y1); //x lere g�re s�ral�
	merge_sort(0, n-1, y2, x2); //y lere g�re s�ral�
	
	printf("%.4lf", close(x1, y1, x2, y2, 0, n-1));
	
	return 0;
}
