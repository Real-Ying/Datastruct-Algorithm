#include <iostream>
#include <limits.h>

class Solution {
 public:
  int reverse(int x) {
    int rev=0;  //存放反转后的数 
    int pop=0;  //存放弹出的数
    while (x!=0) {									     
      //不断弹出最右边的数
      pop=x%10;  //得到最右边数
      x/=10;     //弹出

      if (rev>INT_MAX/10 || rev==INT_MAX/10&&pop>7)   //判断上限   
        return 0;
      if (rev<INT_MIN/10 || rev==INT_MIN/10&&pop<-8)  //判断下限
	return 0;

      rev=rev*10+pop;  //压入，乘10个位空出0留给压入的数
    }
    return rev;
  }
};

int main() {
  int _x = -123456;
  Solution solution;
  int result = solution.reverse(_x);
  std::cout << result << std::endl;
  return 1;

  /*因为int占4字节32位，根据二进制编码的规则，
   * INT_MAX = 2^31-1=2147483647,INT_MIN = -2^31=-2147483648
   * 所有超过该限值的数，都会出现溢出，出现warning，但是并不会出现error。
   * 如果想表示的整数超过了该限值，可以使用长整型long long 占8字节64位。*/
}
