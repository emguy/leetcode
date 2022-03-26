/*
 *   253. Meeting Rooms II
 *   
 *   Given an array of meeting time intervals intervals where intervals[i] =
 *   [starti, endi], return the minimum number of conference rooms required.
 *   
 *   Example 1:
 *   Input: intervals = [[0,30],[5,10],[15,20]]
 *   Output: 2
 *
 *   Example 2:
 *   Input: intervals = [[7,10],[2,4]]
 *   Output: 1
 *    
 *   Constraints:
 *   
 *   1 <= intervals.length <= 104
 *   0 <= starti < endi <= 106
 *
 */
class Solution {
public:
  int minMeetingRooms(vector<vector<int>>& intervals) {
    auto comparator {
      [] (vector<int>& a, vector<int>& b) {
          return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
      }
    };
    
    sort(intervals.begin(), intervals.end(), comparator);
    
    auto heap_comparator {
      [] (int a, int b) {
          return a > b;
      }
    };
    
    priority_queue<int, vector<int>, decltype(heap_comparator)> heap(heap_comparator);
    
    int most = 0;
    for (auto v : intervals) {
      while (!heap.empty() && heap.top() <= v[0]) {
          heap.pop();
      }
      heap.push(v[1]);
      most = heap.size() > most ? heap.size() : most;
    }
    
    return most;
  }
};
