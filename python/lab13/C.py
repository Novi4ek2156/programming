import tkinter as tk

est_a_no_b = []
est_b_no_a = []
zn_odinakov = []
odinakovo = 0
root = tk.Tk()
root.title("Сравнение списков")
root.geometry("800x400")
def add_a():
    x = entry.get()
    listbox_a.insert(tk.END,x)
    entry.delete(0, tk.END)
        
def add_b():
    x = entry.get()
    listbox_b.insert(tk.END,x)
    entry.delete(0, tk.END)

def proverka():
    zn_a = listbox_a.get(0, tk.END)
    zn_b = listbox_b.get(0, tk.END)
    est_a_no_b = []
    est_b_no_a = []
    zn_odinakov = []
    odinakovo = 0
    for i in zn_a:
        if i in zn_b:
            odinakovo+=1
            zn_odinakov.append(i)
        if i != zn_b and i not in zn_odinakov:
            est_a_no_b.append(i)
    for i in zn_b:
        if i not in zn_a and i not in zn_odinakov:
            est_b_no_a.append(i)
    label_end.configure(text=f"Есть в А но нету в Б:{est_a_no_b}\nЕсть в Б но нету в А:{est_b_no_a}\nОдиново:{odinakovo}|{zn_odinakov }")


label_sp1 = tk.Label(root, text="Список А:")
label_sp1.grid(row=0, column=0)
label_sp2 = tk.Label(root, text="Список Б:")
label_sp2.grid(row=0, column=1)
label_result = tk.Label(root, text="Результат:")
label_result.grid(row=0, column=2)
listbox_a = tk.Listbox(root, width=20)
listbox_a.grid(row=1, column=0)
listbox_b = tk.Listbox(root, width=20)
listbox_b.grid(row=1, column=1)
label_end = tk.Label(root, text="")
label_end.grid(row=1, column=2)
label_entry = tk.Label(root, text="Введите значение:")
label_entry.grid(row=2, column=0)
entry = tk.Entry(root)
entry.grid(row=2, column=1)
button_a = tk.Button(root, text="Добавить в А", command=add_a)
button_a.grid(row=3, column=0)
button_b = tk.Button(root, text="Добавить в Б", command=add_b)
button_b.grid(row=3, column=1)
button_result = tk.Button(root, text="Проверка", command=proverka)
button_result.grid(row=3, column=2)

root.mainloop()