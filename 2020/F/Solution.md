[![green-pi](https://img.shields.io/badge/Rendered%20with-Green%20Pi-00d571?style=flat-square)](https://github.com/nschloe/green-pi?activate&inlineMath=$)

# Kick Start 2020 F

## A: ATM Queue

> 关键词：排序

小数据量下，本题可以通过模拟解决，但大数据量下会TLE。

这里可以得到2个结论：

- 取钱次数多的人一定在取钱次数少的后面取完
- 若取前次数一样，则排在队列前面的人先取完

所以可以根据上面2个结论，对队列的所有人进行排序，然后输出即可。

时间复杂度为 $O(N\log{N})$ 。

## B. Metal Harvest

> 关键词：数组

首先对`intervals`排序；

然后记录一个`cursor`表示当前位置之前的都被覆盖，初始为`intervals[0].first`；

然后往后遍历：

- 若当前`intervals[i]`剩余的部分大于`k`，那么需要额外部署`(intervals[i].second - cursor) / k`个机器人，然后更新`cursor`到对应位置
- 若当前`intervals[i]`剩余的部分等于`k`，则部署1个机器人，然后更新`cursor`到`intervals[i + 1].first`
- 否则，部署1个机器人，然后向后查找`intervals`，找到最小的`j`满足`intervals[j].second > cursor + k`，更新`cursor`为`max(intervals[j].first, cursor + k)`
  - 前者的情况是`cursor + k`小于了`intervals[j].first`，为了达到最优，需要快进到`intervals[j].first`

最后返回结果。

时间复杂度为 $O(N\log{N})$ 。

## C. Painters' Duel

> 关键词：深度搜索，博弈

本题典型的博弈题。

这里定义一个函数 $f(pos_A, pos_B, cnt_A, cnt_B)$ ，它表示在 $A$ 为先手， $A$ 访问了 $cnt_A$ 个房屋， $B$ 访问了 $cnt_B$ 个房屋的情况下， $A$ 能获取的最高得分。

那么可以得到下面的递推式：

$$
\begin{equation}

f(pos_A, pos_B, cnt_A, cnt_B)=

\left\{
             \begin{array}{lr}
             \max{\lbrace -f(pos_B, nextpos_A, cnt_B, cnt_A+1)\rbrace} & 当A可以移动,nextpos_A合法 \\
             -f(pos_B, pos_A, cnt_B, cnt_A) & 当A不可以移动\\
             cnt_A - cnt_B & 当A和B都不能移动  
             \end{array}
\right.

\end{equation}
$$

这个递推式可通过DFS搜索得到。

而对于时间复杂度，易知除了第一步之外，其它步骤最多只有2个扇出，所以有：

-  $T(N) = 2 \cdot T(N-1)$
-  $T(0) = O(1)$

所以时间复杂度为 $O(2^N) = O(2^{S^2})$ ， $S$ 最大为6，似乎不够，但是实际上多数搜索的深度不会达到最大值，所以还是能过测试用例的。

另外的优化可以有：记忆化搜索，Alpha-Beta剪枝等。

## D. Yeetzhee

> 关键词：概率，深度搜索

这里参考了这篇文章：https://blog.csdn.net/weixin_51000954/article/details/108890978。写的很不错，这里整理一下。

定义函数 $f(state)$ 为状态 $state$ 转化为状态 $target$ 的期望次数，这里：

-  $state$ 和 $target$ 都为每组点数的数量（不过没有绑定组号，所以顺序改变，状态依旧是同一个状态）

-  $target$ 等于给定参数`groups`，且 $state$ 和 $target$ 都逆序排序
- 初始时 $state$ 为空，表示当前没有出现任何组

首先，若投掷骰子的点数在之前出现过，我们遍历出现过的每个组，每个组的概率是 $1/M$ ，所以这种情况下，会有：
$$
f_{1}(state) = \sum_{0 \le i \lt len(state)}\frac{1}{M}[1+f(new\_state_i)]  \tag{new_state[i] = state[i]+1且new_state合法}
$$
然后，若投掷骰子的点数在之前没出现过，此时的概率为 $1-len(state)/M$ ，这里往 $state$ 后面追加1，然后会有：
$$
f_{2}(state) = (1-\frac{len(state)}{M})\cdot [1+f(new\_state)] \tag{new_state在state基础锁追加了1, 且new_state合法}
$$
而 $new\_state$ 合法需要满足逆序排序下， $new\_state[i] \le target[i]$ ，且 $new\_state$ 长度不能超过 $target$ 。

在第1个和第2个情况下，都有可能出现不合法的情况，从而导致重新投掷，这里记录不合法的点数次数 $invalid$ ：

- 对于第1个情况，若新状态不合法，则计数+1
- 对于第2个情况，若新状态不合法，则计数增加 $M - len(state)$ 

根据递归的期望，可以得到下面的方程式：
$$
f(state) = P_{invalid} \cdot (1 + f(state)) + f_{valid}(state)
$$
而：
$$
f_{valid}(state) = f_{1}(state) + f_{2}(state) \\
P_{invalid} = \frac{invalid}{M}
$$
所以上面的答案就可以得到：
$$
f(state)=\frac{f_{1}(state)+f_{2}(state)+\frac{invalid}{M}}{1-\frac{invalid}{M}}
$$
而 $f_{1}$ 和 $f_{2}$ 可以通过DFS求得。为了加速，可以将DFS的结果记忆化。

上面的引文也指出，状态总数最大在百万级别，所以不会出现TLE和MLE。