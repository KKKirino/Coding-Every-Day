import collections

'''
岛屿数量：

给定一个 n * n 的区域，里面有海洋还有陆地，形如：

1011001
0100111
0100011
0100001

其中 1 表示该处为陆地，0 表示为海洋，我们定义两块四连通的陆地是连接在一起的，多块连通的陆地可以形成岛屿。

问给定的区域内有多少个岛屿？

input:
[
  '1011001',
  '0100111',
  '0100011',
  '0100001',
]

output:
4
'''

def count_islands(blocks: list) -> int:
  if len(blocks) == 0 or len(blocks[0]) == 0:
    return 0

  rows, cols = len(blocks), len(blocks[0])
  visited = [[0] * cols for i in range(rows)]
  count = 0
  for r in range(rows):
    for c in range(cols):
      if blocks[r][c] == '1' and visited[r][c] == 0:
        dfs_for_islands(blocks, visited, r, c)
        count += 1
  return count 

def dfs_for_islands(blocks, visited, r, c):
  if visited[r][c] or blocks[r][c] == '0': return

  visited[r][c] = 1
  d = [[0, 1], [0, -1], [-1, 0], [1, 0]]
  for dr, dc in d:
    nr, nc = r + dr, c + dc
    if nr >= len(blocks) or nr < 0 or nc >= len(blocks[0]) or nc < 0: continue
    dfs_for_islands(blocks, visited, nr, nc)


test_case_for_islands = [
  '1011001',
  '0100111',
  '0100011',
  '0100001',
]

print('Count islands: ', count_islands(test_case_for_islands))

'''
进阶问题：输出每个岛屿的大小。

input:
[
  '1011001',
  '0100111',
  '0100011',
  '0100001',
]

output:
[1, 2, 4, 3]
'''

def count_islands_with_area(blocks):
  if len(blocks) == 0 or len(blocks[0]) == 0:
    return 0

  rows, cols = len(blocks), len(blocks[0])
  visited = [[0] * cols for i in range(rows)]
  shared_var = [0]
  res = []
  for r in range(rows):
    for c in range(cols):
      if blocks[r][c] == '1' and visited[r][c] == 0:
        shared_var[0] = 0
        dfs_for_islands_with_area(blocks, visited, r, c, shared_var)
        res.append(shared_var[0])

  return res

def dfs_for_islands_with_area(blocks, visited, r, c, shared_var):
  if visited[r][c] or blocks[r][c] == '0': return 0

  shared_var[0] += 1
  visited[r][c] = 1
  d = [[0, 1], [0, -1], [-1, 0], [1, 0]]
  for dr, dc in d:
    nr, nc = r + dr, c + dc
    if nr >= len(blocks) or nr < 0 or nc >= len(blocks[0]) or nc < 0: continue
    dfs_for_islands_with_area(blocks, visited, nr, nc, shared_var)

print('Count islands with area: ', count_islands_with_area(test_case_for_islands))

'''
进阶问题：使用迭代式 BFS 解决上述问题。
'''

def count_islands_bfs(blocks: list) -> int:
  if len(blocks) == 0 or len(blocks[0]) == 0:
    return 0

  d = [[0, 1], [0, -1], [-1, 0], [1, 0]]
  rows, cols = len(blocks), len(blocks[0])
  count = 0
  blocks = [list(line) for line in blocks]
  for r in range(rows):
    for c in range(cols):
      if blocks[r][c] == '1':
        queue = [(r, c)]
        blocks[r][c] == '0'

        while queue:
          [r, c] = queue.pop(0)
          for dr, dc in d:
            nr, nc = r + dr, c + dc
            if nr >= len(blocks) or nr < 0 or nc >= len(blocks[0]) or nc < 0 \
              or blocks[nr][nc] == '0': continue
            queue.append([nr, nc])
            blocks[nr][nc] = '0'

        count += 1
  return count


def count_islands_area_bfs(blocks: list) -> int:
  if len(blocks) == 0 or len(blocks[0]) == 0:
    return 0

  d = [[0, 1], [0, -1], [-1, 0], [1, 0]]
  rows, cols = len(blocks), len(blocks[0])
  res = []
  blocks = [list(line) for line in blocks]
  for r in range(rows):
    for c in range(cols):
      if blocks[r][c] == '1':
        queue = [[r, c]]
        count = 0

        while queue:
          [cr, cc] = queue.pop(0)
          if blocks[cr][cc] == '0': continue
          count += 1
          blocks[cr][cc] = '0'
          for dr, dc in d:
            nr, nc = cr + dr, cc + dc
            if nr >= len(blocks) or nr < 0 or nc >= len(blocks[0]) or nc < 0: continue
            queue.append([nr, nc])

        res.append(count)
  return res

test_case_for_islands_bfs = [
  '1011001',
  '0100111',
  '0100011',
  '0100001',
]

print('Count islands with my bfs: ', count_islands_bfs(test_case_for_islands_bfs))

print('Count islands area with my bfs: ', count_islands_area_bfs(test_case_for_islands_bfs))


