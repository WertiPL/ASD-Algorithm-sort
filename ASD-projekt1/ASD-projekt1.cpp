// ASD-projekt1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip> 


void losuj() {

    srand(time(NULL));
    std::fstream plik;
    plik.open("losoweliczby.txt", std::ios::app | std::ios::out);
    if (!plik.good())
    {
        std::cout << "Error";
    }
    else
    {
        for (int i = 0; i < 500000; i++)
        {
            int liczba = std::rand();
            plik << liczba << " ";
            plik.flush();
        }
        plik.close();
    }
}
void sort_babelki( int A[], int n)
{

    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (A[j] > A[j + 1]) {
                int jplus = j + 1;
                std::swap(A[j], A[jplus]);

            }
 }
//lomuto
int partition(int A[], int p, int r)
{
    int x = A[r];
    int i = (p - 1);

    for (int j = p; j <= r - 1; j++)
    {
        if (A[j] <= x)
        {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    int temp = i + 1;
    std::swap(A[temp], A[r]);
    temp = i + 1;
    return temp;
}

void quickSort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}
void heapify(int A[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && A[l] > A[largest])
        largest = l;
    if (r < n && A[r] > A[largest])
        largest = r;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

void heapSort(int A[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}
 

//scalenie posortowanych podtablic
void scal(int A[], int left, int middle, int right)
{
    int temp[500000];
    int i = left, j = middle + 1;

    for (int i = left; i <= right; i++)
        temp[i] = A[i];
    for (int k = left; k <= right; k++)
        if (i <= middle)
            if (j <= right)
                if (temp[j] < temp[i])
                    A[k] = temp[j++];
                else
                    A[k] = temp[i++];
            else
                A[k] = temp[i++];
        else
            A[k] = temp[j++];
}

void sortowanie_przez_scalanie(int A[], int left, int right)
{
    if (right <= left) return;

    int middle = (right + left) / 2;

    sortowanie_przez_scalanie(A, left, middle);
    sortowanie_przez_scalanie(A, middle + 1, right);

    scal(A, left, middle, right);
}
int main()
{
     int dane = 350000;
    int array[500000];

    std::ifstream plik;
    plik.open("losoweliczby.txt", std::ios::in);

    if (!plik.good())
    {
        losuj();
    }
    else
    {
        for (int i = 0; i < dane; i++)
            plik >> array[i];
    }
    std::cout << "Start";
        clock_t start, end;

        
     start = clock();

     quickSort(array, 0, dane-1);

     end = clock();

     if (!plik.good())
     {
         losuj();
     }
     else
     {
         for (int i = 0; i < dane; i++)
             plik >> array[i];
     }
        double time_taken= double(end - start) / double(CLOCKS_PER_SEC);
         std::cout << "Sortowanie Lomuto czas dla liczb losowych: " << std::fixed;
         std::cout << time_taken << std::setprecision(5); ;
         std::cout << " s " << std::endl;
         start = clock();

         sortowanie_przez_scalanie(array, 0, dane-1);

         end = clock();
         time_taken = double(end - start) / double(CLOCKS_PER_SEC);
         std::cout << "Sortowanie przez scalanie czas dla liczb losowych: " << std::fixed;
         std::cout << time_taken << std::setprecision(5); ;
         std::cout << " s " << std::endl;
         if (!plik.good())
         {
             losuj();
         }
         else
         {
             for (int i = 0; i < dane; i++)
                 plik >> array[i];
         }

         start = clock();

         heapSort(array, dane);



         end = clock();
         if (!plik.good())
         {
             losuj();
         }
         else
         {
             for (int i = 0; i < dane; i++)
                 plik >> array[i];
         }
         time_taken = double(end - start) / double(CLOCKS_PER_SEC);
         std::cout << "Sortowanie przez kopcowanie czas dla liczb losowych: " << std::fixed;
         std::cout << time_taken << std::setprecision(5); 
         std::cout << " sec " << std::endl;

     start = clock();

     sort_babelki(array, dane);

     end = clock();



     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Bąbelkowe czas dla liczb losowych : " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " s " << std::endl;
    
        for (int i = dane - 1, j = 0; i > 0 || j < dane; i--, j++)
        {
            array[j] = i;
        }


     start = clock();

     quickSort(array, 0, dane-1);



     end = clock();


      time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Sortowanie Lomuto czas dla odwrotnie posortowanych: " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " s " << std::endl;
     for (int i = dane - 1, j = 0; i > 0 || j < dane; i--, j++)
     {
         array[j] = i;
     }
     start = clock();

     sortowanie_przez_scalanie(array, 0, dane-1);



     end = clock();

    
     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Sortowanie przez scalanie czas dla odwrotnie posortowanych: " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " s " << std::endl;
     for (int i = dane - 1, j = 0; i > 0 || j < dane; i--, j++)
     {
         array[j] = i;
     }
     start = clock();

     heapSort(array, dane);



     end = clock();
     for (int i = dane - 1, j = 0; i > 0 || j < dane; i--, j++)
     {
         array[j] = i;
     }

     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Sortowanie przez kopcowanie czas dla odwrotnie posortowanych: " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " sec " << std::endl;

     start = clock();

     sort_babelki(array, dane);

     end = clock();



     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Bąbelkowe czas dla odwrotnie posortowanych : " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " s " << std::endl; 
//liczb posortowanyc
     for (int i = 0; i < dane; i++)
     {
         array[i] = i;
     }

     start = clock();

     quickSort(array, 0, dane - 1);



     end = clock();

     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Sortowanie Lomuto czas dla liczb posortowanych: " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " s " << std::endl;
     for (int i = 0; i < dane; i++)
     {
         array[i] = i;
     }
     start = clock();

     sortowanie_przez_scalanie(array, 0, dane - 1);

     end = clock();
     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Sortowanie przez scalanie czas dla liczb posortowanych: " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " s " << std::endl;

     for (int i = 0; i < dane; i++)
     {
         array[i] = i;
     }
     start = clock();

     heapSort(array, dane);

     end = clock();
     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Sortowanie przez kopcowanie czas dla liczb posortowanych: " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " sec " << std::endl;
    for (int i = 0; i < dane; i++)
     {
        array[i] = i;
     }
     start = clock();

     sort_babelki(array, dane);

     end = clock();

     time_taken = double(end - start) / double(CLOCKS_PER_SEC);
     std::cout << "Bąbelkowe czas dla liczb posortowanych : " << std::fixed;
     std::cout << time_taken << std::setprecision(5);
     std::cout << " s " << std::endl;
     return 0;
}
