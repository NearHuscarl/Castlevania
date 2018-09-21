from tkinter import (
    Frame,
    Tk,
    DISABLED,
    NORMAL,
    END,
    PhotoImage,
    filedialog,
)
from tkinter.ttk import (
    Button,
    Entry,
    Label,
    Labelframe
)

from PIL import ImageTk, Image
import os

import spritesheet
from color import rgb_to_hex, hex_to_rgb


class Application(Frame):

    def __init__(self, master):
        Frame.__init__(self, master)

        self.master: Tk = master

        self.init_ui()
        self.center_window()

    def init_ui(self):
        self.master.title("Spritesheet Tool")
        self.padding = '1m'
        self.copyImage = PhotoImage(file='images/copy.png')  # 16x16 pixels

        self.master.grid_rowconfigure(0, weight=1)
        self.master.grid_columnconfigure(0, weight=1)

        self.previewFrame = Frame(self.master)
        self.infoFrame = Frame(self.master)

        self.actionFrame = Labelframe(self.infoFrame, text='Menu')
        self.settingFrame = Labelframe(self.infoFrame, text='Settings')
        self.bboxFrame = Labelframe(self.infoFrame, text='Boundary Box')
        self.spriteFrame = Labelframe(self.infoFrame, text='Sprite Preview')

        self.previewFrame.grid(column=0, row=0, sticky='nsew')
        self.infoFrame.grid(column=1, row=0, sticky='n')

        self.actionFrame.grid(column=0, row=1, padx=self.padding, pady=self.padding, sticky='ew')
        self.actionFrame.grid_columnconfigure(0, weight=1)
        self.actionFrame.grid_columnconfigure(2, weight=1)
        self.actionFrame.grid_rowconfigure(0, weight=1)
        self.actionFrame.grid_rowconfigure(2, weight=1)

        self.settingFrame.grid(column=0, row=2, padx=self.padding, pady=self.padding, sticky='ew')
        self.settingFrame.grid_columnconfigure(1, weight=1)

        self.bboxFrame.grid(column=0, row=3, padx=self.padding, pady=self.padding, sticky='ew')
        self.bboxFrame.grid_columnconfigure(1, weight=1)

        self.spriteFrame.grid(column=0, row=4, padx=self.padding, pady=self.padding, sticky='w')
        self.spriteFrame.grid_columnconfigure(0, weight=1)
        self.spriteFrame.grid_columnconfigure(2, weight=1)
        self.spriteFrame.grid_rowconfigure(0, weight=1)
        self.spriteFrame.grid_rowconfigure(2, weight=1)

        self.spritesheetPanel = Label(self.previewFrame)
        self.spritesheetPanel.bind('<Button 1>', self.on_click_image)

        self.openButton = Button(self.actionFrame, text='Open Spritesheet', command=self.on_open_image)

        self.transColorLabel = Label(self.settingFrame, text='Transparent Color')
        self.transColorEntry = Entry(self.settingFrame, width=10)
        self.transColorPanel = Label(self.settingFrame)

        self.topLabel = Label(self.bboxFrame, text='top')
        self.bottomLabel = Label(self.bboxFrame, text='bottom')
        self.leftLabel = Label(self.bboxFrame, text='left')
        self.rightLabel = Label(self.bboxFrame, text='right')

        self.topEntry = Entry(self.bboxFrame)
        self.bottomEntry = Entry(self.bboxFrame)
        self.leftEntry = Entry(self.bboxFrame)
        self.rightEntry = Entry(self.bboxFrame)

        self.copyTopButton = Button(self.bboxFrame, image=self.copyImage,
                                    command=lambda: self.on_click_copy_button(self.topEntry))
        self.copyBottomButton = Button(self.bboxFrame, image=self.copyImage,
                                       command=lambda: self.on_click_copy_button(self.bottomEntry))
        self.copyLeftButton = Button(self.bboxFrame, image=self.copyImage,
                                     command=lambda: self.on_click_copy_button(self.leftEntry))
        self.copyRightButton = Button(self.bboxFrame, image=self.copyImage,
                                      command=lambda: self.on_click_copy_button(self.rightEntry))

        self.spritePanel = Label(self.spriteFrame, border=2)

        self.spritesheetPanel.grid(row=0, column=0)
        self.openButton.grid(row=1, column=1, padx=self.padding, pady=self.padding)

        self.transColorLabel.grid(row=1, column=0, padx=self.padding)
        self.transColorEntry.grid(row=1, column=1, sticky='ew')
        self.transColorPanel.grid(row=1, column=2, sticky='ew')

        self.topLabel.grid(row=0, column=0, sticky='e', padx=self.padding, pady=self.padding)
        self.bottomLabel.grid(row=1, column=0, sticky='e', padx=self.padding, pady=self.padding)
        self.leftLabel.grid(row=2, column=0, sticky='e', padx=self.padding, pady=self.padding)
        self.rightLabel.grid(row=3, column=0, sticky='e', padx=self.padding, pady=self.padding)

        self.topEntry.grid(row=0, column=1, sticky='ew')
        self.bottomEntry.grid(row=1, column=1, sticky='ew')
        self.leftEntry.grid(row=2, column=1, sticky='ew')
        self.rightEntry.grid(row=3, column=1, sticky='ew')

        self.copyTopButton.grid(row=0, column=2, padx=self.padding)
        self.copyBottomButton.grid(row=1, column=2, padx=self.padding)
        self.copyLeftButton.grid(row=2, column=2, padx=self.padding)
        self.copyRightButton.grid(row=3, column=2, padx=self.padding)

        self.spritePanel.grid(row=1, column=1, sticky='nsew')
        self.init_value()

    def init_value(self):
        default_spritesheet_path = os.path.join(os.getcwd(), 'images', 'spritesheet.png')
        self.set_spritesheet_panel(default_spritesheet_path)
        self.set_transparent_color(self.spritesheet_image.getpixel((0, 0)))

    def set_spritesheet_panel(self, image_path):
        self.spritesheet_image = Image.open(image_path).convert('RGB')
        self.spritesheet_photo = ImageTk.PhotoImage(self.spritesheet_image)
        self.spritesheetPanel.configure(image=self.spritesheet_photo)

    def set_transparent_color(self, rgb_color):
        self.transColorEntry.configure(state=NORMAL)
        self.set_text(self.transColorEntry, rgb_to_hex(rgb_color))
        self.transColorEntry.configure(state=DISABLED)

        self.trans_color_photo = ImageTk.PhotoImage(Image.new(self.spritesheet_image.mode, (19, 19), rgb_color))
        self.transColorPanel.configure(image=self.trans_color_photo)

    def center_window(self):
        self.master.update_idletasks()

        width = self.master.winfo_width()
        height = self.master.winfo_height()

        x = (self.master.winfo_screenwidth() // 2) - (width // 2)
        y = (self.master.winfo_screenheight() // 2) - (height // 2)

        self.master.geometry('{}x{}+{}+{}'.format(width, height, x, y))

    def resize(self):
        width = self.spritesheet_photo.width() + self.infoFrame.winfo_width()
        height = max(self.spritesheet_photo.height(), self.infoFrame.winfo_height())
        self.master.geometry('{}x{}'.format(width, height))

    def on_open_image(self):
        filetypes = [('Images', '*.png'), ('All files', '*')]
        dialog = filedialog.Open(self, filetypes=filetypes)
        path = dialog.show()

        if path != '':
            self.set_spritesheet_panel(path)
            self.set_transparent_color(self.spritesheet_image.getpixel((0, 0)))

            self.resize()
            self.center_window()

    @classmethod
    def set_text(cls, entry, text):
        entry.delete(0, END)
        entry.insert(0, text)

    def on_click_image(self, e):
        bbox = spritesheet.get_sprite_bbox(
            (e.x, e.y),
            self.spritesheet_image,
            hex_to_rgb(self.transColorEntry.get()))

        if bbox is None:
            return

        left, top, right, bottom = bbox

        self.set_text(self.leftEntry, left)
        self.set_text(self.topEntry, top)
        self.set_text(self.rightEntry, right)
        self.set_text(self.bottomEntry, bottom)

        self.sprite_image = self.spritesheet_image.crop((left, top, right, bottom))
        self.sprite_photo = ImageTk.PhotoImage(self.sprite_image)
        self.spritePanel.configure(image=self.sprite_photo)

    def on_click_copy_button(self, entry):
        self.master.clipboard_clear()
        self.master.clipboard_append(entry.get())
        self.master.update()  # now it stays on the clipboard after the window is closed


def main():
    root = Tk()

    app = Application(root)
    app.mainloop()


if __name__ == '__main__':
    main()
