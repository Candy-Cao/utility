
from bisect import bisect_left
from typing import List

#最长递增子序列（严格递增）；交换状态和状态的值。
#贪心：定义g[i] 为 长为(i + 1)的递增子序列的最小结尾元素；
class Solution:
    def LIS(self, nums: List[int]) -> int:
        g = []
        for x in nums:
            j = bisect_left(g, x)
            if j == len(g):
                g.append(x)
            else:
                g[j] = x
        return len(g)