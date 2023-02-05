from functions.maze_map import MazeMap
from functions.sensor import SensorData
from functions import Position


if __name__ == '__main__':
    maze_map = MazeMap(5, 8)

    sensor_data = SensorData([0, 0, 1])
    current_pos = Position(0, 7)
    current_dir = 0


    maze_map.update(current_pos, current_dir, sensor_data)
    cross_nodes = maze_map.get(current_pos)

    maze_map.view()


