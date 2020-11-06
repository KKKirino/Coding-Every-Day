from typing import List
def binary_search(nums: List[int], x: int) -> int:
  """Define template of Binary Search."""
  l, r = 0, len(nums) - 1
  while l < r:
    m = (l + r) // 2
    if nums[m] >= x: r = m
    else: l = m + 1
  return l
