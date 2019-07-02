#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int sum;
    vector<int> result;
    for (int i = 0; i < nums.size() - 1; i++) {
      for (int j = 0; j < nums.size() - 1; j++) {
        if (i == j)
          continue;
	else {
	  sum = nums[i] + nums[j];
	  if (sum == target) {
	    result.push_back(i);
	    result.push_back(j);
	    return result;
	  }
	} 
      } 
    }
    return result;						         
  }

};

int main() {
  vector<int> _nums = {2, 7, 11, 5};
  int _target = 9;
  Solution example;
  vector<int> _result = example.twoSum(_nums, _target);
  for(int k = 0; k <_result.size(); k++) {
   std::cout << _result[k] << std::endl;
  }
  return 0;
}

