"""
Color helper functions. Copy from https://github.com/dylanaraps/pywal/blob/master/pywal/util.py
"""


def rgb_to_hex(color):
    """ Convert an rgb color to hex """
    return "#%02x%02x%02x" % (*color,)


def hex_to_rgb(color):
    """ Convert a hex color to rgb """
    return tuple(bytes.fromhex(color.strip("#")))
