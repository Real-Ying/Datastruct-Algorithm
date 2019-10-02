#include <stdio.h>
#define MaxSize 10
typedef struct {
  int arr[MaxSize];
  int length = MaxSize;
}SqList;

void swap(SqList& L, int i ,int  j) {
  int temp = L.arr[i];
  L.arr[i] = L.arr[j];
  L.arr[j] = temp;
}

int SqList_Del_Single1(SqList& L, int e) {
  int i;
  for (i = 0; i < L.length; ++i) {
    //printf("%d\t",i);
    if (e == L.arr[i]) {
      //printf("！！\n");
      while (i < L.length-1) {   
        L.arr[i] = L.arr[i+1];  	  
        i++;
      }
      L.length--;
      return 1;  						  	
    }
  }
  return 0;
}

int SqList_Del_Single2(SqList& L, int e) {
  int i,sz;
  for (i = 0; i < L.length; i++) {
    if (e == L.arr[i]) {
      sz = L.length-1;
      swap(L, i, sz);
      L.length--;
    } 
  }
}

int SqList_Del_Max(SqList& L) {
  int i;
  int pos = 0;
  int max = L.arr[0];
  for (i = 0; i < L.length; i++) {
    if (L.arr[i] > max) {
      max = L.arr[i];
      pos = i;
    }
  }
  int sz = L.length-1;
  swap(L, pos, sz);
  L.length--;
  return max;
}

//按上面的两种方法(稍作处理)可以但是效率不高
//计数方法:找到值相等则计录个数，遇到不等则根据计录用其覆盖前面相等的
//思考 单个相等和连续相等 两种情况
int SqList_Del_Multi1(SqList& L, int e) {  
  int i,count;
  for (i = 0, count = 0; i < L.length; i++) {
    if (L.arr[i] == e) 
      count++;
    else 
      L.arr[i - count] = L.arr[i];
  }
  L.length -= count;  
  int sz = L.length;
  return sz;
}

//双指针方法(会元素改变相对位置): 
//两个指针指向数组两端，low端向前遍历 若等于则与j交换、high端向前1位 并且长度减1
//否则(不等)则low端继续向前跳过不操作，直到两端错过
int SqList_Del_Multi2(SqList& L, int e) {
  int i = 0;
  int j = L.length-1;
  while (i <= j) {
    if (e == L.arr[i]) {
      L.arr[i] = L.arr[j];
      j--;
      L.length--;
    } else {
      i++;
    }
  }
  return L.length;	
}

//删除有序数组中给定值区间的元素
int SqList_Del_Interval_Sq(SqList& L, int low, int high) {
 int i, j;
 for (i = 0; i < L.length && L.arr[i] < low; i++) {} //循环找到重复区间前后下标   
 for (j = i; j < L.length && L.arr[j] <= high; j++) {} //前-等于low，后-大于high的第一位 
   
 for (; j < L.length; i++, j++)
   L.arr[i] = L.arr[j];
 L.length = i;
 return L.length; 
}

//删除无序数组中大小在给定值区间的元素
int SqList_Del_Interval(SqList& L, int low, int high) {
  int i;
  for (i = 0; i < L.length; i++) {
    if (L.arr[i] > low && L.arr[i] < high)
      swap(L, i, L.length);
      L.length--;
  } 
  return L.length;
}

//就地逆置
int Reverse(SqList& L) {
  int i, j;
  for (i = 0, j = L.length -1; i < j; i++, j--)
    swap(L, i, j);
  return L.length;
}

//旋转：使得数组向右循环移动k位
//这种方法时间和空间复杂度都很优：
//三步 1.数组就地逆置 2.前k个元素逆置(下标0~k-1) 3.剩余元素再逆置(k~L.length-1) 
int Rotate(SqList& L, int k) {
  k = k % L.length; //实际移动的步数是步长对数组长度取余的结果 
  if (k == 0)         //因为每个数组长度的移动只会使得所有元素又回到原处
    return 0;
  int i, j;
  for (i = 0, j = L.length - 1; i < j; i++, j--)  //(0,L.length-1)
    swap(L, i, j);
  for (i = 0, j = k - 1; i < j; i++, j--)         //(0,k-1)
    swap(L, i, j);
  for (i = k, j = L.length -1; i < j; i++, j--)   //(k,L.length-1)
    swap(L, i, j);
  return 1;
}

//两个有序->合并有序
//从循环比较两个数组较小的一个装入新数组 直到一个数组全部装入完毕
//将剩余的数组元素装入
int Merge(SqList L1, SqList L2, SqList& L0) {
  if ((L1.length + L2.length) > L0.length)
    return 0;
  int i, j, k;
  for (i = 0, j = 0,k = 0; i < L1.length && j < L2.length; k++) {
    if (L1.arr[i] < L2.arr[j])
      L0.arr[k] = L1.arr[i++];
    else if (L1.arr[i] > L2.arr[j])
      L0.arr[k] = L2.arr[j++];    
  } 
  while (i < L1.length)  //哪个遍历数少于其遍历数组的长度就是有剩余的数组
    L0.arr[k++] = L1.arr[i++];  //循环将剩余装入(其实这里if else的条件和循环相同所以省略了)
  while (j < L2.length)   
    L0.arr[k++] = L2.arr[j++];
  return 1;  
}

//两个数组的交集(包含重复项 ep {1,2,2,3} and {2,2} => {2,2})
//使用位标记数组
int Is_Intersect(SqList L1, SqList L2, SqList& L0) {
  int i, j;
  int k = -1;
  int mark[L2.length] = {0,0,0,0,0}; //L2的位标记数组 被标记为0的说明第一次遍历到可以放入集合 为1的表示虽然相同但是已经放入过 
  for (i = 0; i < L1.length; i++) {          //因为每次找到相同元素后标记放入后就会直接break保证了尽管重复但出现次数一直	  
    for (j = 0; j < L2.length; j++) {
      if (L1.arr[i] == L2.arr[j] && mark[j] == 0) {
        mark[j] = 1;
        L0.arr[++k] = L1.arr[i];
	break;
      } 
    }
  }
  L0.length = k + 1;
  
  printf("mark = ");
  for (int l=0; l<5; l++) 
    printf("%d",mark[l]);
  printf("\n");

  return L0.length;
}

//判断是否重复 使用标记数组（也可以用哈希表）
int Duplicate(SqList& L) {
  int mark[L.length] = {0,0,0,0,0,0,0,0,0,0};
  int i, j, k;
  for (i = 0; i < L.length; i++) {
    for (j = i + 1; j < L.length; j++) {
      if (L.arr[i] == L.arr[j]) {
        mark[i]++; //这里统计频率了 也可以在下句直接跳出外层循环	
      }
    }
  }
  for (k =0; k < L.length; k++) {
    if (mark[k] != 0)
      return 1; //存在重复
  }
  return 0;
}

//判断是否子数组
int Is_SubSet(SqList L1, SqList L2) {
  int i, j;
  for (i = 0; i <L1.length; i++) {
    if (L1.arr[i] == L2.arr[0]) {
      for (j = 0; j < L2.length && i < L1.length; ++i, ++j) {
	if (L1.arr[i] != L2.arr[j]) 
      	  break;      
      }
      if (j == L2.length)
        return 1; 
    } 
  }
  return 0;  
}

/****************
int main() {
  int res;
  SqList _L;
  int j,k;
  for (j = 0,k = 10; k > 0 ; k-- ) {
    _L.arr[j++] = k; 
  }
   
  int l;
  for (l = 0; l < _L.length; l++) {
    printf("%d\n", _L.arr[l]);
  } 
  printf("length = %d\n", _L.length);

  res = Rotate(_L, 3);

  
  for (l = 0; l < _L.length; l++) {
    printf("%d\n", _L.arr[l]);
  }  
  printf("res = %d\n", res);

  if (res == 1) { 
    printf("ok\n");
    return 1;
  } else if (res == 0){ 
    printf("false\n");
    return 0;
  }
} 
******************************/
/***********
int main() {
  int res;
  SqList _L;
  int temp[10] = {1,2,3,4,5,6,7,8,9,10};
  int j;
  for (j = 0; j < 10; j++ ) {
    _L.arr[j] = temp[j]; 
  }
  int l;
  for (l = 0; l < _L.length; l++) {
    printf("%d\n", _L.arr[l]);
  }
  printf("********************\n");

  res = Duplicate(_L);

  for (l = 0; l < _L.length; l++) {
    printf("%d\n", _L.arr[l]);
  }
  printf("res = %d\n",res);  

  return res;
}
********/


int main() {
  int res;
  SqList _L1, _L2, _L0;
  _L1.length = 5;
  _L2.length = 2;
  _L0.length = 13;

  int _L1_temp[5] = {9,1,3,3,8};	  
  int _L2_temp[5] = {1,3,2};
  int p, q;
  for (p = 0; p < _L1.length; p++) {
    _L1.arr[p] = _L1_temp[p];  
  }
  for (q = 0; q < _L2.length; q++ ) {
    _L2.arr[q] = _L2_temp[q];
  }

  res = Is_SubSet(_L1, _L2);
  /***
  int l;
  for (l = 0; l < _L0.length; l++) {
    printf("%d\n", _L0.arr[l]);
  }***/
  //printf("pos_9 = %d\n", _L0.arr[2]);
  printf("res = %d\n", res);  
}



