from enum import Enum
import numpy as np
import random

Status = Enum("Status", "None, Wall, Active, Fix")
enable_actions = (0, 1, 2, 3)
count = 7

blockPattern = [
    np.array([[1, 1, 0], [1, 1, 0], [0, 0, 0]]),
    np.array([[0, 1, 0], [0, 1, 0], [0, 1, 0]]),
    np.array([[0, 1, 0], [1, 1, 0], [1, 0, 0]]),
    np.array([[1, 0, 0], [1, 1, 0], [0, 1, 0]]),
    np.array([[0, 1, 0], [1, 1, 1], [0, 0, 0]]),
    np.array([[1, 0, 0], [1, 1, 1], [0, 0, 0]]),
    np.array([[0, 0, 1], [1, 1, 1], [0, 0, 0]])
]

def collisionBottomWall(y, field, pattern):
    flag = False

    for i in range(3):
        if np.sum(pattern, axis=1)[i] != 0 and field[1][y + i] == Status.Wall:
            flag = True
    
    return flag

def collisionBottomBlock(x, y, field, pattern):
    flag = False

    for i in range(3):
        for j in range(3):
            if pattern[i][j] != 0 and field[x + i][y + j] == Status.Fix:
                flag = True
    
    return flag

def collisionSideWall(x, field, pattern):
    lflag = False
    rflag = False

    for i in range(3):
        if np.sum(pattern, axis=0)[i] != 0 and field[x + i][0] == Status.Wall:
            flag = True
    
    return flag

def rotate(pattern):
    newpat = []
    
    for i in range(3):
        newpat.append(pattern[:, i][::-1])
    
    return np.array(newpat)
   


class Tetris:
    def __init__(self):
        self.screen_n_rows = 15
        self.screen_n_cols = 10
        self.enable_actions = (0, 1, 2, 3)
        self.frame_rate = 5

        self.reset()

    def update(self, action):
        if action == self.enable_actions[1]:
            # move left
            if collisionSideWall(self.bx - 1, self.field, self.pattern) == 0 and collisionBottomBlock(self.bx - 1, self.by, self.field, self.pattern) == 0:
                self.bx -= 1
        elif action == self.enable_actions[2]:
            # move right
            if collisionSideWall(self.bx + 1, self.field, self.pattern) == 0 and collisionBottomBlock(self.bx + 1, self.by, self.field, self.pattern) == 0:
                self.bx += 1
        elif action == self.enable_actions[3]:
            # rotate
            if collisionSideWall(self.bx, self.field, rotate(self.pattern)) == 0 and collisionBottomBlock(self.bx + 1, self.by, self.field, rotate(self.pattern)) == 0:
                self.pattern = rotate(self.pattern)
        else:
            # do nothing
            pass

        if collisionBottomWall(self.by + 1, self.field, self.pattern) == 0 and collisionBottomBlock(self.bx, self.by + 1, self.field, self.pattern) == 0:
            self.by += 1
        else:
            # overwrite
            for i in range(3):
                for j in range(3):
                    if pattern[i][j] != 0:
                        field[x + i][y + j] = Status.Fix


    def reset(self):
        