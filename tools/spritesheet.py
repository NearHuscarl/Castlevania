import os

from PIL import Image, ImageChops

SPRITESHEET_PATH = os.path.join(os.getcwd(), 'spritesheet.png')


def get_saturated_bbox(image):
    background = Image.new(image.mode, image.size, image.getpixel((0, 0)))
    diff = ImageChops.difference(image, background)
    diff = ImageChops.add(diff, diff, 2.0, -100)
    bbox = diff.getbbox()
    return bbox


def have_border(image):
    """ return True if any side has border """
    bbox = get_saturated_bbox(image)
    return bbox != (0, 0, image.size[0], image.size[1])


def have_all_border(image):  # all sides has border
    """ return True if all sides have border """
    bbox = get_saturated_bbox(image)
    return all((bbox[0], bbox[1], (bbox[0] + bbox[2]) <= image.size[0],
                (bbox[1] + bbox[3]) <= image.size[1]))


def have_top_border(image):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image)
    return saturated_bbox[1] > image_bbox[1]


def have_bottom_border(image):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image)
    return saturated_bbox[3] < image_bbox[3]


def have_left_border(image):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image)
    return saturated_bbox[0] > image_bbox[0]


def have_right_border(image):
    image_bbox = image.getbbox()
    saturated_bbox = get_saturated_bbox(image)
    return saturated_bbox[2] < image_bbox[2]


def get_spritesheet_coordinate(column, row):
    left = column - 1
    top = row - 1
    right = column + 2
    bottom = row + 2

    spritesheet = Image.open(SPRITESHEET_PATH).convert('RGB')
    sprite = spritesheet.crop((left, top, right, bottom))

    while not have_all_border(sprite):
        while not have_top_border(sprite):
            top -= 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_bottom_border(sprite):
            bottom += 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_left_border(sprite):
            left -= 1
            sprite = spritesheet.crop((left, top, right, bottom))

        while not have_right_border(sprite):
            right += 1
            sprite = spritesheet.crop((left, top, right, bottom))

    print('left:', left)
    print('top:', top)
    print('right:', right)
    print('bottom:', bottom)

    # sprite.show()


def main():
    print(get_spritesheet_coordinate(303, 384))


if __name__ == '__main__':
    main()
