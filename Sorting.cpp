#include <stdio.h>
int k =0;
int MK=0;
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
    k++;
}

void selectionSort(int a[], int n)
{
    k=0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i+1; j < n; j++)
        {
            if (a[j] < a[i]) {
                swap(&a[j], &a[i]);
                //k++;
            }
        }
    }
    printf("The no of Swaps in this selection sort:%d",k);
}
void bubbleSort(int a[], int n)
{
    int i, j;
    k=0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (a[j] > a[j+1]) {
                swap(&a[j], &a[j + 1]);
                //k++;
            }
        }
    }
    printf("\nThe no of iterations in Bubble sort:%d",k);
}
void insertionSort(int a[], int n)
{
    int i,j,v;
    int K=0;
    for (i=0; i<n; i++){
        v = a[i];
        j= i-1;
        while(j >= 0 && a[j] > v){
            a[j+1]=a[j];
            K++;
            j--;
        }
        a[j+1]= v;
    }
    printf("\nThe no of Swaps in this insertion Sort :%d",K);
}
void heap(int a[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && a[l] > a[largest])
        largest = l;
    if (r < n && a[r] > a[largest])
        largest = r;
    if (largest != i)
    {
        swap(&a[i], &a[largest]);
        heap(a, n, largest);
    }
}
void heapSort(int a[],int n)
{

    int i;
    k=0;
    for (i = n / 2 - 1; i >= 0; i--) {
        heap(a, n, i);
    }
    for (i=n-1; i>=0; i--)
    {
        swap(&a[0], &a[i]);
        heap(a, i, 0);
    }

}
int split (int a[], int low, int high)
{
    int pivot = a[high],k=0;
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i + 1],&a[high]);
    return (i + 1);
}
void quickSort(int a[], int low, int high)
{
    k=0;
    if (low < high)
    {
        int t = split(a, low, high);
        quickSort(a, low, t - 1);
        quickSort(a, t + 1, high);
    }
}
void merge(int a[], int l, int m, int r)
{
    int i, j, k=0;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1+ j];
    i = 0;
    j = 0;
    k=l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        MK++;
    }
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        MK++;
    }
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        MK++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    MK=0;
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}
void printArray(int a[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}
int main()
{
    int a[10],i,n,choice;
    printf("Enter the no of unsorted integers:");
    scanf("%d",&n);
    printf("Enter the unsorted numbers:\n");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

        printf("\nWhat Sort Do you want to do?\n");
        printf("1.Selection Sort\n2.Bubble Sort\n3.insertion Sort\n4.Heap Sort\n5.Quick sort\n6. Merge Sort\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch (choice){
            case 1 :
                selectionSort(a,n);
                break;
            case 2:
                bubbleSort(a,n);
                break;
            case 3:
                insertionSort(a,n);
                break;
            case 4:
                heapSort(a,n);
                printf("\nThe no of Swaps in this heap Sort :%d",k);
                break;
            case 5:
                quickSort(a,0,n-1);
                printf("\nThe no of Swaps in this quick Sort :%d",k);
                break;
            case 6:
                mergeSort(a,0,n-1);
                printf("\nThe no of Swaps in this Merge Sort :%d",MK);
                break;
            default:
                printf("wrong choice\n");
        }

    printf("\nSorted array: \n");
    printArray(a, n);

    return 0;
}
