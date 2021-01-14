[![green-pi](https://img.shields.io/badge/Rendered%20with-Green%20Pi-00d571?style=flat-square)](https://github.com/nschloe/green-pi?activate&inlineMath=$)

# Kick Start 2020 G

## A: Kick_Start

> 关键词：字符串

一遍扫描，维护一个`KICK`数量`n`：

- 若扫描到`KICK`，则`n += 1`
- 若扫描到`START`，则答案`ans += n`

注意考虑`KICK`的重叠，因为它首位字母相同。

## B. Maximum Coins

> 关键词：数组

扫描并获得和最大的对角线即可。

## C. Combination Lock

> 关键词：前缀和、二分查找

首先对 $W$ 排序，可以确定最优解一定在 $W$ 中的某个位置。

我们假定最优解为 $W_{i}$ ，那么首先是判断是否需要绕过边界的问题：

1. 若 $j \lt i$ ，若要绕行则必须有 $W_{j}+N-W_{i} \le W_{i} - W_{j}$ ，即 $W_{j} \le W_{i} - \lceil \frac{N}{2} \rceil$ 

2. 若 $j \gt i$ ，若要绕行则必须有 $W_{i}-(W_{j}-N) \le W_{j} - W_{i}$ ，即 $W_{j} \ge W_{i} + \lceil \frac{N}{2} \rceil$ 

由于 $W$ 已排序，所以可以通过二分法得到上述1和2的左边界 $l$ 和右边界 $r$ ，在 $l$ 之前的和在 $r$ 之后的 $W_j$ 都需要绕过边界。

接下来计算变动次数，首先计算左边不绕过边界的次数，如下式所述：
$$
f_{1}=(W_{i}-W_{l+1})+ ...+(W_{i}-W_{i-1})= (i-l-1) \cdot W_{i} - \sum_{l+1 \le j \le i-1}{W_j} \tag{1}
$$
然后计算右边不绕过边界的次数：
$$
f_{2}=(W_{i+1}-W_{i})+...+(W_{r-1}-W_{i}) = \sum_{i+1 \le j \le r-1}{W_j} - (r-i-1) \cdot W_{i} \tag{2}
$$
然后计算左边绕过边界的次数：
$$
f_{3}=(W_{1}+n-W_{i})+ ...+(W_{l}+n-W_{i})= \sum_{1 \le j \le l}{W_j} + l \cdot (n - W_{i}) \tag{3}
$$
然后计算右边绕过边界的次数：
$$
f_{4}=(W_{i}-(W_{r}-n))+ ...+(W_{i}-(W_{w}-n))= (w-r+1) \cdot (n + W_{i})-\sum_{r \le j \le w} W_{j} \tag{4}
$$
上述4式中的求和项可以通过前缀和得到，所以对于某个 $W_{i}$ ，求解移动次数需要的时间复杂度为 $O(\log{W})$ 。我们对每个 $W_{i}$ 计算这样的移动次数，然后取最小值，总的时间复杂度为 $O(W\log{W})$ 。

## D. Merge Cards

> 关键词：动态规划、数学

当前只写出了暴力求解，待我研究下去AC这道题。