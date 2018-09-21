import os
from PIL import Image, ImageChops

debugging: bool = False


def get_saturated_bbox(image, bg):
    background = Image.new(image.mode, image.size, bg)
    diff = ImageChops.difference(image, background)
    diff = ImageChops.add(diff, diff, 2.0, -100)
    bbox = diff.getbbox()

    if bbox is None:
        return 0, 0, 0, 0

    return bbox


def have_border(image, border_color):
    """ return True if any side has border """
    bbox = get_saturated_bbox(image, border_color)
    return bbox != (0, 0, image.size[0], image.size[1])


def have_all_border(image, border_color):  # all sides has border
    """ return True if all sides have border """
    bbox = get_saturated_bbox(image, border_color)
    return all((bbox[0], bbox[1], (bbox[0] + bbox[2]) <= image.size[0],
                (bbox[1] + bbox[3]) <= image.size[1]))


def have_top_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image, border_color)
    return saturated_bbox[1] > image_bbox[1]


def have_bottom_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image, border_color)
    return saturated_bbox[3] < image_bbox[3]


def have_left_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image, border_color)
    return saturated_bbox[0] > image_bbox[0]


def have_right_border(image, border_color):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image, border_color)
    return saturated_bbox[2] < image_bbox[2]


def get_sprite_bbox(coord, spritesheet, border_color):
    x, y = coord

    left = x - 1
    top = y - 1
    right = x + 2
    bottom = y + 2

    selected_pixel = spritesheet.getpixel((x, y))

    if selected_pixel == border_color:
        return None

    sprite = spritesheet.crop((left, top, right, bottom))

    while not have_all_border(sprite, border_color):

        while not have_top_border(sprite, border_color):
            top -= 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_bottom_border(sprite, border_color):
            bottom += 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_left_border(sprite, border_color):
            left -= 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_right_border(sprite, border_color):
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
    spritesheet_path = os.path.join(os.getcwd(), 'spritesheet.png')
    spritesheet = Image.open(spritesheet_path).convert('RGB')
    border_color = spritesheet.getpixel((0, 0))

    get_sprite_bbox((347, 469), spritesheet, border_color)
    get_sprite_bbox((174, 31), spritesheet, border_color)
    get_sprite_bbox((169, 64), spritesheet, border_color)
    get_sprite_bbox((175, 266), spritesheet, border_color)


if __name__ == '__main__':
    debugging = True
    main()
