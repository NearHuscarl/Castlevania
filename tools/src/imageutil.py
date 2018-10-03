"""
Image-related utilities
"""

from PIL import Image, ImageChops


def _get_bbox(image):
    bbox = image.getbbox()
    if bbox is None:
        return 0, 0, 0, 0
    return bbox


def _get_main_image_bbox(image, bg):
    """ get bounding box of image without border https://stackoverflow.com/a/10986041 """
    background = Image.new(image.mode, image.size, bg)
    diff = ImageChops.difference(image, background)
    diff = ImageChops.add(diff, diff, 2.0, -100)
    return _get_bbox(diff)


def have_border(image, border_color):
    """ return True if any sides has border """
    bbox = _get_main_image_bbox(image, border_color)
    return bbox != (0, 0, image.size[0], image.size[1])


def have_all_border(image, border_color, border_thickness=1):  # all sides has border
    """ return True if all sides have border """
    image_bbox = _get_bbox(image)
    main_image_bbox = _get_main_image_bbox(image, border_color)
    return (main_image_bbox[0] == image_bbox[0] + border_thickness and
            main_image_bbox[1] == image_bbox[1] + border_thickness and
            main_image_bbox[2] == image_bbox[2] - border_thickness and
            main_image_bbox[3] == image_bbox[3] - border_thickness)


def have_top_border(image, border_color, border_thickness=1):
    image_bbox = _get_bbox(image)
    main_image_bbox = _get_main_image_bbox(image, border_color)
    return main_image_bbox[1] == image_bbox[1] + border_thickness


def have_bottom_border(image, border_color, border_thickness=1):
    image_bbox = _get_bbox(image)
    main_image_bbox = _get_main_image_bbox(image, border_color)
    return main_image_bbox[3] == image_bbox[3] - border_thickness


def have_left_border(image, border_color, border_thickness=1):
    image_bbox = _get_bbox(image)
    main_image_bbox = _get_main_image_bbox(image, border_color)
    return main_image_bbox[0] == image_bbox[0] + border_thickness


def have_right_border(image, border_color, border_thickness=1):
    image_bbox = _get_bbox(image)
    main_image_bbox = _get_main_image_bbox(image, border_color)
    return main_image_bbox[2] == image_bbox[2] - border_thickness
