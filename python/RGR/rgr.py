import tkinter as tk


root = tk.Tk()
root.title("Книжный магазин")
root.geometry("600x400")
janr = ["Научная литература", "Классическая литература", "Философия"]
books = ["\"Введение в философию\" Зигмунд Фрейд Философия", "\"Понять природу человека\" Альфред Адлер Научная", "\"Зов Ктулху\" Говард Лафкрафт Классика"]
classic = []
filosophi = []
sience = []
for book in books:
    if "Классика" in book:
        classic.append(book)
    elif "Философия" in book:
        filosophi.append(book)
    elif "Научная" in book:
        sience.append(book)
def choice_janre():
    b = selected_words.get()
    listbox.delete(0, tk.END)
    if b == "Классическая литература":
        listbox.insert(0,classic)
    elif b == "Философия":
        listbox.insert(0,filosophi)
    elif b == "Научная литература":
        listbox.insert(0,sience)


selected_words = tk.StringVar(value="Выберите жанр:")
option_menu = tk.OptionMenu(root, selected_words, *janr)
option_menu.config(width=20, font="Arial 12")
option_menu.pack()
listbox = tk.Listbox(root, width=50)
for i in books:
    listbox.insert(0,i)
listbox.pack()
label = tk.Label(root, text="Введите название")
label.pack()
entry = tk.Entry(root)
entry.pack()
button = tk.Button(root, text="enter", command=choice_janre)
button.pack()
root.mainloop()