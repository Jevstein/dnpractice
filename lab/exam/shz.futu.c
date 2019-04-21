



//////////////////////////////////////////
// 1.一面
// 1.删除字符串中的空格，并返回空格的个数，时间复杂度要求 O（n），空间复杂度要求O(1)
// 举例  输入"a b c"，处理之后变成"abc"，并返回2
{
      int func(char *s) {
            char *p1 = NULL;//空格
            char *p2 = NULL;//字母

            int n = 0;
            int pos = 0;

            for (int i=0; i<len(s); i++) {
                  if (s[i] == '\0')
                        return;

                  if (s[i] == ' ') {
                        p1 = s[i];
                        n++;
                  } else {
                        p2 = s[i];
                        
                        if (p1) {
                              *p1 = *p2;
                              *p2 = ' ';
                        }
                  }
            }

            return n;
      }
}

// 2.判断字符串小括号是否匹配
{
      struct stack{
            char *x;
            int len;
            int capacity;
      }

      void push(stack *S, char *c){

      }

      char pop(stack *S){

      }

      char top(stack *S)
      {

      }

      bool empty() {
            return len == 0;
      }

      main()
      {
            stack s;

            char *s = "a()()((()"
            int len = strlen(s);
            int i=0;
            for (i=0; i<len; i++) {
            if (s[i] == '(') {
            push(&s, s[i]);
            } else if (s[i] == ')') {
            if (!pop(&s)){
            //不匹配
            }
            }
            }

            if (!empty())
                  //不匹配
      }
}

// 3.{25,17,31,41,47,45,42}, 找出比左边大且比右边小大数，如： 31，41
{
      //0.申请一个空间Q，如bitset

      //1.从左到右遍历： 找出满足大于左边的所有数，放入空间Q中

      //2.从右到左遍历： 找出满足小于右边的所有数，若这些数同时存在空间Q中，即那便是要找的数

      // 空间复杂度： O(2*n)
}

//////////////////////////////////////////
// 2.二面
//1.	生成扫雷，m*n的空间，k个雷，非雷的地方填数字(数字代表周围有几个雷）： 生成地图 （m*n，k）   
//[i][j]==0： 雷
//[i][j] > 0:    num
{
      int ** func (int m, int n, int k) {
            assert(k < m * n);
            
            int **map = (int *)calloc(m,  n * sizeof(int));
            int i =0, j=0;
            for ()
            
            //1.随机生成k个雷的位置
            
            //2.遍历除雷外的空格区域，赋值为查找出的周边雷的个数

            return map;
      }
}
      
// 2.	字符串，去重，保证顺序
      //kmp
     //"a abcdf a"
     // p r
     //00000011 11111111 1111111111 11111111
{
      void func(char *s) {
            assert(s);

            int bitset = 0; 
            char *p = s;
            char *r = p;

            for (; *r !='\0';  r++) {
                  int idx = 1 << (*r - 'a');
                  if (idx & bitset) {//重复
                        continue;
                  } else {
                        bitset |= idx;
                        *p++ = *r;
                  }
            }
            *p = '\0';
      }
}
