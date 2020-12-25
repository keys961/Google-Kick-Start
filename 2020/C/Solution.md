[![green-pi](https://img.shields.io/badge/Rendered%20with-Green%20Pi-00d571?style=flat-square)](https://github.com/nschloe/green-pi?activate&inlineMath=$)

# Kick Start 2020 C

## A: Countdown

> 关键词：数组

白给的，扫描计数就行。

## B: Stable Wall

> 关键词：拓扑排序

对于第一组样例而言，可以暴力搜索解决，但对于第二个样例就必定超时。

这里我们维护3个字段：

- `visited[26]`：表示还有哪些字母没有放置
- `min_indices[26][col]`：表示对于某个字母，每一列的最小行号，从最底下开始算
- `max_indices[26][col]`：表示对于某个字母，每一列的最大行号，从最底下开始算

首先我们扫描整个矩阵，填充这3个字段。

然后先预先检查可行性，这里只需要检查同一字母是否出现“コ”形，假如出现则一定无解，这个也很容易。

然后开始拓扑排序：

1. 寻找所有`min_indices[c]`全为0的字母`c`，添加到队列中，并设置`visited[c] = false`。
2. 弹出队列加入到解中
3. 扫描其它未入队的字母，假如`max_indices[c][i] == min_indices[c'][i] - 1`，则设置`min_indices[c'][i] = 0`，
4. 若`min_indices[c']`全为0，则将`c'`入队，设置`visited[c'] = false`
5. 重复第2步，直到队列为空为止

可以得知，即使使用最烂的写法，上面的步骤时间复杂度最多为 $O(N^2C+NRC)$ ，也能满足题目要求了。

## C: Perfect Subarray

> 关键词：散列表，前缀和

求子数组的和，可以使用前缀和加速，这点不多赘述。

然而要计算子数组个数，若要扫描前缀和数组，也有$O(N^2)$的时间复杂度，肯定会超时。

注意到数组元素 $-100 \le A_i \le 100$ ，长度最大为 $10^5$ ，我们可以判定整个数组最大和为 $10^7$ ，因此可以通过这个空间搜索，搜索次数可以至少降低到 $\sqrt{10^7}=10^{3.5}\approx3162$ ，次数远小于 $10^5$ 。

由于数组存在负数，我们需要记录下面的字段：

- `prefix_sum`：一个散列表，键为前缀和，值为次数，初始有`prefix_sum[0] = 1`
- `min_sum`：当前最小前缀和
- `max_sum`：当前最大前缀和
- `sum`：当前前缀和

这里一个一个遍历数组元素，遍历时：

- 更新前缀和`sum`
- 易知，我们需要的完全平方数`target`必在`[max(sum - max, 0), sum - min]`，所以在这个空间搜索（用 $O(\sqrt{N})$ 方式）。对于每个`target`，查找`prefix_sum[sum - target]`，并将其增加到结果中

整体时间复杂度为 $O(N * \sqrt{NA_{max}})$ 。

## D. Candies

> 关键词：前缀和，线段树

这里看似很麻烦，实际上图示一下就比较容易理解了。

这里引用Google题解的图，原数组为`[5, 2, 7, 4, 6, 3, 9, 1, 8]`，当查询完整的数组时，需要计算整个三角形的和：

![img](https://codejam.googleapis.com/dashboard/get_file/AQj_6U184qxEuWRNTp3PZXNWBgZiKf2C9h2gA2UsOpoG4Fp_90YVMEw79q9eQvC_yLznXMZz4dL2/query_1_9.png)

而查询部分数组时，例如查询`[5, 8]`区间，那么需要计算蓝色三角的和，它等于整个大三角减去橙色和灰色的：

![img](https://codejam.googleapis.com/dashboard/get_file/AQj_6U1AJAna9pJJYIWOEqS1_eH01sCGHp-j0FgthFZ_JyFLkjnKKCILoMLwTPc6AWSPRnQSWtxz/query_5_8.png)

### 前缀和

这个计算可以很容易通过前缀和解决，定义2个前缀和函数：

- $f_1(x) = \sum_{i=1}^{x}{((-1)^{i-1} \cdot A_{i} \cdot i)}$ ：计算大三角的前缀和
- $f_{2}(x) = \sum_{i=1}^{x}{((-1)^{i-1} \cdot A_{i})}$ ：计算大三界最底下的那行前缀和

那么查询的时候就有：
$$
Q(x, y) = (-1)^{x-1} \{ [f_{1}(y)-f_{1}(x-1)]-(x-1)[f_{2}(y)-f_{2}(x-1)] \}
$$
此时：

- 查询时间复杂度为 $O(1)$ 
- 更新时间复杂度为 $O(N)$ 

这个解法可以通过测试1，但无法通过测试2，因为更新时间复杂度过高。

### 线段树

解决前缀和解法不足的方式就是线段树，这里对序列 $((-1)^{i-1} \cdot A_{i} \cdot i)$ 和 $((-1)^{i-1} \cdot A_{i})$ 构建2个线段树 $t_1$ 和 $t_2$ ，合并操作为求和。

此时查询的公式就变为：
$$
Q(x, y) = (-1)^{x-1} \{ [t_{1}.query(y,x)]-(x-1)[t_{2}.query(y,x)] \} \tag{x,y为闭区间}
$$
此时：

- 查询时间复杂度为 $O(\log{N})$ 
- 更新时间复杂度为 $O(\log{N})$ 

这样就能通过测试2。
