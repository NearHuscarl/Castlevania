from tkinter import (
    Frame,
    Tk,
    END,
)


class Application(Frame):
    """ TKinter Application base class with some helper methods """

    def __init__(self, master):
        Frame.__init__(self, master)
        self.master: Tk = master

    @classmethod
    def validate_number_value(cls, current_char):
        """ accept number value only """
        if current_char in '0123456789':
            return True
        return False

    def center_window(self):
        self.master.update_idletasks()

        width = self.master.winfo_width()
        height = self.master.winfo_height()

        x = (self.master.winfo_screenwidth() // 2) - (width // 2)
        y = (self.master.winfo_screenheight() // 2) - (height // 2)

        self.master.geometry('{}x{}+{}+{}'.format(width, height, x, y))

    @classmethod
    def set_text(cls, entry, text):
        entry.delete(0, END)
        entry.insert(0, text)

    @classmethod
    def set_readonly_text(cls, entry, text):
        entry.configure(state='normal')
        cls.set_text(entry, text)
        entry.configure(state='readonly')
