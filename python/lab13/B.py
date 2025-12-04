import tkinter as tk
from tkinter import messagebox
root = tk.Tk()
root.title("Телефонная книга")
root.geometry("625x425")

def add_contact():
    name = entry.get()
    nomer = int(entry2.get())
    if name != '' and nomer != '':
        listbox.insert(tk.END,name+"-"+str(nomer))
        entry.delete(0, tk.END)
        entry2.delete(0,tk.END)
        messagebox.showinfo("Контакт","Контакт добавлен")
    else:
        messagebox.showwarning("Ошибка","Некоректно введены данные,попробуйте снова!")
def delete_contact():
    selected = listbox.curselection()    
    listbox.delete(selected)

def clear():
    listbox.delete(0,tk.END)
    messagebox.showinfo("Контакты удалены","Список очищен")
def pashalka():
    window = tk.Toplevel()
    window.title("Пасхалка")
    window.geometry("1000x200")
    messagebox.showinfo("Пасхалка","Поздравляем вы нашли пасхалку")
    label_secret = tk.Label(window, text='Штирлиц лежал на кровати. Лампа горела, но света не давала. Штирлиц потушил лампу и Света дала', font="Arial 14")
    label_secret.pack()
    label_secret2 = tk.Label(window, text="Спасибо за внимание",font="Arial 14")
    label_secret2.pack()

label1 = tk.Label(root, text="Список контактов", font="Arial 14")
label1.pack()
listbox = tk.Listbox(root, width=30)
listbox.pack()
label2 = tk.Label(root, text="Введите имя контакта:")
label2.pack()
entry = tk.Entry(root)
entry.pack()
label3 = tk.Label(root, text="Введите номер:")
label3.pack()
entry2 = tk.Entry(root)
entry2.pack()
button_add = tk.Button(root, text="Добавить контакт", command=add_contact)
button_add.pack()
button_delete = tk.Button(root, text="Удалить контакт",command=delete_contact)
button_delete.pack()
button_clear = tk.Button(root, text="Очистить список", command=clear)
button_clear.pack()
button_secret= tk.Button(root, text="Пасхалка", command=pashalka)
button_secret.pack()
root.mainloop()