# Modified from https://github.com/arimb/PurePursuit/blob/master/PathGenerator.py
# Generates waypoints and path for a robot given points.

# import cv2
import configparser
import math
import sys
import matplotlib.pyplot as plt
import os
from pdb import set_trace

# READ CONFIG FILE
config = configparser.ConfigParser()
config.read("config.ini")
input_path = config["PATH"]["INPUT_FILE_LOCATION"]
#set_trace()
files = [f for f in os.listdir(input_path) ]
#set_trace()

for file in files:
    input_file = os.path.join(input_path, file)
    waypoints = []
    with open(input_file) as f:
        lines = f.readlines()
        for line in lines:
            values = line.rstrip().split(",")
            values2 = [float(x) for x in values[:2]]
            direction = values[2]
            waypoints.append(values2)

    # INITIALIZE WAYPOINTS

    # MAKE SURE AT LEAST 2 POINTS SELECTED
    if len(waypoints) < 2:
        continue

    # CONVERT PIXELS TO INCHES, CALCULATE WAYPOINT DISTANCE, INJECT MID-WAYPOINTS
    total_waypoints = []
    for i in range(len(waypoints) - 1):
        dist = math.sqrt((waypoints[i + 1][0] - waypoints[i][0]) ** 2 + (waypoints[i + 1][1] - waypoints[i][1]) ** 2)
        j = 0
        while j < dist:
            total_waypoints.append(tuple(a + j / dist * (b - a) for a, b in zip(waypoints[i], waypoints[i + 1])))
            j += float(config["POINT_INJECTION"]["POINT_DIST"])
        # set_trace()
    total_waypoints.append(waypoints[-1])

    # SMOOTH WAYPOINTS - W[0]=X, W[1]=Y
    smooth_waypoints = [[w[0], w[1]] for w in total_waypoints]
    weight_data = float(config["POINT_INJECTION"]["WEIGHT_DATA"])
    weight_smooth = float(config["POINT_INJECTION"]["WEIGHT_SMOOTH"])
    tolerance = float(config["POINT_INJECTION"]["TOLERANCE"])
    change = tolerance
    while change >= tolerance:
        change = 0
        for i in range(1, len(total_waypoints) - 1):
            for j in range(len(total_waypoints[i])):
                aux = smooth_waypoints[i][j]
                smooth_waypoints[i][j] += weight_data * (total_waypoints[i][j] - smooth_waypoints[i][j]) + \
                                          weight_smooth * (smooth_waypoints[i - 1][j] + smooth_waypoints[i + 1][j] - 2 *
                                                           smooth_waypoints[i][j])
                change += abs(aux - smooth_waypoints[i][j])
            # set_trace()

    # CALCULATE PATH DISTANCE - W[2]
    smooth_waypoints[0].append(0)
    for i, w in enumerate(smooth_waypoints[1:], start=1):
        w.append(smooth_waypoints[i - 1][2] + math.sqrt(
            (w[0] - smooth_waypoints[i - 1][0]) ** 2 + (w[1] - smooth_waypoints[i - 1][1]) ** 2))

    # CALCULATE CURVATURE - W[3]
    smooth_waypoints[0].append(0.0001)
    smooth_waypoints[-1].append(0.0001)
    for i, w in enumerate(smooth_waypoints[1:-1], start=1):
        w[0] += 0.0001
        w[1] += 0.0001
        k1 = .5 * (w[0] ** 2 + w[1] ** 2 - smooth_waypoints[i - 1][0] ** 2 - smooth_waypoints[i - 1][1] ** 2) / (
                w[0] - smooth_waypoints[i - 1][0])
        k2 = (w[1] - smooth_waypoints[i - 1][1]) / (w[0] - smooth_waypoints[i - 1][0])
        b = .5 * (smooth_waypoints[i - 1][0] ** 2 - 2 * smooth_waypoints[i - 1][0] * k1 + smooth_waypoints[i - 1][1] ** 2 -
                  smooth_waypoints[i + 1][0] ** 2 + 2 * smooth_waypoints[i + 1][0] * k1 - smooth_waypoints[i + 1][
                      1] ** 2) / (
                    smooth_waypoints[i + 1][0] * k2 - smooth_waypoints[i + 1][1] + smooth_waypoints[i - 1][1] -
                    smooth_waypoints[i - 1][0] * k2)
        a = k1 - k2 * b
        r = math.sqrt((w[0] - a) ** 2 + (w[1] - b) ** 2)
        w.append(1 / r)

    # CALCULATE DESIRED VELOCITY - W[4]
    for w in smooth_waypoints:
        w.append(min(float(config["VELOCITY"]["MAX_VEL"]), float(config["VELOCITY"]["TURNING_CONST"]) / w[3]))
    # set_trace()

    # ADD ACCELERATION LIMITS - W[5]
    smooth_waypoints[-1].append(0)
    for i, w in enumerate(reversed(smooth_waypoints[:-1]), start=1):
        w.append(min(w[4], math.sqrt(smooth_waypoints[-i][5] ** 2 + 2 * float(config["VELOCITY"]["MAX_ACCEL"]) * \
                                     math.sqrt(
                                         (w[0] - smooth_waypoints[-i][0]) ** 2 + (w[1] - smooth_waypoints[-i][1]) ** 2))))

    smooth_waypoints[0][5] = float(config["VELOCITY"]["STARTING_VEL"])
    for i, w in enumerate(smooth_waypoints[1:], start=1):
        test = math.sqrt(smooth_waypoints[i - 1][5] ** 2 + 2 * float(config["VELOCITY"]["MAX_ACCEL"]) * \
                         math.sqrt((w[0] - smooth_waypoints[i - 1][0]) ** 2 + (w[1] - smooth_waypoints[i - 1][1]) ** 2))
        print(test)
        if test < w[5]:
            w[5] = test
        else:
            break

    # WRITE RESULTS TO FILE
    output_file = os.path.join(config["PATH"]["OUTPUT_FILE_LOCATION"], "gen_" + file)
    with open(output_file, "w+") as of:
        for w in smooth_waypoints:
            of.write(str(w[0]) + "," + str(w[1]) + "," + str(w[5]) + "," + direction + "\n")

    # GRAPH WAYPOINTS
    xvals = []
    yvals = []
    for w in smooth_waypoints:
        xvals.append(w[0])
        yvals.append(w[1])
    # xvals.append(0)
    # yvals.append(28.5)
    plt.plot(xvals, yvals)
    plt.axis("equal")
    plt.show()