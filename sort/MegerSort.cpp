#include <iostream>

using namespace std;

void merge(int arr[], int low, int high, int mid)
{
    int sizeArr1 = mid - low + 1;
    int sizeArr2 = high - mid;
    int *arr1 = new int[sizeArr1];
    int *arr2 = new int[sizeArr2];

    for (int i = 0; i < sizeArr1; i++)
        *(arr1 + i) = arr[low + i];
    for (int i = 0; i < sizeArr2; i++)
        *(arr2 + i) = arr[mid + i + 1];

    int index1 = 0;
    int index2 = 0;
    int index = low;

    while (index1 < sizeArr1 && index2 < sizeArr2)
    {
        if (arr1[index1] < arr2[index2])
        {
            arr[index++] = arr1[index1];
            index1++;
        }
        else
        {
            arr[index++] = arr2[index2];
            index2++;
        }
    }

    while (index1 < sizeArr1)
    {
        arr[index++] = arr1[index1++];
    }

    while (index2 < sizeArr2)
    {
        arr[index++] = arr2[index2++];
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, high, mid);
    }
}

void show(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[] = {1, 5, 4, 6, 7, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, 0, n - 1);
    show(arr, n);
    return 0;
}