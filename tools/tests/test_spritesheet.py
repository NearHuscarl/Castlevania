import pytest
import os
from PIL import Image

from imageutil import (
    have_all_border,
    have_top_border,
    have_bottom_border,
    have_left_border,
    have_right_border,
    have_border,
)


@pytest.fixture(scope='module')
def images():
    """ a dictionary where keys are border types and values are corresponding images of that type """
    _image_path = os.path.join(os.getcwd(), 'images')
    return dict(no_border=Image.open(os.path.join(_image_path, 'image_no_border.png')),
                border_all=Image.open(os.path.join(_image_path, 'image_border_all.png')),
                border_top=Image.open(os.path.join(_image_path, 'image_border_top.png')),
                border_bottom=Image.open(os.path.join(_image_path, 'image_border_bottom.png')),
                border_left=Image.open(os.path.join(_image_path, 'image_border_left.png')),
                border_right=Image.open(os.path.join(_image_path, 'image_border_right.png')))


@pytest.fixture(scope='module')
def border_color(images):
    """ color of border to detect """
    return images['border_all'].getpixel((0, 0))


def test_have_top_border(images, border_color):
    """ have_top_border(image) should return True when image have top border """
    assert have_top_border(images['no_border'], border_color) is False
    assert have_top_border(images['border_all'], border_color) is True
    assert have_top_border(images['border_top'], border_color) is True
    assert have_top_border(images['border_bottom'], border_color) is False
    assert have_top_border(images['border_left'], border_color) is False
    assert have_top_border(images['border_right'], border_color) is False


def test_have_bottom_border(images, border_color):
    """ have_bottom_border(image) should return True when image have bottom border """
    assert have_bottom_border(images['no_border'], border_color) is False
    assert have_bottom_border(images['border_all'], border_color) is True
    assert have_bottom_border(images['border_top'], border_color) is False
    assert have_bottom_border(images['border_bottom'], border_color) is True
    assert have_bottom_border(images['border_left'], border_color) is False
    assert have_bottom_border(images['border_right'], border_color) is False


def test_have_left_border(images, border_color):
    """ have_left_border(image) should return True when image have left border """
    assert have_left_border(images['no_border'], border_color) is False
    assert have_left_border(images['border_all'], border_color) is True
    assert have_left_border(images['border_top'], border_color) is False
    assert have_left_border(images['border_bottom'], border_color) is False
    assert have_left_border(images['border_left'], border_color) is True
    assert have_left_border(images['border_right'], border_color) is False


def test_have_right_border(images, border_color):
    """ have_right_border(image) should return True when image have right border """
    assert have_right_border(images['no_border'], border_color) is False
    assert have_right_border(images['border_all'], border_color) is True
    assert have_right_border(images['border_top'], border_color) is False
    assert have_right_border(images['border_bottom'], border_color) is False
    assert have_right_border(images['border_left'], border_color) is False
    assert have_right_border(images['border_right'], border_color) is True


def test_have_border(images, border_color):
    """ have_border(image) should return True when image have any borders """
    assert have_border(images['no_border'], border_color) is False
    assert have_border(images['border_all'], border_color) is True
    assert have_border(images['border_top'], border_color) is True
    assert have_border(images['border_bottom'], border_color) is True
    assert have_border(images['border_left'], border_color) is True
    assert have_border(images['border_right'], border_color) is True


def test_have_all_border(images, border_color):
    """ have_all_border(image) should return True when image have all 4 borders """
    assert have_all_border(images['no_border'], border_color) is False
    assert have_all_border(images['border_all'], border_color) is True
    assert have_all_border(images['border_top'], border_color) is False
    assert have_all_border(images['border_bottom'], border_color) is False
    assert have_all_border(images['border_left'], border_color) is False
    assert have_all_border(images['border_right'], border_color) is False
