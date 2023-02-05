from typing import *
from ._types import WALL, NOWALL, UNDEFINE


class Position:
    x: int
    y: int
    def __init__(self, x: int, y: int) -> None:
        self.x = x
        self.y = y

    def __repr__(self) -> str:
        return f"({self.x}, {self.y})"


class WallObject:
    wall: int
    def __init__(self) -> None:
        self.wall = UNDEFINE

    def update(self, sensor_data: int):
        if sensor_data == 1:
            self.wall = WALL
        elif sensor_data == 0:
            self.wall = NOWALL


class MazeNode:
    east: WallObject
    west: WallObject
    south: WallObject
    north: WallObject
    def __init__(self, east: WallObject, west: WallObject, south: WallObject, north: WallObject) -> None:
        self.east = east
        self.west = west
        self.south = south
        self.north = north

    def __repr__(self) -> str:
        txt = "|"
        if self.west is not None:
            if self.west.wall == NOWALL:
                txt += "←"
            elif self.west.wall == UNDEFINE:
                txt += "?"
            else:
                txt += " "
        else:
            txt += " "

        if self.south is not None:
            if self.south.wall == NOWALL:
                txt += "↓"
            elif self.south.wall == UNDEFINE:
                txt += "?"
            else:
                txt += " "
        else:
            txt += " "

        if self.north is not None:
            if self.north.wall == NOWALL:
                txt += "↑"
            elif self.north.wall == UNDEFINE:
                txt += "?"
            else:
                txt += " "
        else:
            txt += " "

        if self.east is not None:
            if self.east.wall == NOWALL:
                txt += "→"
            elif self.east.wall == UNDEFINE:
                txt += "?"
            else:
                txt += " "
        else:
            txt += " "
        txt += "|"
        return txt

