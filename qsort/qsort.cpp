// qsort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Containers
#include <array>
#include <vector>
#include <list>

// Misc headers
#include <iostream>

// timing
#include <chrono>

// ANSI C headers
#include <cstdlib>
#include <ctime>

#include "SampleQuickSort.h"

using namespace MJBSampleCode;
using namespace std::chrono;

using HRC = high_resolution_clock;

template<class T>
void write(T arr)
{
   for (auto e : arr)
   {
      std::cout << e << " ";
   }
   std::cout << std::endl;
}

template<class T>
void test(std::initializer_list<T> l)
{
   std::vector<int> v(l);
   QuickSort( v.begin(), v.end());
   write(v);
}

double elapsedAsDouble( HRC::time_point t1, HRC::time_point t2)
{
   duration<double> temp = duration_cast<std::chrono::duration<double>>(t2 - t1);
   return temp.count();
}

int main()
{
   test({ 1 });
   test({ 1, 2 });
   test({ 2, 1 });

   test({ 2, 2 });

   test({ 1, 2, 3 });
   test({ 1, 3, 2 });
   test({ 2, 1, 3 });
   test({ 2, 3, 1 });
   test({ 2, 3, 1 });
   test({ 3, 1, 2 });
   test({ 3, 2, 1 });

   test({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
   test({ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
   test({ 10, 9, 8, 7, 6, 1, 4, 3, 2, 5 });
   test({ 5, 9, 8, 7, 6, 10, 4, 3, 2, 1 });

   std::srand( static_cast<unsigned int>(std::time(0)));
   for (auto i = 0; i < 20; ++i)
   {
      std::vector<int> v;
      for (int j = 0; j < 10; ++j)
         v.push_back(rand() % 10 + 1);
      QuickSort(v.begin(), v.end());
      write(v);
   }

   // List
//#ifndef BIDIR_ITER
   std::list<int> myList{ 1, 2, 3 };
   QuickSort(myList.begin(), myList.end());
//#endif

   // Timing compared to std::sort, out of curiosity
   {
      std::vector<int> v;
      for (int j = 0; j < 30; ++j)
         v.push_back(rand() % 30 + 1);
      
      std::vector<int> v1(v);
      HRC::time_point t1 = HRC::now();
      QuickSort(v1.begin(), v1.end());
      HRC::time_point t2 = HRC::now();
      std::cout << "Elapsed time: " << elapsedAsDouble(t1, t2) << "\n";
      write(v1);

      std::vector<int> v2(v);
      t1 = HRC::now();
      std::sort(v2.begin(), v2.end());
      t2 = HRC::now();
      std::cout << "Elapsed time: " << elapsedAsDouble(t1, t2) << "\n";
      write(v2);
   }

}

/*
* Original version from someone on the internet.  Uses last element as pivot value
* 
* Ref: http://www.cs.fsu.edu/~lacher/courses/COP4531/lectures/sorts/slide09.html
* 
template <typename RandomIt, typename Compare>
RandomIt QuickSortPartition(RandomIt first, RandomIt last, Compare compare)
{
   auto pivot = std::prev(last, 1);
   auto i = first;
   for (auto j = first; j != pivot; ++j) {
      // bool format
      if (compare(*j, *pivot)) {
         std::swap(*i++, *j);
      }
   }
   std::swap(*i, *pivot);
   return i;
}
*/

/*
* My first rewrite written in a way I understood the partitioning better,
* and using the midpoint as the pivot.
* Algorithm supposedly patterned after Hoare's method, modified for iterators
* I wasn't confident the code always worked, due to uncertainty involving how
* the pivot value itself is being swapped potentially.
* 
template <typename RandomIt, typename Compare>
RandomIt QuickSortPartition(RandomIt first, RandomIt last, Compare compare)
{
   size_t midPoint = std::distance( first, last) / 2;
   auto pivotVal = *std::next( first, midPoint);

   auto i = first;
   auto j = std::prev( last, 1);
   while ( true)
   {
      while ( i < last && *i < pivotVal)
         ++i;
      while ( j >= first && *j > pivotVal)
         --j;;
      if (i >= j)
      {
         return i;
      }
      std::swap( *i, *j--);
      // Incrementing i could cause us to skip over pivot, so we only decrement j
   }
}
*/
