import tkinter as tk

step = 0
root = tk.Tk()
root.title("")
root.geometry("+500+500")

def next_step():
    global step, A, B
    step += 1
    if step == 1:
        A = int(alice_g_ent.get()) ** int(alice_a_ent.get()) % int(alice_p_ent.get())
        # txt = alice_chat_lbl.cget("text") + "\n"
        txt = alice_g_ent.get() + "^" + alice_a_ent.get() + " mod " + alice_p_ent.get() + " = " + str(A)
        alice_chat_lbl.config(text=txt)
    if step == 2:
        # txt = eve_chat_lbl.cget("text") + "\n"
        txt = "➡️: " + alice_g_ent.get() + ", " + alice_p_ent.get() + ", " + str(A)
        eve_chat_lbl.config(text=txt)
    if step == 3:
        B = int(alice_g_ent.get()) ** int(bob_b_ent.get()) % int(alice_p_ent.get())
        # txt = bob_chat_lbl.cget("text") + "\n"
        txt = alice_g_ent.get() + "^" + bob_b_ent.get() + " mod " + alice_p_ent.get() + " = " + str(B)
        bob_chat_lbl.config(text=txt)
    if step == 4:
        K = A ** int(bob_b_ent.get()) % int(alice_p_ent.get())
        txt = bob_chat_lbl.cget("text") + "\n"
        txt += str(A) + "^" + bob_b_ent.get() + " mod " + alice_p_ent.get() + " = " + str(K) + "✅"
        bob_chat_lbl.config(text=txt)
    if step == 5:
        txt = eve_chat_lbl.cget("text") + "\n"
        txt += "⬅️️: " + str(B)
        eve_chat_lbl.config(text=txt)
    if step == 6:
        K = B ** int(alice_a_ent.get()) % int(alice_p_ent.get())
        txt = alice_chat_lbl.cget("text") + "\n"
        txt += str(B) + "^" + alice_a_ent.get() + " mod " + alice_p_ent.get() + " = " + str(K) + "✅"
        alice_chat_lbl.config(text=txt)
    # print(step)


next_btn = tk.Button(root, text="Дальше", command=next_step)
next_btn.pack()

windowAlice = tk.Toplevel(root)
windowAlice.title("Алиса 😇")
windowAlice.geometry("310x350+0+0")
windowAlice.columnconfigure(2, weight=1)
windowAlice.rowconfigure(4, weight=1)

alice_a_lbl = tk.Label(windowAlice, text="Соль: ", anchor="e")
alice_a_lbl.grid(row=0, column=0)
alice_a_ent = tk.Entry(windowAlice)
alice_a_ent.grid(row=0, column=1)
alice_g_lbl = tk.Label(windowAlice, text="G (открытое): ", anchor="e")
alice_g_lbl.grid(row=1, column=0)
alice_g_ent = tk.Entry(windowAlice)
alice_g_ent.grid(row=1, column=1)
alice_p_lbl = tk.Label(windowAlice, text="P (открытое): ", anchor="e")
alice_p_lbl.grid(row=2, column=0)
alice_p_ent = tk.Entry(windowAlice)
alice_p_ent.grid(row=2, column=1)
alice_chat_lbl = tk.Label(windowAlice, bg="white", fg="black", anchor="nw", justify="left")
alice_chat_lbl.grid(row=3, column=0, columnspan=2, padx=5, pady=5, sticky=tk.E + tk.W + tk.S + tk.N)

windowBob = tk.Toplevel(root)
windowBob.title("Боб 😇")
windowBob.geometry("310x350+700+0")
windowBob.columnconfigure(2, weight=1)
windowBob.rowconfigure(4, weight=1)

bob_b_lbl = tk.Label(windowBob, text="Соль: ", anchor="e")
bob_b_lbl.grid(row=0, column=0)
bob_b_ent = tk.Entry(windowBob)
bob_b_ent.grid(row=0, column=1)
bob_chat_lbl = tk.Label(windowBob, bg="white", fg="black", anchor="nw", justify="left")
bob_chat_lbl.grid(row=3, column=0, columnspan=2, pady=61, sticky=tk.E + tk.W + tk.S + tk.N)

# windowCarol = tk.Toplevel(root)
# windowCarol.title("Что показать еще")
# windowCarol.geometry("+475+175")
#
# windowDavid = tk.Toplevel(root)
# windowDavid.title("Что показать еще")
# windowDavid.geometry("+475+175")

windowEve = tk.Toplevel(root)
windowEve.title("Ева 😈")
windowEve.geometry("310x310+350+0")
windowEve.columnconfigure(1, weight=1)
windowEve.rowconfigure(2, weight=1)

eve_chat_lbl = tk.Label(windowEve, bg="white", fg="black", anchor="nw", justify="left")
eve_chat_lbl.grid(row=0, column=0, columnspan=2, pady=89, sticky=tk.E + tk.W + tk.S + tk.N)

root.mainloop()
