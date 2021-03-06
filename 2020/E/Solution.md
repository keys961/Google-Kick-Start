[![green-pi](https://img.shields.io/badge/Rendered%20with-Green%20Pi-00d571?style=flat-square)](https://github.com/nschloe/green-pi?activate&inlineMath=$)

# Kick Start 2020 E

## A: Longest Arithmetic

> 关键词：数组

白给，扫描就行。

## B: High Buildings

> 关键词：数组

首先有一个结论：共同看到的建筑是最高的，高度相同。

所以对于这里的 $A$, $B$, $C$，可以用下面的策略排列：

- 前 $A - \lceil C/2 \rceil$ 个建筑递增，这里直接填充 $N-1$
- 后 $B - \lfloor C/2 \rfloor$ 个建筑递减，这里直接填充 $N-1$ 
- 根据上面的，直接将 $C$ 个最高建筑平均分摊到上面两个中间
- 最中间剩余部分填充1

而为了过样例，需要 $A \le B$，所以出现 $A \gt B$，则需要交换一下顺序，并最后逆序序列。

> 反例：$A=2, B=1, C=1, N=4$，若不做上面的处理，则得到序列`[3,4,1,3]`，显然不对；而做了上面处理，最后得到的是`[4,1,1,3]`，这就对了。

而构建序列之前，首先判断不可能的情形，这里很明显：

-  $A + B - C \gt N$
-  $A = 1, B = 1, C = 1, N \ne 1$

## C: Toys

> 关键词：贪心、优先队列

问题分为2步：

1. 判断玩耍是否可能无限循环下去
2. 若不能无限玩耍，去掉哪些玩具后，玩耍时间最长

### a. 判断是否能无限完下去

若要无限玩下去，需要所有的玩具 $i$ 满足：$r_{i} \le \sum_{j \ne i}{e_{j}}$，即
$$
r_{i} + e_{i} \le \sum_{j}{e_{j}} \tag{1}
$$

我们对 $r_{i} + e_{i}$ 进行考察，若我们去掉了较小的 $r_{i} + e_{i}$ ，而它不能满足上式 $(1)$，那么比它大的也肯定不满足，所以拿掉这样的玩具会造成额外的操作，并不是最优的。

所以我们可以将所有的 $r_{i} + e_{i}$ 放入一个最大堆中，每次检查堆顶是否满足上式 $(1)$，若不满足则弹出堆顶并修改上式 $(1)$ 的右边。这样的检查直到堆顶满足上式或者堆为空为止，前者代表能无限玩下去，后者代表不能无限玩下去。

### b. 若不能无限玩耍，去掉哪些玩具

若不能无限玩下去，那么玩具最多只能被玩2次。

这里依旧会用到式 $(1)$ ：

- 首先初始化最后能玩的时间`val`为 $\sum_{j}{e_{j}}$，初始化`del`为0，表示所有玩具被玩了1次
- 扫描每个玩具
  - 若该玩具满足式 $(1)$ ，说明它能玩2次，将其加入到最大堆中
  - 若不满足，则将其移除，更新`val`和`del`，并更新式 $(1)$ 的右边，然后不断检查堆顶是否满足式 $(1)$ ，若不满足则不断弹出堆顶，并更新`val`和`del`和式 $(1)$ 的右边
- 更新`val`，并计算`val`的最大值，若`val`更大，则更新`del`的最小值
- 最后返回答案

## D. Golden Stone

> 关键词：图、最短路径

这里虽然给了城市的图，但是这里不会在这张图搜索，而是转化成另一个图，它的顶点是 $V = \lbrace (c, s) | c \in N, s \in S \rbrace$，即城市和石头的点对作为顶点。

那么边如何定义？有下面2点：

1. 若 $c$ 本来拥有石头 $s$ ，那么有一条无向边连接了 $(c, s)$ 和 $(c',s)$ ，其中 $c$ 和 $c'$ 有条路径相连
2. 若 $c$ 通过转换和本来拥有的石头得到了石头集合 $S_{c}$ ，而这个集合能够转化为石头 $s'$ ，那么会有一条无向边连接了 $(c, S_{c})$ 和 $(c, s')$

题目中需要我们求得到达顶点 $(c,1)$ 的路径最短长度，即 $\min_{c \in N}\lbrace cost(c,1)\rbrace$ ，由于有上面2条性质，我们可以使用Dijkstra算法：

- 首先初始化所有的 $cost(c,s) = inf$根据输入，此外维护一个 $recipe\_cost(c,r) = 0$ 表示使用石头转换所需的开销
- 然后根据上面的第1点，置 $cost(c,s) = 0$ ，然后将其压入最小堆中
- 不断弹出最小堆堆顶，弹出的堆顶标记 $(c,s)$ 已经访问，若没访问过，则：
  - 首先更新 $recipe\_cost(c,r)$ （直接累加 $cost(c,s)$ ），判断转换是否已经满足要求，若满足要求，则判断 $recipe\_cost(c,r)$ 是否优于 $cost(c,s')$ ，若优于，则更新 $cost(c,s')$ 并将其压入最小堆中，这一步对应的是第2点提及的边
  - 然后更新 $cost(c',s)$ ，对应的开销是 $cost(c, s)+1$ ，若得到的开销优于原有的，则更新并将 $cost(c',s)$ 压入最小堆中