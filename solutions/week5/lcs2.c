#include <stdio.h>

// 5.haftadaki videoda da g�rece�in gibi edit_distance algosunda karakterlerin e�it oldu�u durumu maaliyet saymad�k ama insertin, deletion
// ve replace durumunu maliyet sayd�k. Yani bunlar�n bir fazlas� iin min durumuna bakt�k. Videoda da g�rece�in gibi lgs i�in yaln�zca e�it
// oldu�u durumda bir fazlas�na bak�caz, di�er durumlar i�in kendilerine bak�caz. ��nk� yaln�zca e�it olan substringlere bak�yoruz.

long long max(long long x, long long y, long long z){
	long long max = x;
	if(max < y) max = y;
	if(max < z) max = z;
	return max;
}

long long lcs2(long long n, long long* arr1, long long m, long long* arr2){
	long long i, j, dist[n+1][m+1];
	
	for(i=0;i<=n;i++) dist[i][0] = 0;
	for(i=0;i<=m;i++) dist[0][i] = 0;
	
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(arr1[i-1] == arr2[j-1]){
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
	long long n, m, arr1[100], arr2[100], i;
	
	scanf("%lld", &n);
	
	for(i=0;i<n;i++) scanf("%lld", &arr1[i]);
	
	scanf("%lld", &m);
	
	for(i=0;i<m;i++) scanf("%lld", &arr2[i]);
	
	printf("%lld", lcs2(n, arr1, m, arr2));
	return 0;
}
