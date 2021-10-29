#include <iostream>
#include <algorithm>

using namespace std;

void quickSort(int arr[], int low, int high)
{
    if (low >= high)
        return;

    int pivot = high;
    int left = low;
    int right = high - 1;
    while (left < right)
    {
        while (arr[left] <= arr[pivot])
            left++;
        while (arr[right] >= arr[pivot])
            right--;

        if (left < right)
        {
            swap(arr[left], arr[right]);
        }
    }

    if (arr[left] > arr[pivot])
        swap(arr[left], arr[pivot]);

    quickSort(arr, low, left - 1);
    quickSort(arr, left + 1, high);
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
    cout << "N " << n << endl;
    quickSort(arr, 0, n - 1);
    show(arr, n);
    return 0;
}