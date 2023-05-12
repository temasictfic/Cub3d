#!/usr/bin/python3

################################################################################
# wta & awoimbee | Cub3D Map Generator                                        #
################################################################################

import tkinter as tk
import sys, os, time
import random

class Player:
    def __init__(self, isSet=False, pos=(0, 0)):
        self.isSet = isSet
        self.pos = pos

def display():
    "Display an array in the canvas from the list"
    global board

    #Delete all cells
    canvas.delete("cell")

    #Coordinates in the canvas used to place the squares
    x, y = 0, 0
    #Path the table up and down
    for row in range(len(board)):
        for column in range(len(board[0])):
            if board[row][column] == 'C':
                canvas.create_rectangle(
                    x,
                    y,
                    x+caseSize,
                    y+caseSize,
                    fill="yellow",
                    tag="cell",
                    outline="grey"
                )
            elif board[row][column] == 1:
                canvas.create_rectangle(
                    x,
                    y,
                    x+caseSize,
                    y+caseSize,
                    fill="black",
                    tag="cell",
                    outline="grey"
                )
            elif board[row][column] == 64:
                canvas.create_rectangle(
                    x,
                    y,
                    x+caseSize,
                    y+caseSize,
                    fill="cyan",
                    tag="cell",
                    outline="grey"
                )
            elif board[row][column] == 2:
                canvas.create_rectangle(
                    x,
                    y,
                    x+caseSize,
                    y+caseSize,
                    fill="red",
                    tag="cell",
                    outline="grey"
                )
            elif board[row][column] == 3:
                canvas.create_rectangle(
                    x,
                    y,
                    x+caseSize,
                    y+caseSize,
                    fill="green",
                    tag="cell",
                    outline="grey"
                )
            x += caseSize
            if x >= mapWidth*caseSize:
                x = 0
        y += caseSize

def is_not_border(x, y):
    return 0 < y < mapHeight - 1 and 0 < x < mapWidth - 1

def is_prev_wall(board, x, y):
    if x-1 >= 0 and x + 1 < mapWidth:
        return(not(board[y][x-1] == 2 or board[y][x-1] == 3))
    return (1)

def placeThing(event):
    ## canvas coordinates -> last_dragboard coordinates
    event.x //= caseSize
    event.y //= caseSize

    if event.state != 0:
        if placeThing.lastDrag == (event.x, event.y, event.state):
            return
        else:
            placeThing.lastDrag = (event.x, event.y, event.state)
    #https://anzeljg.github.io/rin2/book2/2405/docs/tkinter/event-handlers.html
    if is_not_border(event.x, event.y):
        isPlayerLoc = board[event.y][event.x] == 64
        ## Control and Left Click => COLLECTIBLE
        if event.state == 4 and event.num == 1:
            board[event.y][event.x] = 'C'
        ## Left Click => WALL
        elif event.state == 256 or event.num == 1:
            if isPlayerLoc:
                player.isSet = False
            board[event.y][event.x] = int(not board[event.y][event.x])
        ## Shift and Right Click  => OPEN_DOOR
        elif event.state == 1 and event.num == 2:
                board[event.y][event.x] = 3
        ## Right Click  => CLOSED_DOOR
        elif event.state == 512 or event.num == 2:
            if board[event.y][event.x] == 2:
                board[event.y][event.x] = 1
            else:
                board[event.y][event.x] = 2
        ## Shift and Left Click  => PLAYER
        elif event.num == 3 or event.state == 1024:
            ## Mid click
            if not isPlayerLoc:
                board[event.y][event.x] = 64
                if player.isSet:
                    board[player.pos[1]][player.pos[0]] = 0
                player.isSet = True
                player.pos = (event.x, event.y)
            else:
                board[event.y][event.x] = 0
                player.isSet = False
    #Display
    display()
placeThing.lastDrag = -1


def clearAll():
    "Delete all cells"
    global board, player
    #Re-initializing steps
    board = [[0 if is_not_border(i, j) else 1 for i in range(mapWidth)] for j in range(mapHeight)]
    player.isSet = False
    #Display
    display()

def texturesTxt():
    path = os.curdir
    path += "/textures/"
    dirlist = os.listdir(path)
    NO = [d for d in dirlist if d.startswith('wall_north')]
    SO = [d for d in dirlist if d.startswith('wall_south')]
    WE = [d for d in dirlist if d.startswith('wall_west')]
    EA = [d for d in dirlist if d.startswith('wall_east')]
    CO = [d for d in dirlist if d.startswith('coin')]
    DO = [d for d in dirlist if d.startswith('door')]
    dic = {'NO': NO, 'SO': SO, 'WE': WE, 'EA': EA, 'CO': CO, 'DO': DO}
    string = ""
    for key, value in dic.items():
        string += key + " "
        for v in value:
            string += path + v + " "
        string += "\n"
    string += "F 116,84,20" + "\n"
    string += "C 135,206,235" + "\n"
    return(string)

def saveFile():
    named_tuple = time.localtime() # get struct_time
    time_string = time.strftime("%m.%d.%Y_%H:%M:%S", named_tuple)
    if player.isSet:
        mapFile = open("./map" + time_string + ".cub" , "w")
        mapFile.write(texturesTxt() + "\n")
        #Path the table up and down
        for row, _ in enumerate(board):
            for column, _ in enumerate(board[0]):
                #Only trace if the square is alive
                if board[row][column] == 1:
                    mapFile.write("1")
                elif board[row][column] == 2:
                    mapFile.write("2")
                elif board[row][column] == 3:
                    mapFile.write("3")
                elif board[row][column] == 64:
                    mapFile.write(random.choice("NSWE"))
                elif board[row][column] == 'C':
                    mapFile.write("C")
                else:
                    mapFile.write("0")
            mapFile.write("\n")
        mapFile.close()
        print("You can now run:\n\t./cub3d map.cub")
        root.destroy()
    else:
        errorMsg.set("You need to set the spawn point!")


def setMapSize():
    global askWin, mapWidth, mapHeight

    tmpW = int(askSize.e_w.get())
    tmpH = int(askSize.e_h.get())
    if 4 < tmpW <= 400 and 4 < tmpH <= 400:
        mapWidth = tmpW
        mapHeight = tmpH
        askWin.destroy()
    else:
        print("Bad dimensions !")

def askSize():
    global askWin
    askWin = tk.Tk()
    askWin.title("What size?[4-400]")
    #Added 2 input fields to the window
    askSize.e_w = tk.Entry(askWin)
    askSize.e_w.grid(row=1, column=1, padx=3, pady=3)
    askSize.e_h = tk.Entry(askWin)
    askSize.e_h.grid(row=1, column=3, padx=3, pady=3)
    #Adding a button to the window
    ok_button = tk.Button(askWin, text="OK", command=setMapSize)
    askWin.bind("<Return>", setMapSize)
    ok_button.grid(row=2, column=2, padx=3, pady=3)
    askWin.mainloop()

##########################################
#          PROGRAMME PRINCIPAL           #
##########################################

if __name__ == "__main__":
    global mapWidth, mapHeight
    ######## INIT VARS ########
    player = Player()
    if len(sys.argv) != 3:
        print(
            "You can directly specify the width and height:\n"
            "./map_creator.py <width> <height>"
        )
        askSize()
    else:
        mapWidth = int(sys.argv[1])
        mapHeight = int(sys.argv[2])
    if mapWidth < 4 or mapHeight < 4 or mapWidth > 400 or mapHeight > 400:
        print("Invalid map size")
        sys.exit(0)
    caseSize = int(max(-0.15 * max(mapWidth, mapHeight * (16/9)) + 30, 4))
    board = [[0 if is_not_border(i, j) else 1 for i in range(mapWidth)] for j in range(mapHeight)]

    ######## INIT WINDOW ########
    root = tk.Tk()
    root.title("Cub3D map generator")
    root.configure(background="grey")
    ## Board canvas
    canvas = tk.Canvas(
        root,
        width=caseSize*mapWidth,
        height=caseSize*mapHeight,
        bg="white",
        bd=0,
        highlightthickness=0
    )
    canvas.grid(column=1, row=1, padx=2, pady=2, columnspan=100)
    canvas.bind("<Button-1>", placeThing) #Localization of clicks in the canvas3
    canvas.bind("<B1-Motion>", placeThing)
    canvas.bind("<Button-2>", placeThing)
    canvas.bind("<B2-Motion>", placeThing)
    canvas.bind("<Button-3>", placeThing)
    canvas.bind("<B3-Motion>", placeThing)
    ## Buttons frame
    userPart = tk.LabelFrame(
        root,
        bd=2,
        text="User",
        bg="grey",
        fg="white",
        font=("Calibri", 12)
    )
    userPart.grid(column=100, row=2, padx=5, pady=2, sticky=tk.W)
    ### Save button
    saveButton = tk.Button(
        userPart,
        text="Save",
        command=saveFile,
        bg="white",
        fg="#545556",
        relief="flat",
        font=("Calibri", 12)
    )
    saveButton.grid(column=1, row=1, padx=7, pady=5)
    ### Clear button
    clearButton = tk.Button(
        userPart,
        text="Erase everything",
        command=clearAll,
        bg="white",
        fg="#565454",
        relief="flat",
        font=("Calibri", 12)
    )
    clearButton.grid(column=1, row=2, padx=7, pady=5)
    ### Info frame
    devPart = tk.LabelFrame(
        root,
        text="Control+LeftClick = Collectible\nShift+RightClick = OpenDoor\nRightClick = ClosedDoor\nMidClick = Player\nLeftClick=Wall",
        bg="grey",
        fg="white",
        font=("Calibri", 12),
    )
    devPart.grid(column=99, row=2, padx=5, pady=2, sticky=tk.W)
    errorMsg = tk.StringVar()
    errorMsg.set("")
    cDisp1 = tk.Label(devPart, textvariable=errorMsg, bg="grey", fg="red", font=("Calibri", 12))
    cDisp1.grid(column=1, row=1, padx=7, pady=5)
    ## :/
    root.resizable(False, False)
    ## Draw board lines
    for i in range(len(board[0])):
        canvas.create_line(i * caseSize, 0, i * caseSize, mapHeight * caseSize, fill="grey")
    for i in range(len(board)):
        canvas.create_line(0, i * caseSize, mapWidth * caseSize, i * caseSize, fill="grey")
    ## Events loop
    display()
    root.mainloop()
