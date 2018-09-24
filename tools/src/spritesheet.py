import os
from PIL import Image
from imageutil import (
    have_all_border,
    have_top_border,
    have_bottom_border,
    have_left_border,
    have_right_border,
)

debugging: bool = False


def get_sprite_bbox(coord, spritesheet, border_color, border_thickness=1):
    """ Return boundary box of the sprite at <coord> in <spritesheet> with <border_color> is transparent color """
    x, y = coord
    selected_pixel = spritesheet.getpixel((x, y))

    if selected_pixel == border_color:
        return None

    # get boundary box surrounding selected pixel
    left = x - 1
    top = y - 1
    right = x + 2
    bottom = y + 2

    sprite = spritesheet.crop((left, top, right, bottom))

    while not have_all_border(sprite, border_color, border_thickness):

        if left <= 0 or top <= 0 or right >= spritesheet.width or bottom >= spritesheet.height:
            return None

        while not have_top_border(sprite, border_color, border_thickness) and top > 0:
            top -= 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_bottom_border(sprite, border_color, border_thickness) and bottom < spritesheet.height:
            bottom += 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_left_border(sprite, border_color, border_thickness) and left > 0:
            left -= 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_right_border(sprite, border_color, border_thickness) and right < spritesheet.width:
            right += 1
            sprite = spritesheet.crop((left, top, right, bottom))

    if debugging:
        print('left:', left)
        print('top:', top)
        print('right:', right)
        print('bottom:', bottom, '\n')
        # sprite.show()

    return left, top, right, bottom


def main():
    spritesheet_path = os.path.join(os.getcwd(), 'images', 'spritesheet.png')
    spritesheet = Image.open(spritesheet_path).convert('RGB')
    border_color = spritesheet.getpixel((0, 0))

    get_sprite_bbox((347, 469), spritesheet, border_color)
    get_sprite_bbox((174, 31), spritesheet, border_color)
    get_sprite_bbox((169, 64), spritesheet, border_color)
    get_sprite_bbox((175, 266), spritesheet, border_color)


if __name__ == '__main__':
    debugging = True
    main()
