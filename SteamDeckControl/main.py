from pyjoystick.sdl2 import Key, Joystick, run_event_loop
import protocol
import datetime
import sys
import json
import socket

# configs
port = 1
# how many times per second to send data, set this to throttle frequency to optimize latency.
# without this the controller will send data in 500+ fps on my machine, congesting the network.
fps = 200

# globals
state = protocol.State()
last_send_timestamp = 0
interval = 1 / fps

UDP_IP = "192.168.0.161"
UDP_PORT = 4000
up = False
down = False
left = False
right = False


def run(fl, fr, br, bl):
    global UDP_IP, UDP_PORT
    MESSAGE = bytes(json.dumps({"fr": fr, "fl": fl, "br": br, "bl": bl}), "ascii")
    print(MESSAGE)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

# [f, s] => [fl, fr, br, bl]

# [ 0, 0]   => [ 0,  0,  0,  0]
# [ 1, 0]   => [ 1,  1,  1,  1]
# [ 1, 1]   => [ 1,  0,  1,  0]
# [ 0, 1]   => [ 1, -1,  1, -1]
# [ 1,-1]   => [ 0,  1,  0,  1]
# [-1, 0]   => [-1, -1, -1, -1]
# [-1, 1]   => [ 0, -1,  0, -1]
# [-1,-1]   => [-1,  0, -1,  0]
# [ 0,-1]   => [-1,  0, -1,  0]
# [ 0, 1]   => [-1,  1, -1,  1]

def mecanum(vec):
    f = vec[0]
    s = vec[1]
    fl = f + s
    fr = f - s
    br = f + s
    bl = f - s
    return [fl, fr, br, bl]

def normal(vec):
    f = -vec[0]
    s = vec[1]
    if f < 0.1 and f > -0.1 and s < 0.1 and s > -0.1:
        return [0, 0, 0, 0]
    r = f + s
    l = f - s
    r = max(min(r, 1), -1)
    l = max(min(l, 1), -1)
    return [l, r, r, l]

# [-1, 1] => [0, 255]
def norm(val):
    return min(1,max(-1, val)) * 255

def go():
    global up, down, left, right
    forward = state.left_joystick_y
    sideways = state.left_joystick_x
    vec = [forward, sideways]
    vec = normal(vec)
    vec = list(map(norm, vec))
    run(vec[0], vec[1], vec[2], vec[3])

def print_add(joy):
  print('Added', joy)


def print_remove(joy):
  print('Removed', joy)


def key_received(key: Key):
  if key.keytype == Key.KeyTypes.BUTTON:
    # print(key)
    if key.number == 0:
      state.button_A = key.value
    elif key.number == 1:
      state.button_B = key.value
    elif key.number == 2:
      state.button_X = key.value
    elif key.number == 3:
      state.button_Y = key.value
    elif key.number == 4:
      state.button_L_SHOULDER = key.value
    elif key.number == 5:
      state.button_R_SHOULDER = key.value
    elif key.number == 6:
      state.button_BACK = key.value
    elif key.number == 7:
      state.button_START = key.value
    # elif key.number == 8: # no this button on steam deck
    #   pass
    elif key.number == 9:
      state.button_L_THUMB = key.value
    elif key.number == 10:
      state.button_R_THUMB = key.value
  elif key.keytype == Key.KeyTypes.AXIS:
    if key.number == 0:
      state.left_joystick_x = key.value  # [-1, 1]
    elif key.number == 1:
      state.left_joystick_y = key.value  # reverse axis-Y value
    elif key.number == 2:
      state.left_trigger = int(key.value * 255)  # [0, 1] => [0, 255]
    elif key.number == 3:
      state.right_joystick_x = int(
          (key.value + 1) / 2 * 65535)  # [-1, 1] => [0, 65535]
    elif key.number == 4:
      state.right_joystick_y = int(
          (-key.value + 1) / 2 * 65535)  # reverse axis-Y value
    elif key.number == 5:
      state.right_trigger = int(key.value * 255)  # [0, 1] => [0, 255]
  elif key.keytype == Key.KeyTypes.HAT:
    state.button_DPAD = key.value

  # send data if enough time has passed
  global last_send_timestamp
  if datetime.datetime.now().timestamp() - last_send_timestamp > interval:
    go()
    last_send_timestamp = datetime.datetime.now().timestamp()


def main(args):
    try:
      run_event_loop(print_add, print_remove, key_received)
    except KeyboardInterrupt:
      # gracefully exit on ctrl-c
      pass

def parse_args():
    import argparse

    parser = argparse.ArgumentParser(description="Keyboard control for the robot")
    parser.add_argument("ip", type=str, help="IP address of the robot")
    parser.add_argument("--port", type=int, default=4000, help="Port of the robot")
    args = parser.parse_args()
    return args

if __name__ == "__main__":
    args = parse_args()
    UDP_IP = args.ip
    UDP_PORT = args.port
    main(args)
