from __future__ import annotations
from itertools import permutations
import math
from typing import Callable, Mapping, List, Tuple
from queue import PriorityQueue

class EFPuzzleState():
  """State definition for Eight Figure Puzzle."""

  def __init__(self, state: str, g: int, h: int, parent: str) -> None:
    """Define the state with string, g value and h value and parent index."""
    self.state = state
    self.g = g
    self.h = h
    self.f = g + h
    self.parent = parent

  def __lt__(self, other: EFPuzzleState) -> bool:
    """Override operator '<'"""
    return self.f < other.f

  @staticmethod
  def vector2matrix_index(vector_index: int, width: int = 3) -> Tuple[int, int]:
    """Convert vector index to matrix index."""
    return (vector_index // width, vector_index % width)

  @staticmethod
  def matrix2vector_index(matrix_row_index: int, matrix_col_index: int, width: int = 3) -> int:
    """Convert matrix index to vector index."""
    return matrix_row_index * width + matrix_col_index


class EightFigurePuzzle():
  def __init__(self, puzzle: str, target: str, h_function: Callable[[str, str], int] = None):
    """Define the puzzle with init state, targe state and h(x).

    Args:
      puzzle: a string denotes a initial state of puzzle
      target: a string denotes a target state of puzzle
      h_function: h(x)
    """
    self.puzzle = puzzle
    self.target = target
    self.h_function = self.default_h_function if h_function is None else h_function
    self.close_list = {} # type: Mapping[str, EFPuzzleState]

  def solve(self):
    """Solve the puzzle."""
    open_list = PriorityQueue() # type: PriorityQueue[EFPuzzleState]
    # 1. add initial state to priority queue
    open_list.put(EFPuzzleState(self.puzzle, 0, self.h_function(self.puzzle, self.target), None))
    # 2. do a star algo
    while not open_list.empty():
      cur_state = open_list.get()
      if cur_state.state in self.close_list: continue
      self.close_list[cur_state.state] = cur_state
      if cur_state.state == self.target: break
      for adj_state_str in self.get_adj_states_list(cur_state.state):
        open_list.put(EFPuzzleState(adj_state_str, cur_state.g + 1, self.h_function(adj_state_str, self.target), cur_state.state))

  def show_output(self):
    """Show output."""
    print('Init State:\n' + self.format_output_string(self.puzzle))
    print('Target State:\n' + self.format_output_string(self.target))
    path = [] # type: List[str]
    state_str = self.target
    while state_str in self.close_list:
      path.append(state_str)
      state_str = self.close_list[state_str].parent
    if not path:
      print('No Solution.')
      return
    print('\nPath:')
    while path:
      print(self.format_output_string(path.pop()) + '\n')

  @staticmethod
  def format_output_string(state_str: str) -> str:
    """Format state string to formated string."""
    state_matrix = EightFigurePuzzle.string2matrix(state_str)
    return '\n'.join(' '.join(map(str, line)) for line in state_matrix)

  @staticmethod
  def get_adj_states_list(cur_state_str: str, width: int = 3) -> List[str]:
    """Get adjacent state list."""
    height = len(cur_state_str) // width
    adj_state_list = [] # type: List[str]
    zero_vector_index = cur_state_str.index('0')
    zr, zc = EFPuzzleState.vector2matrix_index(zero_vector_index)
    for dr, dc in [[-1, 0], [1, 0], [0, -1], [0, 1]]:
      nr, nc = zr + dr, zc + dc
      if nr < 0 or nr >= height or nc < 0 or nc >= width: continue
      vector_index = EFPuzzleState.matrix2vector_index(nr, nc)
      cur_state_vector = list(cur_state_str)
      cur_state_vector[zero_vector_index], cur_state_vector[vector_index] = \
        cur_state_vector[vector_index], cur_state_vector[zero_vector_index]
      adj_state_list.append(''.join(cur_state_vector))
    return adj_state_list

  @staticmethod
  def default_h_function(state: str, target: str) -> int:
    """Compute h function for given init state and target state."""
    return sum(s != t for s, t in zip(state, target))

  @staticmethod
  def matrix2string(matrix: List[List[int]]) -> str:
    """Convert matrix to string."""
    return ''.join(''.join(map(str, line)) for line in matrix)

  @staticmethod
  def string2matrix(state_string: str, width: int = 3) -> List[List[int]]:
    """Convert string to matrix."""
    height = len(state_string) // width
    matrix = [[0] * width for i in range(height)]
    for i in range(len(state_string)):
      r, c = EFPuzzleState.vector2matrix_index(i)
      matrix[r][c] = int(state_string[i])
    return matrix

if __name__ == "__main__":
  puzzle_str = input('Please input initial state: ')
  target_str = input('Please input target state: ')
  solver = EightFigurePuzzle(puzzle_str, target_str)
  solver.solve()
  solver.show_output()