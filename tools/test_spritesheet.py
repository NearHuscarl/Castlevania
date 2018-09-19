import unittest
import os
from PIL import Image

from spritesheet import (
    have_all_border,
    have_top_border,
    have_bottom_border,
    have_left_border,
    have_right_border,
    have_border
)


class SpritesheetTest(unittest.TestCase):
    _spritesheet_path = os.path.join(os.getcwd(), 'spritesheet.png')

    @classmethod
    def setUpClass(cls):
        img = Image.open(cls._spritesheet_path).convert('RGB')

        cls.image_no_border = img.crop((61, 53, 85, 83))

        cls.image_border_top = img.crop((61, 52, 85, 83))
        cls.image_border_bottom = img.crop((61, 53, 85, 84))
        cls.image_border_left = img.crop((60, 53, 85, 83))
        cls.image_border_right = img.crop((61, 53, 86, 83))
        cls.image_border_all = img.crop((60, 52, 86, 84))

    def test_have_top_border(self):
        """ have_top_border(image) should return True when image have top border """
        self.assertEqual(have_top_border(self.image_no_border), False)
        self.assertEqual(have_top_border(self.image_border_top), True)
        self.assertEqual(have_top_border(self.image_border_bottom), False)
        self.assertEqual(have_top_border(self.image_border_left), False)
        self.assertEqual(have_top_border(self.image_border_right), False)

    def test_have_bottom_border(self):
        """ have_bottom_border(image) should return True when image have bottom border """
        self.assertEqual(have_bottom_border(self.image_no_border), False)
        self.assertEqual(have_bottom_border(self.image_border_top), False)
        self.assertEqual(have_bottom_border(self.image_border_bottom), True)
        self.assertEqual(have_bottom_border(self.image_border_left), False)
        self.assertEqual(have_bottom_border(self.image_border_right), False)

    def test_have_left_border(self):
        """ have_left_border(image) should return True when image have left border """
        self.assertEqual(have_left_border(self.image_no_border), False)
        self.assertEqual(have_left_border(self.image_border_top), False)
        self.assertEqual(have_left_border(self.image_border_bottom), False)
        self.assertEqual(have_left_border(self.image_border_left), True)
        self.assertEqual(have_left_border(self.image_border_right), False)

    def test_have_right_border(self):
        """ have_right_border(image) should return True when image have right border """
        self.assertEqual(have_right_border(self.image_no_border), False)
        self.assertEqual(have_right_border(self.image_border_top), False)
        self.assertEqual(have_right_border(self.image_border_bottom), False)
        self.assertEqual(have_right_border(self.image_border_left), False)
        self.assertEqual(have_right_border(self.image_border_right), True)

    def test_have_border(self):
        """ have_border(image) should return True when image have any borders """
        self.assertEqual(have_border(self.image_no_border), False)
        self.assertEqual(have_border(self.image_border_top), True)
        self.assertEqual(have_border(self.image_border_bottom), True)
        self.assertEqual(have_border(self.image_border_left), True)
        self.assertEqual(have_border(self.image_border_right), True)

    def test_have_all_border(self):
        """ have_all_border(image) should return True when image have all 4 borders """
        self.assertEqual(have_all_border(self.image_no_border), False)
        self.assertEqual(have_all_border(self.image_border_top), False)
        self.assertEqual(have_all_border(self.image_border_bottom), False)
        self.assertEqual(have_all_border(self.image_border_left), False)
        self.assertEqual(have_all_border(self.image_border_right), False)
        self.assertEqual(have_all_border(self.image_border_all), True)


if __name__ == '__main__':
    unittest.main()
