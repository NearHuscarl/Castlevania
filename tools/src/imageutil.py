"""
Image-related utilities
"""

from PIL import Image, ImageChops


def _get_saturated_bbox(image, bg):
    """ https://stackoverflow.com/a/10986041 """
    background = Image.new(image.mode, image.size, bg)
    diff = ImageChops.difference(image, background)
    diff = ImageChops.add(diff, diff, 2.0, -100)
    bbox = diff.getbbox()

    if bbox is None:
        return 0, 0, 0, 0

    return bbox


def have_border(image, border_color):
    """ return True if any side has border """
    bbox = _get_saturated_bbox(image, border_color)
    return bbox != (0, 0, image.size[0], image.size[1])


def have_all_border(image, border_color):  # all sides has border
    """ return True if all sides have border """
    bbox = _get_saturated_bbox(image, border_color)
    return all((bbox[0], bbox[1], (bbox[0] + bbox[2]) <= image.size[0],
                (bbox[1] + bbox[3]) <= image.size[1]))


def have_top_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = _get_saturated_bbox(image, border_color)
    return saturated_bbox[1] > image_bbox[1]


def have_bottom_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = _get_saturated_bbox(image, border_color)
    return saturated_bbox[3] < image_bbox[3]


def have_left_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = _get_saturated_bbox(image, border_color)
    return saturated_bbox[0] > image_bbox[0]


def have_right_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = _get_saturated_bbox(image, border_color)
    return saturated_bbox[2] < image_bbox[2]
