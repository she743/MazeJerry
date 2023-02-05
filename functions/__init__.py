from typing import *

from .maze_map import MazeMap
from ._data_frame import Position, MazeNode
from ._types import *
from .sensor import Sensor, SensorData
from .motor import Motor


class JerryRobot:
    def __init__(
        self,
        current_dir: int,
        start_pos: Position,
        target_pos: Position,
        map_size_x: int,
        map_size_y: int,
        ir_sensor_pins: List[int],
        tcrt_sensor_pins: List[int],
        motor_pins: List[int],
    ) -> None:
        self.current_dir = current_dir
        self.current_pos = start_pos
        self.start_pos = start_pos
        self.target_pos = target_pos
        
        self.maps = MazeMap(size_x=map_size_x, size_y=map_size_y)

        self.ir_sensors = Sensor( ir_sensor_pins )
        self.tcrt_sensors = Sensor( tcrt_sensor_pins )
        self.motors = Motor( motor_pins )

    def run(self):
        '''
            Running cycle
                >>> Sensing()       // Get IR sensor data
                >>> Update_map()    // Update maze map with collected IR sensor data,
                                    // Return 'MazeNode' used when searching for a path.
                >>> Search_path()   // Search a path using 'AStar' algorithm.
                                    // Return Next step.
                >>> Move()          // Move Jerry Robot to the next step.
        '''
        while (self.current_pos != self.target_pos):
            ir_sensor_data = self.ir_sensing()
            cross_nodes = self.update_map( ir_sensor_data )
            self.search_path( cross_nodes )
            self.move()

    def ir_sensing(self) -> SensorData:
        return self.ir_sensors.get()

    def update_map(self, sensor_data: SensorData) -> MazeNode:
        self.maps.update(
            self.current_pos,
            self.current_pos,
            sensor_data
        )
        return self.maps.get(self.current_pos)

    def search_path(self, cross_nodes: MazeNode):
        ...

    def move(self):
        ...


__all__ = [
    MazeMap,
    JerryRobot,
    Position
]