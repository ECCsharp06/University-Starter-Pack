from tkinter import *
from tkinter import ttk
from tkinter.messagebox import showerror

window = Tk()
window.geometry("400x600")
window.title("Python Hesap Makinesi Geliştirilmiş")

# Configure grid layout to center the widgets
window.grid_rowconfigure(0, weight=1)
window.grid_rowconfigure(1, weight=1)
window.grid_rowconfigure(2, weight=1)
window.grid_rowconfigure(3, weight=1)
window.grid_rowconfigure(4, weight=1)
window.grid_rowconfigure(5, weight=1)
window.grid_rowconfigure(6, weight=1)
window.grid_rowconfigure(7, weight=1)
window.grid_rowconfigure(8, weight=1)
window.grid_columnconfigure(0, weight=1)
window.grid_columnconfigure(1, weight=1)
window.grid_columnconfigure(2, weight=1)
window.grid_columnconfigure(3, weight=1)

def calculate():
    try:
        result = eval(a.get())
        a.delete(0, END)
        a.insert(END, result)
    except ZeroDivisionError:
        a.delete(0, END)
        showerror(title="Hata", message="BİR SAYI SIFIRA BÖLÜNEMEZ.")
    except ValueError:
        a.delete(0, END)
        showerror(title="Hata", message="Lütfen bir sayı değeri girin.")
    except SyntaxError:
        a.delete(0, END)
        showerror(title="Hata", message="Geçersiz işlem. Bir sayıyı yanlış yazmış olabilirsiniz.")

def clear():
    a.delete(0, END)

def key_input(event):
    key = event.char
    if key == "\r":
        calculate()
    elif key == "\x08":
        a.delete(len(a.get())-1)
    elif key in "0123456789+-*/.()":
        a.insert(END, key)
    elif key == 'c' or key == 'C':
        clear()
    elif key == '%':
        a.insert(END, "%")
    elif key == '^':
        a.insert(END, "**")
    elif key == 'x':
        a.insert(END, "*")

window.bind("<Key>", key_input)

Button(window, text="1", command=lambda: a.insert(END, "1"), width=3, height=3).grid(row=2, column=0, pady=6, padx=6, sticky="nsew")
Button(window, text="2", command=lambda: a.insert(END, "2"), width=3, height=3).grid(row=2, column=1, pady=6, padx=6, sticky="nsew")
Button(window, text="3", command=lambda: a.insert(END, "3"), width=3, height=3).grid(row=2, column=2, pady=6, padx=6, sticky="nsew")
Button(window, text="+", command=lambda: a.insert(END, "+"), width=3, height=3).grid(row=2, column=3, pady=6, padx=6, sticky="nsew")

Button(window, text="4", command=lambda: a.insert(END, "4"), width=3, height=3).grid(row=3, column=0, pady=6, padx=6, sticky="nsew")
Button(window, text="5", command=lambda: a.insert(END, "5"), width=3, height=3).grid(row=3, column=1, pady=6, padx=6, sticky="nsew")
Button(window, text="6", command=lambda: a.insert(END, "6"), width=3, height=3).grid(row=3, column=2, pady=6, padx=6, sticky="nsew")
Button(window, text="-", command=lambda: a.insert(END, "-"), width=3, height=3).grid(row=3, column=3, pady=6, padx=6, sticky="nsew")

Button(window, text="7", command=lambda: a.insert(END, "7"), width=3, height=3).grid(row=4, column=0, pady=6, padx=6, sticky="nsew")
Button(window, text="8", command=lambda: a.insert(END, "8"), width=3, height=3).grid(row=4, column=1, pady=6, padx=6, sticky="nsew")
Button(window, text="9", command=lambda: a.insert(END, "9"), width=3, height=3).grid(row=4, column=2, pady=6, padx=6, sticky="nsew")
Button(window, text="x", command=lambda: a.insert(END, "*"), width=3, height=3).grid(row=4, column=3, pady=6, padx=6, sticky="nsew")

Button(window, text="C", command=clear, width=3, height=3).grid(row=5, column=0, pady=6, padx=6, sticky="nsew")
Button(window, text="0", command=lambda: a.insert(END, "0"), width=3, height=3).grid(row=5, column=1, pady=6, padx=6, sticky="nsew")
Button(window, text="=", command=calculate, width=3, height=3).grid(row=5, column=2, pady=6, padx=6, sticky="nsew")
Button(window, text="/", command=lambda: a.insert(END, "/"), width=3, height=3).grid(row=5, column=3, pady=6, padx=6, sticky="nsew")

Button(window, text="(", command=lambda: a.insert(END, "("), width=3, height=3).grid(row=6, column=0, pady=6, padx=6, sticky="nsew")
Button(window, text=")", command=lambda: a.insert(END, ")"), width=3, height=3).grid(row=6, column=1, pady=6, padx=6, sticky="nsew")
Button(window, text=".", command=lambda: a.insert(END, "."), width=3, height=3).grid(row=6, column=2, pady=6, padx=6, sticky="nsew")
Button(window, text="%", command=lambda: a.insert(END, "%"), width=3, height=3).grid(row=6, column=3, pady=6, padx=6, sticky="nsew")

Button(window, text="^", command=lambda: a.insert(END, "**"), width=3, height=3).grid(row=7, column=0, pady=6, padx=6, sticky="nsew")
Button(window, text="√", command=lambda: a.insert(END, "**0.5"), width=3, height=3).grid(row=7, column=1, pady=6, padx=6, sticky="nsew")
Button(window, text="1/x", command=lambda: a.insert(END, "**-1"), width=3, height=3).grid(row=7, column=2, pady=6, padx=6, sticky="nsew")
Button(window, text="x^2", command=lambda: a.insert(END, "**2"), width=3, height=3).grid(row=7, column=3, pady=6, padx=6, sticky="nsew")

Button(window, text="Delete", command=lambda: a.delete(len(a.get())-1), width=3, height=3).grid(row=8, column=0, pady=6, padx=6, sticky="nsew")
Button(window, text="Çıkış", command=window.quit, width=3, height=3).grid(row=8, column=1, pady=6, padx=6, sticky="nsew")

a = Entry(window, width=50, borderwidth=5)
a.grid(row=1, column=0, columnspan=4, pady=6, padx=6, sticky="nsew")

window.mainloop()