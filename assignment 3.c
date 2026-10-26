/*
	Assignment 3 - Searching and Sorting methods
	Problem Statement -
	Write a C program to create a student database using an array of structures. 
	Apply searching (Linear and Binary Search) and sorting techniques (Insertion Sort, Selection Sort, Shell sort).

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct air
{
	char day[16];
	int aqi;
	float humid;
};

void accept_data(struct air data[], int n);

void display_data(struct air data[], int n);

int linearSearch(struct air data[], int n, float a);

void bubbleSort(struct air data[], int n);

int binarySearch(struct air data[], int n, int a);

void selectionSort(struct air data[], int n);

void insertionSort(struct air data[], int n);

void shellSort(struct air data[], int n);

void mergeSort(struct air data[], int low, int high);

void merge(struct air data[], int low, int mid, int high);

int main()
{
	struct air data[100];
	
	int num;
	printf("Enter number of elements (less than 100) : ");
	scanf("%d",&num);
	
	int choice;
	int a1;
	float hm;
	int k1, k2;
	int low=0;
	int end=num;
	
	do
	{
	
		if(num == 0)
		{
			printf("Empty DATASET.\n");
			exit(0);
		}
	
		printf("\nEnter 1 to accept data\nEnter 2 to display data\nEnter 3 to search humidity percentage by linear search\nEnter 4 for bubble sorting of data by AQI values\nEnter 5 to search AQI value by binary search\nEnter 6 for selection sorting of data by humidity percentage\nEnter 7 for insertion sorting of data by ASCII values of days\nEnter 8 for shell sorting of data by AQI values\nEnter 9 for merge sorting of data by humidity values\n");
		
		printf("Enter your choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("please enter unique data! \n");
				accept_data(data, num);
				break;
			
			case 2:
				display_data(data, num);
				break;
				
			case 3:
				printf("Enter humidity percentage to be searched : ");
				scanf("%f",&hm);
				
				k1 = linearSearch(data, num, hm);
				
				if(k1 == -1)
				{
					printf("AQI value %f not found in data.\n", hm);
				}
				else
				{
					printf("AQI value %f found at location %d data.\n", hm, k1+1);
				}
			
				break;
			
			case 4:
				printf("Data is sorted in ascending/increasing values of AQI : \n");
				bubbleSort(data, num);
				display_data(data, num);
				break;
				
			case 5:
				printf("Enter AQI value to be searched : ");
				scanf("%d",&a1);
				
				bubbleSort(data, num);
				
				k2 = binarySearch(data, num, a1);
				
				if(k2 == -1)
				{
					printf("AQI value %d not found in data.\n", a1);
				}
				else
				{
					printf("AQI value %d found at location %d data.\n", a1, k2+1);
				}
			
				break;
				
			case 6:
				printf("Data is sorted in ascending/increasing values of humidity percentage : \n");
				selectionSort(data, num);
				display_data(data, num);
				break;
				
			case 7:
				printf("Data is sorted in ascending/increasing ASCII values of days : \n");
				insertionSort(data, num);
				display_data(data, num);
				break;
				
			case 8:
				printf("Data is sorted in ascending/increasing values of AQI : \n");
				shellSort(data, num);
				display_data(data, num);
				break;
				
			case 9:
				printf("Data is sorted in ascending/increasing order of humidity values: \n");
				mergeSort(data,low,end);
				display_data(data,num);
				break;
				
			default:
				printf("\nInvalid choice.\n");
				break;
		}
		
	}while(choice <=9 && choice != 0);
	
	return 0;
	
}

void accept_data(struct air data[], int n)
{
	printf("Enter data : \n");
	for(int i=0; i<n; i++)
	{
		printf("Enter day : ");
		scanf("%s",data[i].day);
		
		printf("Enter AQI : ");
		scanf("%d",&data[i].aqi);
		
		printf("Enter humidity percentage : ");
		scanf("%f",&data[i].humid);
		
		printf("\n");
	}
}

void display_data(struct air data[], int n)
{
	for(int i=0; i<n; i++)
	{
		printf("Day : ");
		printf("%s",data[i].day);
		
		printf("\nAQI : ");
		printf("%d",data[i].aqi);
		
		printf("\nHumidity percentage : ");
		printf("%.3f",data[i].humid);
		
		printf("\n\n");
	}
	
}

int linearSearch(struct air data[], int n, float a)
{
	int i;
	 for(i=0; i<n; i++)
	 {
	 	if(data[i].humid == a)
	 	{
	 		return i;
	 		break;
	 	}
	 }
	 
	 return -1;
	 
}

void bubbleSort(struct air data[], int n)
{
	struct air temp;
	for(int i=0; i<n-1; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(data[j].aqi > data[j+1].aqi)
			{
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}
	}
	
}

int binarySearch(struct air data[], int n, int a)
{
	
	int start = 0;
	int end = n-1;
	int mid = (start+end)/2;
	
	while(start <= end)
	{
		if(data[mid].aqi == a)
		{
			return mid;
			break;
		}
		else if(data[mid].aqi > a)
		{
			start = mid+1;
		}
		else
		{
			end = mid-1;
		}
		
		mid = (start+end)/2;
		
	}
	
	return -1;
	
}
	
void selectionSort(struct air data[], int n)
{
	struct air temp;
	
	for(int i=0; i<n; i++)
	{
		float min = data[i].humid;
		int idmin = i;
		
		for(int j=i+1; j<n; j++)
		{
			if(data[j].humid < min)
			{
				min = data[j].humid;
				idmin = j;
			}
		}
		
		temp = data[i];
		data[i] = data[idmin];
		data[idmin] = temp;
	}
		
}

void insertionSort(struct air data[], int n)
{
	struct air key;
	int i, j;
	for(i=1; i<n; i++)
	{
		key = data[i];
		
		j = i-1;
		
		while(j>=1 && strcmp(data[j].day, key.day) < 0)
		{
			data[j+1] = data[j];
			j--;
		}
		
		data[i] = key;
	}

}


void shellSort(struct air data[], int n)
{
	struct air temp;
	int gap;
	int swapf, i;
	for(gap=n/2; gap>0; gap = gap/2)
	{
		while(swapf == 1)
		{
			swapf = 0;
			i = 0;
			
			while(i < n-gap)
			{
				if(data[i].aqi > data[i+gap].aqi)
				{
					temp = data[i];
					data[i] = data[i+gap];
					data[i+gap] = temp;
					swapf = 1;
				}
				
				i++;
			}
		}
	}
}

void mergeSort(struct air data[], int low, int high)
{
	if(low < high)
	{
		int mid = (low+high)/2;
		
		mergeSort(data, low, mid);
		mergeSort(data, mid+1, high);
		
		merge(data, low, mid, high);
		
	}
	
}

void merge(struct air data[], int low, int mid, int high)
{
	int lhalf = low;
	int rhalf = mid+1;
	int i = low;
	
	struct air buffer[100];
	
	while(lhalf <= mid && rhalf <= high)
	{
		if(data[lhalf].humid < data[rhalf].humid)
		{
			buffer[i] = data[lhalf];
			lhalf++;
			i++;
		}
		else
		{
			buffer[i] = data[rhalf];
			rhalf++;
			i++;
		}
	}
	
	while(lhalf <= mid)
	{
		buffer[i] = data[lhalf];
		lhalf++;
		i++;
	}
	
	while(rhalf <= high)
	{
		buffer[i] = data[rhalf];
		rhalf++;
		i++;
	}
	
	for(int x=low; x<high;x++)
	{
		data[x] = buffer[x];
	}
	
}
