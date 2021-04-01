#pragma once

#include <iterator>
#include <algorithm>

namespace MJBSampleCode
{

 // Uncomment for non bidirectional version
 //#define BIDIR_ITER

// Notes:
// If I understood templates better, it might be possible to use template specialization to have
// both the bidirectional and non bidirectional version properly selected.  Iterator traits?  Not sure.

// I am mostly confident the bidirectional version works.  The other version would need more
// testing and thought.

#ifdef BIDIR_ITER
// Invariant - at least two elements
// Doesn't require random iterators
   template <typename IterType, typename Compare>
   IterType QuickSortPartition(IterType first, IterType last, Compare compare)
   {
      size_t count = last - first;

      // Lacks elegance perhaps, but simplies task of mentally verifying
      // that the code works for two elements
      // Code below may not work correctly unless there's at least three elements
      if (count == 2)
      {
         auto second = last - 1;
         if (!compare(*first, *second))
         {
            std::swap(*first, *second);
         }
         return first;
      }

      // Calculate pivot position and value
      size_t midPoint = count / 2;
      auto pivot = first + midPoint;
      auto pivotVal = *pivot;

      // Swap pivot to be last element, to simplify code
      // There may be more elegant/efficient solutions, but this seems to
      // simplify the code below.
      auto actualLast = last - 1; // last points to end, not last element
      std::swap(*pivot, *actualLast);
      pivot = actualLast; // Move pivot to point to last element
      last = pivot; // Adjust last to point to last element

      auto i = first;
      auto j = last - 1; // Iterate from the last element excluding the pivot
      while (true)
      {
         while (i < last && compare(*i, pivotVal))
            ++i;
         while (j > first && !compare(*j, pivotVal))
            --j;
         if (i >= j)
         {
            std::swap(*i, *pivot);
            return i;
         }
         std::swap(*i++, *j--);
      }
   }
#endif

#ifndef BIDIR_ITER
   // Invariant - at least two elements
   // Doesn't require random iterators
   // My first attempt at making this work for non bi-direction iterators
   // I doubt it's as efficient as it could be
   // I have concerns over whether it always works, because it's hard to 
   // mentally verify all the corner cases involving the final swap of the pivot
   template<typename IterType, typename Compare>
   IterType QuickSortPartition(IterType first, IterType last, Compare compare)
   {
      size_t count = std::distance(first, last);

      // Lacks elegance perhaps, but simplies task of mentally verifying
      // that the code works for two elements
      // Code below may not work correctly unless there's at least three elements
      if (count == 2)
      {
         auto second = std::prev(last, 1);
         if (!compare(*first, *second))
         {
            std::swap(*first, *second);
         }
         return first;
      }

      // Calculate pivot position and value
      size_t midPoint = count / 2;
      auto pivot = std::next(first, midPoint);
      auto pivotVal = *pivot;

      // Swap pivot to be last element, to simplify code
      // There may be more elegant/efficient solutions, but this seems to
      // simplify the code below.
      auto actualLast = std::prev(last, 1); // last points to end, not last element
      std::swap(*pivot, *actualLast);
      pivot = actualLast; // Move pivot to point to last element
      last = pivot; // Adjust last to point to last element

      auto i = first;
      auto j = std::prev(last, 1); // Iterate from the last element excluding the pivot
      while (true)
      {
         while (compare(*i, pivotVal))
         {
            if (i == j)
               break;
            i = std::next(i, 1);
         }
         while (!compare(*j, pivotVal))
         {
            if (i == j)
               break;
            j = std::prev(j, 1);
         }
         if (i == j)
         {
            if (std::next(i, 1) != pivot)
            {
               // Swap pivot to position i
               std::swap(*i, *pivot);
               // Return pivot position
               return i;
            }
            else
            {
               if (!compare(*i, pivotVal))
               {
                  std::swap(*i, *pivot);
                  return i;
               }
               else
               {
                  return pivot;
               }
            }
         }
         std::swap(*i, *j);
      }
   }
#endif

   template <typename IterType, typename Compare = std::less<typename IterType::value_type>>
   void QuickSort(IterType first, IterType last, Compare compare = std::less<typename IterType::value_type>())
   {
      if (std::distance(first, last) > 1) {
         IterType bound = QuickSortPartition(first, last, compare);
         QuickSort(first, bound, compare);
         QuickSort(std::next(bound, 1), last, compare);
      }
   }


} // namespace

