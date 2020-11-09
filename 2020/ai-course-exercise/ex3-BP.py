"""AIcourse ex3 BP problem"""
from __future__ import annotations
from operator import ge
from os import get_exec_path
from typing import Tuple
import os

import numpy as np


NNGradType = Tuple[np.array, np.array, np.array, np.array]

class LinearNeuralNetwork():
  """Define structure of linear neural network."""

  def __init__(self, input_dim: int, output_dim: int, hidden_units: int, batch_size: int, seed: int = 42) -> None:
    """Init layer with D_i, D_o, H, B, Y = Sigmoid(W_2 * (W_1 * x + b_1) + b2)

    Args:
      input_dim: input dimension
      output_dim: output dimension
      hidden_units: the number of units in hidden layer
      batch_size: batch size
      seed: random seed
    """
    np.random.seed(seed)
    self.input_dim = input_dim
    self.output_dim = output_dim
    self.hidden_units = hidden_units
    self.batch_size = batch_size
    
    self.w_1 = self.init_params((input_dim, hidden_units))
    self.b_1 = self.init_params((hidden_units))
    self.w_2 = self.init_params((hidden_units, output_dim))
    self.b_2 = self.init_params((output_dim))

  def forward(self, x: np.array) -> np.array:
    """Forward propagation."""
    assert x.shape[1] == self.input_dim, \
      "Incorrect input dimension {}, which should be {}.".format(x.shape[1], self.input_dim)
    y_pred = (x @ self.w_1 + self.b_1) @ self.w_2 + self.b_2
    return 1 / (1 + np.exp(-y_pred)) # predict with sigmoid

  def backward(self, x: np.array, y_target: np.array) -> Tuple[np.float, NNGradType]:
    """Backward propagation."""
    h = x @ self.w_1 + self.b_1 # shape: n * hidden_units
    y = h @ self.w_2 + self.b_2 # shape: n * out_dim
    sig_y = 1 / (1 + np.exp(-y)) # shape: n * out_dim

    loss = np.square(sig_y - y_target).sum() # shape: 1

    grad_sig_y = 2 * (sig_y - y_target) # shape: n * out_dim
    grad_y = y * (1 - y) * grad_sig_y # shape: n * out_dim
    grad_w_2 = h.T @ grad_y # shape: hidden_units * out_dim
    grad_b_2 = np.ones(self.batch_size) @ grad_y # shape: 1 * out_dim
    grad_h = grad_y @ self.w_2.T # shape: n * hidden_units
    grad_w_1 = x.T @ grad_h # shape: input_dim * hidden_units
    grad_b_1 = np.ones(self.batch_size) @ grad_h # shape: 1 * hidden_units
    
    return loss, (grad_w_2, grad_b_2, grad_w_1, grad_b_1)

  def optimize_params(self, grads: NNGradType, lr: float = 0.99):
    """Optimize the parameters of the network."""
    for param_name, grad in zip(['w_2', 'b_2', 'w_1', 'b_1'], grads):
      param = getattr(self, param_name)
      setattr(self, param_name, param - lr * grad)

  def __call__(self, **kwargs):
    """Override callable behavior."""
    return self.forward(**kwargs)

  def init_params(self, shape: Tuple[int, ...]) -> np.array:
    """Init parameters with kaiming init. std = gain / sqrt(fan_mode)."""
    fan_in = shape[0]
    gain = 1
    return np.random.normal(0, gain / np.sqrt(fan_in))
    

class Trainer():
  """Trainer for NN."""
  pass

class DataLoader():
  """Iris Dataloader."""
  pass