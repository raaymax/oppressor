import json
import socket

from pynput import keyboard
from pynput.keyboard import Listener as KeyboardListener

UDP_IP = "192.168.0.161"
UDP_PORT = 4000
up = False
down = False
left = False
right = False


def run(fr, fl, br, bl):
    global UDP_IP, UDP_PORT
    MESSAGE = bytes(json.dumps({"fr": fr, "fl": fl, "br": br, "bl": bl}), "ascii")
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))


def go():
    forward = state.

    r = 0
    l = 0
    if up:
        r += 255
        l += 255
    if down:
        r += -255
        l += -255
    if right:
        r += -255
        l += 255
    if left:
        r += 255
        l += -255
    r = max(min(r, 255), -255)
    l = max(min(l, 255), -255)
    run(l, r, l, r)


def on_release(key):
    global up, down, left, right
    if key == keyboard.Key.up:
        up = False
    if key == keyboard.Key.down:
        down = False
    if key == keyboard.Key.right:
        right = False
    if key == keyboard.Key.left:
        left = False
    go()


def on_press(key):
    global up, down, left, right
    if key == keyboard.Key.up:
        up = True
    if key == keyboard.Key.down:
        down = True
    if key == keyboard.Key.right:
        right = True
    if key == keyboard.Key.left:
        left = True
    go()


def parse_args():
    import argparse

    parser = argparse.ArgumentParser(description="Keyboard control for the robot")
    parser.add_argument("ip", type=str, help="IP address of the robot")
    parser.add_argument("--port", type=int, default=4000, help="Port of the robot")
    args = parser.parse_args()
    return args


def main(args):
    with KeyboardListener(on_press=on_press, on_release=on_release) as listener:
        listener.join()


if __name__ == "__main__":
    args = parse_args()
    UDP_IP = args.ip
    UDP_PORT = args.port
    main(args)
