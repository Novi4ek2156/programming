import tkinter as tk
from tkinter import messagebox

Accounts = "/home/vlad/programming/python/RGR/users_accounts"
Books = "/home/vlad/programming/python/RGR/books_list"
korz_list = []
def window_register(): #окно регистрации
    global win_register, win_password_entry1, win_password_entry2, win_login_entry
    win_register = tk.Toplevel()
    win_register.title("Регистрация")
    win_register.geometry('400x300')
    win_register.transient(root)
    win_register.grab_set()
    win_login = tk.Label(win_register, text="Логин:")
    win_login.pack()
    win_login_entry = tk.Entry(win_register)
    win_login_entry.pack()
    win_password_label1 = tk.Label(win_register, text="Введите пароль:")
    win_password_label1.pack()
    win_password_entry1 = tk.Entry(win_register, show="*")
    win_password_entry1.pack()
    win_password_label2 = tk.Label(win_register, text="Подтвердите пароль:")
    win_password_label2.pack()
    win_password_entry2 = tk.Entry(win_register, show="*")
    win_password_entry2.pack()
    win_register_button = tk.Button(win_register, text="Создать аккаунт", command=create_account)
    win_register_button.pack()   
user_name = []
user_password = []
user_code =[]
def create_account(): #ф-я создания аккаунта
    global user_name, user_password
    password1 = win_password_entry1.get()
    password2 = win_password_entry2.get()
    name = win_login_entry.get()
    if password1 != password2:
        messagebox.showerror('Ошибка', 'Пароли не совпадают!')
    else:
        with open(Accounts, 'r') as file:
            users =[]
            for line in file:
                line = line.split(":")
                users.append(line[0])
                print(users, line)
            if name not in users:
                with open(Accounts, 'a') as file:
                    file.write(f"{name}:{password1}\n")
                    messagebox.showinfo("Аккаунт","Аккаунт успешно создан!")
            elif name in users:
                messagebox.showerror("Ошибка","Аккаунт с таким именем уже есть")
                  
def vhod_v_account(): #окно входа в аккаунт
    global vhod_entry_login, vhod_entry_passwd
    win_vhod = tk.Toplevel()
    win_vhod.title("Вход")
    win_vhod.geometry("400x300")
    win_vhod.transient(root)
    win_vhod.grab_set()
    vhod_label_login = tk.Label(win_vhod, text="Введите логин:")
    vhod_label_login.pack()
    vhod_entry_login = tk.Entry(win_vhod)
    vhod_entry_login.pack()
    vhod_label_passwd = tk.Label(win_vhod, text="Введите пароль:")
    vhod_label_passwd.pack()
    vhod_entry_passwd = tk.Entry(win_vhod, show="*")
    vhod_entry_passwd.pack()
    vhod_button = tk.Button(win_vhod, text="Войти", command=vhod)
    vhod_button.pack()
def vhod(): #ф-я входа
    name = vhod_entry_login.get()
    password = vhod_entry_passwd.get()
    with open(Accounts, "r") as file:
        global user_code, user_name, user_password
        i = 0
        lines = file.readlines()
        while i in range(0, len(Accounts)):
            line = lines[i].strip("\n")
            a, b = line.split(':')
            if a == name and b == password:
                break
            else:
                i+=1   
        if name == a and password == b :
            messagebox.showinfo("Вход", "Вы вошли в аккаунт")
            user_name = name
            user_password = password
            user_code = i
            user_label.configure(text=name)
            i+=1
        elif name != lines[0] or password != lines[-1]:
            messagebox.showerror("Вход", "Не верно введен логин или пароль")
            
        else:
            i+=1


def menu_korzina():
    global korz_listbox
    win_korz = tk.Toplevel()
    win_korz.title("Корзина")
    win_korz.geometry("400x300")
    win_korz.transient(root)
    win_korz.grab_set()
    korz_label = tk.Label(win_korz, text="Список товаров:")
    korz_label.pack()
    korz_listbox = tk.Listbox(win_korz, width=60)
    for i in range(len(korz_list)):
        korz_listbox.insert(tk.END, korz_list[i])
    korz_listbox.pack()
    korz_button1 = tk.Button(win_korz, text="Приобрести", command=buying)
    korz_button1.pack()
    korz_button2 = tk.Button(win_korz, text="Очистить список", command=ochistka)
    korz_button2.pack()
def ochistka():
    korz_list.clear()
    korz_listbox.delete(0, tk.END)
    messagebox.showinfo("Очистка","Список очищен")
def add_to_korzina():                           
    a = root_listbox.curselection()
    if a:
        index = a[0]
        value = root_listbox.get(index)
        korz_list.append(value)
    else:
        messagebox.showerror("Ошибка","Ошибка")
def dobavka_knig():
    with open(Books, 'r', encoding='utf-8') as file:
        for line in file:
            book_line = line.split(":")
            book_line[-1] = book_line[-1].strip("\n")
            if book_line and len(book_line) != 0:  
                root_listbox.insert(tk.END, f"\"{book_line[0]}\" Автор: {book_line[1]}, В наличии: {book_line[2]}")
def searching():
    book = search_entry.get()
    spisok = root_listbox.get(0, tk.END)
    if len(book) == 0:
            messagebox.showerror("Ошибка","Поле не должно быть пустым")
    else:
        for i in range(len(spisok)):
            if book.lower() in spisok[i].lower():  
                root_listbox.itemconfig(i, bg="yellow")  
                found = True
            else:
                root_listbox.itemconfig(i, bg="white")  
        if not found:
            messagebox.showinfo("Результат поиска", "Ничего не найдено")
def buying():
    # Читаем все данные из файла
    with open(Books, "r") as file:
        lines = file.readlines()
    books_data = {}
    for line in lines:
        line = line.strip()
        if line and ":" in line:
            parts = line.split(":")
            if len(parts) >= 3:
                key = f"{parts[0]}:{parts[1]}" 
                books_data[key] = int(parts[2])
    
    for item in korz_list:
        item = item.strip()
        if not item or ":" not in item:
            continue      
        parts = item.split(":")
        if len(parts) < 3:
            continue    
        book_name = parts[0]
        author = parts[1]
        buy_quantity = int(parts[2])
        key = f"{book_name}:{author}"
        if key in books_data:
            books_data[key] -= buy_quantity
            if books_data[key] < 0:
                books_data[key] = 0
            print(f"Куплено {buy_quantity} шт.: {book_name} ({author})")
    with open(Books, "w") as file:
        for key, quantity in books_data.items():
            name_author = key.split(":")
            file.write(f"{name_author[0]}:{name_author[1]}:{quantity}\n")
    
   
    korz_list.clear()
    messagebox.showinfo("Покупка","Покупка завершена!")



root = tk.Tk()
root.title("Книжный магазин")
root.geometry("770x400")
user_label = tk.Label(root, text="Гость")
user_label.grid(row=0, column=0)
korzina_button = tk.Button(root, text="🛒", command=menu_korzina)
korzina_button.grid(row=0, column=1, sticky='ne')
register_button = tk.Button(root, text="Регистрация", command=window_register)
register_button.grid(row=0, column=2, sticky="ne")
vhod_button = tk.Button(root, text="Войти", command=vhod_v_account) 
vhod_button.grid(row=0, column=3, sticky="ne")
label_search = tk.Label(root, text="Поиск:")
label_search.grid(row=1, column=0)
search_entry = tk.Entry(root, width=60)
search_entry.grid(row=1, column=1)
search_button = tk.Button(root, text="🔍", command=searching)
search_button.grid(row=1, column=2)
root_listbox = tk.Listbox(root, width=60)
dobavka_knig()
root_listbox.bind("<Double-Button-1>", add_to_korzina)
root_listbox.grid(row=2,column=1, pady=10)
root_for_korz_button = tk.Button(root, text="Добавить\nв корзину", command=add_to_korzina)
root_for_korz_button.grid(row=3, column=0)
root.mainloop()
    
