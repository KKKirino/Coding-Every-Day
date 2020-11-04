from itertools import permutations
import math
from typing import Callable
from collections import deque

class EightFigurePuzzle():
  def __init__(self, puzzle: list, target: list, h_function: Callable[[list, list], int] = None):
    self.puzzle = puzzle
    self.target = target
    self.h_function = self.default_h_function if h_function is None else h_function

  def solve(self):
    dq = deque([(self.puzzle, 0)])


  def default_h_function(self, state: list, target: list) -> int:
    rows, cols = len(state), len(state[0])
    h = 0
    for r in range(rows):
      for c in range(cols):
        h += int(state[r][c] != target[r][c])
    return h

if __name__ == "__main__":
  puzzle = [
    [1, 3, 0],
    [8, 2, 4],
    [7, 6, 5]
  ]