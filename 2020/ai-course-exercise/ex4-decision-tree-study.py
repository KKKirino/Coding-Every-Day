"""AIcourse ex4 Decision Tree Study"""
from __future__ import annotations
from typing import Tuple, List

import os
import numpy as np

class DecisionTreeNode:
  """Definition of the decision tree node."""
  
  def __init__(self, values: np.ndarray, labels: np.ndarray, classes: List[int], \
    depth: int = 0, max_depth: int = None) -> None:
    """Definition of the node.
    
    Args:
      values: array of fit data
      labels: labels of data
      classes: all classes
      depth: current depth of the node
      max_depth: max depth of tree
    """
    self.values = values
    self.labels = labels
    self.classes = classes
    self.depth = depth
    self.max_depth = max_depth
    self.info = self.get_info(labels)
    self.col_index: int = -1 
    self.split_point: float = None
    self.l, self.r = self.build_children()
    self.label = self.vote_class()
    

  def build_children(self) -> Tuple[DecisionTreeNode, DecisionTreeNode]:
    """Build the decision tree with ID3 algorithm."""
    if self.depth >= self.max_depth or self.if_leaf(): return None, None
    n = self.labels.size 
    max_split_point, max_split_col, max_info_gain = float('-inf'), -1, float('-inf')
    for col in range(self.values.shape[1]):
      val_range = np.sort(np.unique(self.values[:, col]))
      for i in range(len(val_range) - 1):
        split_point = (val_range[i] + val_range[i + 1]) / 2
        left_set = self.labels[self.values[:, col] < split_point]
        right_set = self.labels[self.values[:, col] > split_point]
        split_info = sum(s.size / n * self.get_info(s) for s in [left_set, right_set])
        info_gain = self.info - split_info
        if info_gain > max_info_gain:
          max_split_point, max_split_col, max_info_gain = split_point, col, info_gain
    left_child_index = self.values[:, max_split_col] < max_split_point
    right_child_index = self.values[:, max_split_col] > max_split_point
    self.col_index, self.split_point = max_split_col, max_split_point
    return (DecisionTreeNode(self.values[idx], self.labels[idx], self.classes, self.depth + 1, self.max_depth) for \
      idx in [left_child_index, right_child_index]) 

  def vote_class(self) -> int:
    """Vote the most possible class."""
    labels, label_count = np.unique(self.labels, return_counts=True)
    return labels[np.argmax(label_count)] # ATTENTION
  
  def if_leaf(self) -> bool:
    """Check whether the node is the leaf node."""
    return self.values is None or self.values.size == 0 or np.unique(self.labels).size <=1 #ATTENTION
    
  
  @staticmethod
  def get_info(subset_labels: np.ndarray) -> float:
    """Calculate the info of subset.
    
    Args:
      subset_labels: the labels of the subset

    Return:
      info: the information of the subset
    """
    n = subset_labels.size
    return sum(-x / n * np.log2(x / n) for x in np.unique(subset_labels, return_counts=True)[1]) # ATTENTION

  def __str__(self) -> str: # TODO: all
    """Override string method."""
    if not self.l and not self.r: return 'class: {}'.format(self.label)
    l_str = 'feature_{} < {}'.format(
      self.col_index, self.split_point) if self.l else ''
    l_info = self.add_tab(str(self.l))
    r_str = 'feature_{} > {}'.format(
      self.col_index, self.split_point) if self.r else ''
    r_info = self.add_tab(str(self.r))
    return '\n'.join([l_str, l_info, r_str, r_info])

  @staticmethod
  def add_tab(s: str) -> str: # TODO
    """Add tab to format string."""
    return '\n'.join([('|   ' if i > 0 else '|-> ') + l for i, l in enumerate(s.split('\n'))])

class DecisionTree:
  """Definition of the progress of the decision tree."""

  def __init__(self, max_depth: int =10, verbose: bool = True) -> None:
    """Init tree with max_depth."""
    self.tree = None
    self.max_depth = max_depth
    self.verbose = verbose
    self.last_X, self.last_y = None, None # for pruning

  def fit(self, X: np.ndarray, y: np.ndarray) -> None:
    """Fit the decision tree."""
    assert X.shape[0] == y.shape[0], "X and y should have the same number of samples."
    self.last_X, self.last_y = X, y # ATTENTION: the thought
    classes = np.unique(y)
    self.tree = DecisionTreeNode(X, y, classes=classes, max_depth=self.max_depth)

  def prune(self, X: np.ndarray = None, y: np.ndarray = None) -> None:
    """Prune the decision tree."""
    if X is not None and y is not None and X.size and y.size:
      self.last_X, self.last_y = X, y 
    self.do_prune(self.tree)
  
  def do_prune(self, node: DecisionTreeNode) -> None: # for recurrent call
    """Prune the tree"""
    if node is None or (node.l is None and node.r is None): return
    self.do_prune(node.l), self.do_prune(node.r)
    acc_before_prune = self.get_acc(self.predict(self.last_X), self.last_y)
    save_children = (node.l, node.r)
    node.l, node.r =None, None
    acc_after_prune = self.get_acc(self.predict(self.last_X), self.last_y)
    if acc_after_prune < acc_before_prune:
      node.l, node.r = save_children
    elif self.verbose:
      print('Pruned node: ' + str(save_children)) 

  def predict(self, X: np.ndarray) -> np.ndarray:
    """Predict the result."""
    return np.array([self.predict_one_piece(x) for x in X])

  def predict_one_piece(self, row_data: np.ndarray) -> float: # the tree has already been finished. for testing
    """Predict the class of the specifed data.
    
    Args:
      row_data: vector of to-be-predicted data

    Return:
      labels: predicted label
    """
    node = self.tree
    while node and (node.l or node.r):
      node = node.l if row_data[node.col_index] < node.split_point else node.r
    return node.label if node else -1

  @staticmethod
  def get_acc(y_pred: np.ndarray, y: np.ndarray) -> float:
    """Get accuracy of the given y and y_pred."""
    return np.sum(y_pred == y) / y.shape[0]

  @staticmethod
  def load_data(path: str) -> Tuple[np.ndarray, np.ndarray]: # ATTENTION: a template
    """Load data.
    
    Args:
      path: path of data file

    Returns:
     X: feature of data
     y: label of data
    """
    base_path = os.path.dirname(__file__)
    raw_data = np.loadtxt(os.path.join(base_path, path))
    np.random.shuffle(raw_data)
    return raw_data[:, :-1], raw_data[:, -1]

if __name__ == "__main__":
    np.random.seed(42)
    X_train, y_train = DecisionTree.load_data('./dataset/ex4-traindata.txt')
    X_test, y_test = DecisionTree.load_data('./dataset/ex4-testdata.txt')
    my_tree = DecisionTree()
    my_tree.fit(X_train, y_train)
    my_pred = my_tree.predict(X_test)
    print('\nAcc: {:.2f}'.format(DecisionTree.get_acc(my_pred, y_test)))
    print('\nMy Tree:')  
    print(my_tree.tree)  
    my_tree.prune(X_test, y_test)
    my_pred = my_tree.predict(X_test)
    print('\nAcc: {:.2f}'.format(DecisionTree.get_acc(my_pred, y_test)))
    print('\nMy Tree:')
    print(my_tree.tree)