from enum import Enum
import numpy as np

Status = Enum("Status", "None, Wall, Active, Fix")

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

def go():
