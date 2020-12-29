[![green-pi](https://img.shields.io/badge/Rendered%20with-Green%20Pi-00d571?style=flat-square)](https://github.com/nschloe/green-pi?activate&inlineMath=$)

# Kick Start 2020 D

## A: Record Breaker

> 关键词：数组

白给的，扫描计数就行。

## B: Alien Piano

> 关键词：动态规划

定义一个函数 $f(i,c)$ ，代表第 $i$ 个位置设置成音符 $c$ 时，序列 $A[i:]$ 的冲突次数。

那么很容易的能够得到递推式：

- 若 $A[i] = A[i+1]$ ，则 $f(i,c)=f(i+1,c)$
- 若 $A[i] \lt A[i+1]$ 
  - 若无法变大，则 $f(i,c)=1 + \min_{1 \le j \le 4}{f(i+1,j)}$ 
  - 否则 $f(i,c)=\min_{c \lt j \le 4}{f(i+1,j)}$ 
- 若 $A[i] \lt A[i+1]$ 
  - 若无法变大，则 $f(i,c)=1 + \min_{1 \le j \le 4}{f(i+1,j)}$ 
  - 否则 $f(i,c)=\min_{1 \le j \lt c}{f(i+1,j)}$ 
- 初始边界设为0

## C: Beauty of Tree

> 关键词：概率，深度搜索，树，后缀和

假如我们要计算题目中的期望值，需要计算 $N$ 个可能的方案中每个节点的访问次数 $c_{i}$ ，这样就可以计算某个用户 $u$ 访问某个节点 $i$ 的概率：
$$
P_{u}(i) = \frac{c_{i}}{N}
$$
而这里涉及2个用户，它们是独立事件，而这里需要知道2个用户访问到节点 $i$ 的概率，这个概率是“或”关系，很容易通过摩根率得出：
$$
P(i)=1-[(1-P_{u}(i)) \cdot (1-P_{v}(i))]=P_{u}(i)+P_{v}(i)-P_{u}(i) \cdot P_{v}(i)
$$
而涂上某个点的得分为1，那么期望就是树上所有节点概率的总和，即：
$$
E=\sum_{i \in T}P(i)
$$
那么问题就剩下求“ $N$ 个可能的方案中每个节点的访问次数 $c_{i}$ ”，这可以通过一遍的DFS做到：

- 首先根据输入，构建一个树，对于每个节点保存它的儿子节点
- 从根节点开始搜索，维护一个搜索路径`path`
  - 首先DFS每个儿子节点
  - 然后对自己节点的计数`count[i] += 1`（代表从自己节点开始往上走的路径）
  - 最后根据给的步长`step`，往回找路径上的节点，增加自己节点的计数，即`count[path[-step]] += count[i]`（向上传递起始节点在下面的计数，类似后缀和）

总体时间复杂度为 $O(N)$ 。

## D. Locked Doors

> 关键词：

现在只做出一个naive的做法，使用双指针做，时间复杂度为$O(NQ)$，能过样例1，但不能过样例2。