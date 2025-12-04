import tkinter as tk
import random
window = tk.Tk()

def command1():
    a = random.randint(0, 3)
    cvet = ["pink", "blue", "yellow"]
    if a in range(0,3):
        label.configure(bg=cvet[a])








window.title("Hello")
window.geometry("400x200")

label = tk.Label(window, text="Hello")
label.pack()
button = tk.Button(window, text="Enter", command=command1)
button.pack()


window.mainloop()