#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long min(long long x, long long y, long long z){
	long long min = x;
	if(min > y) min = y;
	if(min > z) min = z;
	return min;
}

long long max(long long x, long long y, long long z){
	long long max = x;
	if(max < y) max = y;
	if(max < z) max = z;
	return max;
}

//sorunlu
void reconstruct_alignment(long long dist[][100], long long n, char* str1, long long m, char* str2){
	char alignment1[n+m+1], alignment2[n+m+1];
	long long i = n, j = m, index = 0;
	
	while(i > 0 || j > 0){
		if(i > 0 && dist[i][j] == dist[i-1][j] + 1){
			alignment1[index] = str1[i-1];
			alignment2[index] = '-';
			i--;
		}
		else if(j > 0 && dist[i][j] == dist[i][j-1] + 1){
			alignment1[index] = '-';
			alignment2[index] = str2[j-1];
			j--;
		}
		else{
			alignment1[index] = str1[i-1];
			alignment2[index] = str2[j-1];
			i--;
			j--;
		}
		index++;
	}
	
	alignment1[index] = '\0';
	alignment2[index] = '\0';
	
	strrev(alignment1);
	strrev(alignment2);
	
	printf("%s\n", alignment1);
	printf("%s\n", alignment2);
}

/*
minimum edit distance:
problem: Verilen iki stringin birincisinden ikincisini olu�turmak istiyoruz. Bunu yaparken minimum edit say�s�n� bulmak istiyoruz. Minimum 
operasyon say�s�n� veren ��z�m i�in e�er nicelik olarak ilk stringde olup ikincide olmayan bir harf varsa bunu ilkinden silmek i�in ilk 
stringin harfini alacaz ikincisininkini alm�ycaz (deletion). Veya tam tersi, nitelik olarak ikincide olan ve birincide olmayan bir
harf i�in ikincininkini al�p birincisi i�in bo�luk koyucaz, eksik harfi ifade edecek bu (insertion). Veya replace etmemiz gereken durum
olacak, bunda iki stringden de harf al�caz. (Bu i�lemlerin sonunda minimum operasyon say�s�n� verecek bir optimal alignment olu�acak) 

Proof and algorithm: elimizdeki iki string i�in optimum alignment yap�ld���nda son s�tunda ya iki stringin son harfleri ya ilk stringin son 
harfi ve bo�luk ya da ikinci stringin son harfi ve bo�luk olacak. �ki bo�luk olma �ans� yok. Yani son s�tun �ncesini bir sub problem olarak
d���n�rsen son s�tun �ncesi al�nan ceza art� bu �� durumdan hangisi minimumsa onun cezas� toplam� bize min cezay� verecek. P[i][j]'yi ilk 
stringin ilk i harfi ve ikinci stringin ilk j harfi i�in yap�lan optimal alignment i�in minimum maliyet olarak tan�mlans�n. i ve j deki 
harfler i�in yukarda bahsetti�im gibi olu�abilecek 3 durum var. Bu �� durum sonunda olu�abilecek 3 farkl� maliyeti yazal�m:

1- Birincinin i'sini al�p ikincinin j'sini almazsak P[i][j] = P[i][j-1] + (gap penalty) olur.
2- Birincinin i'sini almay�p ikincinin j'sini al�rsak P[i][j] = P[i-1][j] + (gap penalty) olur. 
3a- �kisini de al�r�z ama mismatch varsa P[i][j] = P[i-1][j-1] + (mismatch penalty) olur. 
3b- �kisini de al�r�z ama mismatch yoksa P[i][j] = P[i-1][j-1] olur. 

E�er match varsa 1, 2 ve 3b'den minimum olan P[i][j]'ye atan�r. match yoksa 1, 2 ve 3a'dan minimumu P[i][j]'ye atan�r. 
��te burada dynamic programming'in g�zelli�i ortaya ��k�yor. P'yi iki boyutlu bir matris olarak olu�turursal ve i� i�e iki for yaparsak i�lem
tamam. ��nk� her hal�karda i�eri girdi�imizde daha �nceki iterasyonlarda hesaplad���m�z de�erlerle kar��la�t�rma yap�caz.

Analysis: O(n*m)
*/

long long edit_dist(long long n, char* str1, long long m, char* str2){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = i; //di�er string bo� oldu�undan her t�rl� di�er stringdeki harf say�s� kadar insertion/deletion olacak.
	for(i=0;i<=m;i++) dist[0][i] = i;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(str1[i-1] == str2[j-1]){
				dist[i][j] = min(dist[i][j-1] + 1, dist[i-1][j] + 1, dist[i-1][j-1]);
			}
			else{
				dist[i][j] = min(dist[i][j-1] + 1, dist[i-1][j] + 1, dist[i-1][j-1] + 1);
			}
		}
	}
	reconstruct_alignment(dist, n, str1, m, str2);
	
	return dist[n][m];
}

//minimum penalty: gap penalty = 1, mismatch penalty = 1, G�rd���n gibi edit distance'�n t�pat�p ayn�s�, Sadece insertion ve deletion i�in bir
//gap penalty ve replace i�in bir mismatch penalty de�i�keni var
long long minimum_penalty(long long n, char* str1, long long m, long long *str2, long long gp, long long mp){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = i * gp;
	for(i=0;i<=m;i++) dist[0][i] = i * gp;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(str1[i-1] == str2[j-1]){
				dist[i][j] = min(dist[i][j-1] + gp, dist[i-1][j] + gp, dist[i-1][j-1]);
			}
			else{
				dist[i][j] = min(dist[i][j-1] + gp, dist[i-1][j] + gp, dist[i-1][j-1] + mp);
			}
		}
	}
	
	return dist[n][m];
}

//longest common subsequence
//edit distance'dan fark�: bunda max uzunlu�u elde etmeye �al��t���m�zdan gap sonucunda ve mismatch'da bi�ey eklemiyoruz, match s�ras�nda +1 
//ekliyoruz ve bunlar aras�nda max'a bak�yoruz. 

long long lcs(long long n, char* str1, long long m, char* str2){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = 0;
	for(i=0;i<=m;i++) dist[0][i] = 0;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(str1[i-1] == str2[j-1]){
				dist[i][j] = max(dist[i][j-1], dist[i-1][j], dist[i-1][j-1] + 1);			
			}
			else{
				dist[i][j] = max(dist[i][j-1], dist[i-1][j], dist[i-1][j-1]);	
			}
		}
	}
	
	return dist[n][m];
}

int main(){
	long long n, m;
	char *str1, *str2;
	
	printf("length of first string: ");
	scanf("%lld", &n);
	str1 = (char*) malloc((n+1)*sizeof(char));
	printf("first string: ");
	scanf("%s", str1);
	
	printf("length of second string: ");
	scanf("%lld", &m);
	str2 = (char*) malloc((m+1)*sizeof(char));
	printf("second string: ");
	scanf("%s", str2);
	
	printf("\nminimum edit distance: %lld", edit_dist(n, str1, m, str2));
	
	printf("\nlongest common subsequence: %lld", lcs(n, str1, m, str2));
	
	return 0;
}
