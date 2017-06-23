import serial
from datetime import datetime

cereal_data = serial.Serial('/dev/ttyACM0',9600) #Connect to Arduino via USB on Serial 9600

data_matrix = [[], #Time
               [], #Main Temp
               [], #Temp 2
               [], #Humidity
               [], #Water Depth
               [], #pH
               ]

try: #will try to add data to the output file
    text_file = open("Output.txt", "r")
    text_split = text_file.readline().split(",")
    for x in text_split:
        temp.append(int(x))
    print(temp)
except FileNotFoundError:
    print("Output file not found, created one")
    text_file = open("Output.txt", "w")
    text_file.close()
finally:
    while 1:
        arduinoData = cereal_data.readline()
        splitData = arduinoData.spit(",")
        #    Write code for GETTING ARRAY DATA
        text_file = open("Output.txt", "w")
        data_matrix[0].append(datetime.month*100+datetime.day)
        text_file.write(",".join(str(e) for e in data_matrix[0]))
        for row in range(len(data_matrix)-1):
            data_matrix[row+1].append(int(splitData[row]));
            text_file.write(",".join(str(e) for e in data_matrix[row]))
        text_file.close()
        print(data_matrix)
