from tkinter import *
from tkinter import ttk
from tkinter.messagebox import showerror

window = Tk()
window.geometry("800x450")
window.title("Python Hesap Makinesi")

def calculation1():
    try:
       t1 = int(a.get())
       t2 = int(b.get())
       sum = t1 + t2
       label1.config(text=sum)
    except ValueError:
        showerror(title="Hata", message="Lütfen bir sayı değeri girin.")
    
def calculation2():
    try:
       t1 = int(a.get())
       t2 = int(b.get())
       multiplication = t1 * t2
       label2.config(text=multiplication)
    except ValueError:
        showerror(title="Hata", message="Lütfen bir sayı değeri girin.")

def calculation3():
    try:
        t1 = int(a.get())
        t2 = int(b.get())
        if t2 == 0:
            showerror(title="Hata", message="Bir sayıyı sıfıra bölemezsiniz.")
        else:
            division = t1 / t2
            label3.config(text=division)
    except ValueError:
        showerror(title="Hata", message="Lütfen bir sayı değeri girin.")

def calculation4():
    try:
        t1 = int(a.get())
        t2 = int(b.get())
        subtraction = t1 - t2
        label4.config(text=subtraction)
    except ValueError:
        showerror(title="Hata", message="Lütfen bir sayı değeri girin.")

def calculation5():
    try:
        t1 = int(a.get())
        t2 = int(b.get())
        if t2 == 0:
            showerror(title="Hata", message="BİR SAYI SIFIRA BÖLÜNEMEZ.")        
        else:
            mod = t1 % t2
            label5.config(text=mod)
    except ValueError:
        showerror(title="Hata", message="Lütfen bir sayı değeri girin.")

Label(window, text="Python İki Tam Sayılı Hesap Makinesine Hoşgeldiniz!", font=('Calibri 18 bold'), justify=CENTER).grid(row=0, column=0, columnspan=3, pady=10, padx=125)
Label(window, text="Lütfen işlem yapmak istediğiniz sayıları giriniz.", font=('Calibri 16'), justify=CENTER).grid(row=1, column=0, columnspan=3, padx= 125)

Label(window, text="İlk Sayı:", font=('Calibri 12')).grid(row=2, column=0, padx=10, pady=5, sticky=E)
a = Entry(window, width=30)
a.grid(row=2, column=1, padx=10, pady=5)

Label(window, text="İkinci Sayı:", font=('Calibri 12')).grid(row=3, column=0, padx=10, pady=5, sticky=E)
b = Entry(window, width=30)
b.grid(row=3, column=1, padx=10, pady=5)

Label(window, text="Lütfen yapmak istediğiniz işlemi seçiniz.", font=('Calibri 16'), justify=CENTER).grid(row=4,column=0, columnspan=3, padx=125)

Button(window, text="Topla", command=calculation1).grid(row=5, column=0, padx=10, pady=10)
label1 = Label(window, text=" ", font=('Calibri 15'))
label1.grid(row=5, column=1, padx=10, pady=10)

Button(window, text="Çıkar", command=calculation4).grid(row=6,column=0, padx=10, pady=10)
label4=Label(window, text=" ", font=('Calibri 15'))
label4.grid(row=6, column=1, padx=10, pady=10)


Button(window, text="Çarp", command=calculation2).grid(row=7, column=0, padx=10, pady=10)
label2 = Label(window, text=" ", font=('Calibri 15'))
label2.grid(row=7, column=1, padx=10, pady=10)

Button(window, text="Böl", command=calculation3).grid(row=8, column=0, padx=10, pady=10)
label3 = Label(window, text=" ", font=('Calibri 15'))
label3.grid(row=8, column=1, padx=10, pady=10)

Button(window, text="Bölümünden Kalanı Bul",command=calculation5).grid(row=9, column=0, padx=10, pady=10)
label5 = Label(window, text=" ", font=('Calibri 15'))
label5.grid(row=9, column=1, padx=10, pady=10)

window.mainloop()
