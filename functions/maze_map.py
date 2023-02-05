from typing import *
from ._data_frame import *
from ._types import *
from .sensor import SensorData


class MazeMap:
    size_x: int
    size_y: int
    def __init__(self, size_x: int, size_y: int) -> None:
        self.size_x = size_x
        self.size_y = size_y

        row_dir_nodes: List[List[WallObject]] = []
        for y in range(size_y):
            row_dir_nodes.append( [WallObject() for _ in range(size_x-1)] )
        col_dir_nodes: List[List[WallObject]] = []
        for x in range(size_x):
            col_dir_nodes.append( [WallObject() for _ in range(size_y-1)] )

        maze_nodes: List[List[MazeNode]] = []
        for y in range(size_y):
            maze_nodes.append( [] )
            for x in range(size_x):
                east_dir_node = row_dir_nodes[y][x] if x < size_x - 1 else None
                west_dir_node = row_dir_nodes[y][x-1] if x > 0 else None
                south_dir_node = col_dir_nodes[x][y] if y < size_y - 1 else None
                north_dir_node = col_dir_nodes[x][y-1] if y > 0 else None

                maze_nodes[-1].append(
                    MazeNode(
                        east=east_dir_node,
                        west=west_dir_node,
                        south=south_dir_node,
                        north=north_dir_node,
                    )
                )
        self.maze_maps = maze_nodes

    def get(self, current_pos: Position):
        return self.maze_maps[current_pos.y][current_pos.x]

    def update(self, current_pos: Position, current_dir: int, sensor_data: SensorData):
        current_node = self.maze_maps[current_pos.y][current_pos.x]
        if current_dir == EAST:
            if current_node.east is not None:
                current_node.east.update( sensor_data.f_data )
            if current_node.north is not None:
                current_node.north.update( sensor_data.l_data )
            if current_node.south is not None:
                current_node.south.update( sensor_data.r_data )
        elif current_dir == WEST:
            if current_node.west is not None:
                current_node.west.update( sensor_data.f_data )
            if current_node.north is not None:
                current_node.north.update( sensor_data.r_data )
            if current_node.south is not None:
                current_node.south.update( sensor_data.l_data )
        elif current_dir == SOUTH:
            if current_node.east is not None:
                current_node.east.update( sensor_data.l_data )
            if current_node.west is not None:
                current_node.west.update( sensor_data.r_data )
            if current_node.south is not None:
                current_node.south.update( sensor_data.f_data )
        elif current_dir == NORTH:
            if current_node.east is not None:
                current_node.east.update( sensor_data.r_data )
            if current_node.west is not None:
                current_node.west.update( sensor_data.l_data )
            if current_node.north is not None:
                current_node.north.update( sensor_data.f_data )

    def view(self):
        print(self.__repr__())

    def __repr__(self) -> str:
        txt = ""
        for j in range(self.size_y):
            for i in range(self.size_x):
                txt += str(self.maze_maps[j][i])
            txt += '\n'
        return txt