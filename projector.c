// P4 assignment
// Ethan Liang

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct groups{
	int size;
	double angle;
}groups;

// swaps the groups
void swap(groups* arr,int a,int b){
	double temp=arr[a].angle;
	arr[a].angle=arr[b].angle;
	arr[b].angle=temp;
}

// creates a pivit for quicksort
int partition(groups* arr,int low,int high){
	double pivot=arr[high].angle;
	int i=(low-1);
	for(int j=low;j<=high;j++){
		if(arr[j].angle<pivot){
			i++;
			swap(arr,i,j);
		}
	}
	swap(arr,i+1,high);
	return (i+1);
}

// quicksort
void quicksort(groups* arr,int low,int high){
	if(low<high){
		int pi=partition(arr,low,high);
		quicksort(arr,low,pi-1);
		quicksort(arr,pi+1,high);
	}
}

int main(void){
	// get number of groups and angles
	int N,A;
	scanf("%d %d",&N,&A);

	// allocate memory
	groups* group=malloc((N*2)*sizeof(groups));

	for (int i=0;i<N;i++){
		// get coordinates and size
		int x,y,s;
		scanf("%d %d %d",&x,&y,&s);

		// turn coordinates into angles
		double angle=atan2(y,x)*180/PI;

		// turns negative angles positive
		if(angle<0){
			angle+=360;
		}

		// fill info into struct
		group[i].size=s;
		group[i].angle=angle;
		group[i+N].size=s;
		group[i+N].angle=angle+360;
	}

	// quicksort items based on angle size
	quicksort(group,0,N*2);

	// info for two pointer sweep
	int minpeople=group[0].size;
	int people=0;
	int left=0;
	int right=0;
	double maxangle=0;

	// two pointer sweep
	while(right<(N*2)){
		if(group[right].angle-group[left].angle<=A){
			people+=group[right].size;
			right++;
		}
		else{
			people-=group[left].size;
			left++;
		}

		// checks smaller group and gets the maxangle
		if(people<minpeople){
			minpeople=people;
			maxangle=group[right].angle-group[left-1].angle;
		}

		// makes sure angle can not be lower than 90
		if(maxangle<=90){
			maxangle=90;
		}
	}

	// prints people and angle
	printf("%d\n%.4lf\n",minpeople,maxangle);

	// free mem
	free(group);

	return(0);
}