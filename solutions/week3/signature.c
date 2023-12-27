#include <stdio.h>

/*safe choice: bence sol kordinat� en k���k olan� bulup e�itsizlik y�ntemiyle onunla ortak alan� olan t�m elemanlar�n ortak alan�n� bulal�m.
  Mesela (2,5), (1,6), (3,15), (7,16), (15,21), (4,20), (17,22) i�in �nce (1,6) dan ba�lay�p s�rayla giderek (3,5) ortak alan�n� bulup 4 tane
  eleman i�in tek �izgiyle i�i hallederiz. Ya da tam tersi sa� kordinat� en b�y�k olan� bulup ona g�re i�lem yapabilirz. 
*/
void sign(long int n, long int arr[][3]){
	long int max, i, left, right, count = 0, point[100], index;
	
	do{
		max=-1;
		for(i=0;i<n;i++){
			if(arr[i][2] != 1 && arr[i][1] > max){ //bak�lmam��sa ve maxtan b�y�kse
				max = arr[i][1];
				index = i;
			}
		}
		if(max != -1){
			arr[index][2] = 1;
			left = arr[index][0];
			right = arr[index][1];	
			for(i=0;i<n;i++){
				if(arr[i][2] != 1){
					if(right >= arr[i][1] && arr[i][1] >= left){
						right = arr[i][1];
						if(arr[i][0] > left) left = arr[i][0];
						arr[i][2] = 1;
					}
					else if(arr[i][1] >= right && right >= arr[i][0]){
						if(arr[i][0] > left) left = arr[i][0];
						arr[i][2] = 1;
					}
				}
			}
			point[count++] = right;
		}
	} while(max != -1);
	printf("%ld\n", count);
	for(i=count-1;i>=0;i--) printf("%ld ", point[i]);
}

int main(){
	long int n, arr[100][3] = {{0}}, i;
	
	scanf("%ld", &n);
	for(i=0;i<n;i++){
		scanf("%ld %ld", &arr[i][0], &arr[i][1]);
	}
	sign(n, arr);
	return 0;
}
