# r1_rover_gps_lidar

1. Gazebo:
```sh
cd <workspace>/src/PX4-gazebo-models
```
```sh
python3 simulation-gazebo --world urjc_trains
```

2. Rover:
```sh
cd <workspace>/src/PX4-Autopilot
```
```sh
PX4_GZ_STANDALONE=1 PX4_GZ_WORLD=urjc_trains_world make px4_sitl gz_rover_lidar_r1
```

3. Mavros:
```sh
ros2 launch mavros px4.launch fcu_url:=udp://:14540@14557
```

4. Launchers:
```sh
ros2 launch r1_rover_launcher r1_rover_lidar.launch.py
```
```sh
ros2 launch r1_rover_launcher r1_rover_easynav.launch.py
```

5. Patrolling:
```sh
ros2 run easynav_patrolling_behavior patrolling_main --ros-args --params-file ~/<workspace>/src/r1_rover_gps_lidar/r1_rover_launcher/config/r1_patrolling_params.yaml
```

