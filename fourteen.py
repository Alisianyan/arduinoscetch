#-----------------------------------------------------
# GUI to turn ON blue/red LED with brightness control
#-----------------------------------------------------
import tkinter as tk
from tkinter import messagebox
from pyfirmata import Arduino, PWM
is_red_butt_on = False
is_blue_butt_on = False
from time import sleep
# Functions=========================================================
def redLED():
#    global is_red_butt_on
#    is_red_butt_on = not is_red_butt_on
#    if (is_red_butt_on):
    brightness = float(LEDredbright.get())
    board.digital[3].write(brightness/100.0)
#    else:
#    board.digital[3].write(0)

#--------------------------------------------
def blueLED():
#    global is_blue_butt_on
#    is_blue_butt_on = not is_blue_butt_on
#    if is_blue_butt_on:
    brightness = float(LEDbluebright.get())
    board.digital[5].write(brightness/100.0)
#    else:
#        board.digital[5].write(0)
#--------------------------------------------
def aboutMsg():
    messagebox.showinfo("About",
    "Logic Don't Care Software\nLED Control Ver 1.0\nAugust 2022")
#=================================================================
# Arduino board connected to serial port COM3
board = Arduino("COM4")
# set mode of Arduino pins D3 & D5 for PWM
board.digital[3].mode = PWM
board.digital[5].mode = PWM
#--------------------------------------------
# initialize window with title & size
win = tk.Tk()
win.title("LED Control")
win.minsize(235,150)
#--------------------------------------------
# Scale widget
LEDbluebright = tk.Scale(win, bd=5, from_=0, to=100, orient=tk.HORIZONTAL)
LEDbluebright.grid(column=1, row=1)
# Label widget
tk.Label(win, text="Red LED Brightness (%)").grid(column=2, row=1)
#--------------------------------------------
# Scale widget
LEDredbright = tk.Scale(win, bd=5, from_=0, to=100, orient=tk.HORIZONTAL)
LEDredbright.grid(column=1, row=2)
# Label widget
tk.Label(win, text="Blue LED Brightness (%)").grid(column=2, row=2)
#--------------------------------------------
# Button widgets
blueBtn = tk.Button(win, bd=5, bg='#89CFF0', text="LED ON", command=blueLED)
blueBtn.grid(column=1, row=3)

redBtn = tk.Button(win, bd=5, bg='red', text="LED ON", command=redLED)
redBtn.grid(column=2, row=3)

aboutBtn = tk.Button(win, text="About", command=aboutMsg)
aboutBtn.grid(column=1, row=4)

quitBtn = tk.Button(win, text="Quit", command=win.quit)
quitBtn.grid(column=2, row=4)
#--------------------------------------------
win.mainloop()