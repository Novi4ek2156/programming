import tkinter as tk
from tkinter import messagebox
import random

fruits = ["Яблоко", "Абрикос", "Апельсин", "Банан"]
index = 0
result = ""
school = ["Ручка", "Линейка", "Карандаш", "Пенал"]
animals = ["Кот", "Собака", "Сова", "Хомяк"]
popitki = 6  
slovo = ""   

def new_game():
    global index, result, slovo, popitki
    index = random.randint(0, 3)
    b = selected_words.get()
    result = ''
    slovo = ''
    popitki = 6  
    label_viselitsa.configure(text=" ")
    if b == "Фрукты":
        messagebox.showinfo("Начало игры", "Вы начали новую игру")
        slovo = len(fruits[index]) * "-"
        label_slovo.configure(text=slovo)
    elif b == "Школа":
        messagebox.showinfo("Начало игры", "Вы начали новую игру")
        slovo = len(school[index]) * "-"
        label_slovo.configure(text=slovo)
    elif b == "Животные":
        messagebox.showinfo("Начало игры", "Вы начали новую игру")
        slovo = len(animals[index]) * '-'
        label_slovo.configure(text=slovo)
    else:
        messagebox.showwarning("Ошибка", "Выберите тему")
    
    label_kolvo_popitok.configure(text=f"Осталось попыток: {popitki}")
    label_result.configure(text="")
    entry.delete(0, tk.END)

def main_game():
    global result, slovo, popitki
    b = selected_words.get()
    entry_get = entry.get().strip()
    
   
    if len(entry_get) != 1:
        messagebox.showwarning("Ошибка", "Введите ровно одну букву!")
        return
    
    word = ""
    if b == "Фрукты":
        word = fruits[index]
    elif b == "Школа":
        word = school[index]
    elif b == "Животные":
        word = animals[index]
    else:
        messagebox.showwarning("Ошибка", "Сначала выберите тему!")
        return
    

    new_slovo = ""
    guessed = False
    for i in range(len(word)):
        if word[i].lower() == entry_get.lower() or word[i] == entry_get:
            new_slovo += word[i]
            if slovo[i] == "-":
                guessed = True
        else:
            new_slovo += slovo[i]
    
    slovo = new_slovo
    label_slovo.configure(text=slovo)
    

    if not guessed:
        popitki -= 1
        label_kolvo_popitok.configure(text=f"Осталось попыток: {popitki}")
        if popitki == 0:
            messagebox.showinfo("Конец игры", f"Вы проиграли! Загаданное слово: {word}")
            label_viselitsa.configure(text="")
            return
    if popitki < 6:
        if popitki == 5:
            label_viselitsa.configure(text="----")
        if popitki == 4:
            label_viselitsa.configure(text="----\n"
                                           "|    |  \n")
        if popitki == 3:
            label_viselitsa.configure(text="----\n"
                                           "|    |  \n"
                                           "|    0  \n")
        if popitki == 2:
            label_viselitsa.configure(text="----\n"
                                           "|    |  \n"
                                           "|    0  \n"
                                           "|   /|\\\n")
        if popitki == 1:
            label_viselitsa.configure(text="----\n"
                                           "|    |  \n"
                                           "|    0  \n"
                                           "|   /|\\\n"
                                           "|    /\\\n"
                                           "|_______")

    if "-" not in slovo:
        label_viselitsa.configure(text=" ")
        messagebox.showinfo("Победа!", f"Вы угадали слово: {word}")
        return
    
    entry.delete(0, tk.END)
    

root = tk.Tk()
root.title("Виселица")
root.geometry("800x500")

label_tem = tk.Label(root, text="Выберите тему:", font="Arial 18")
label_tem.pack()

option = ["Фрукты", "Школа", "Животные"]
selected_words = tk.StringVar(value="Выберите тему:")
option_menu = tk.OptionMenu(root, selected_words, *option)
option_menu.config(width=15, font="Arial 12")
option_menu.pack()

label_slovo = tk.Label(root, text="", font="Arial 18")
label_slovo.pack()

label_result = tk.Label(root, text="", font="Arial 18")
label_result.pack()

label_kolvo_popitok = tk.Label(root, text="Осталось попыток: 6", font="Arial 14")
label_kolvo_popitok.pack()

label_viselitsa = tk.Label(root, text="")
label_viselitsa.pack()

label_entry = tk.Label(root, text="Введите букву:", font="Arial 18")
label_entry.pack()

entry = tk.Entry(root)
entry.pack()

button = tk.Button(root, text="Проверить", command=main_game)
button.pack()

button_new_game = tk.Button(root, text="Новая игра", command=new_game)
button_new_game.pack()

root.mainloop()