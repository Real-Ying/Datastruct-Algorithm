#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target ) {
    vector<int> result;
    for(int i = 0; i < nums.size(); i++) {
      for(int j = i + 1; j < nums.size(); j++) {
        if (nums[i] + nums[j] == target) {
	  result.push_back(i);
          result.push_back(j);
	  return result;
	}
      }
    }
    return result;
  }
};

int main() {
vector<int> _nums = {5, 6, 3, 8, 1};
int _target = 9;
Solution solution;
vector<int> _result = solution.twoSum(_nums, _target);
for(int k = 0; k < _result.size(); k++) 
  cout << _result[k] << endl;
return 1;

}
