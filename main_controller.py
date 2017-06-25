import serial
import time
from datetime import datetime

first_contact = False

cereal_data = serial.Serial("/dev/ttyACM0",9600, timeout=1) #Connect to Arduino via USB on Serial 9600
cereal_data.bytesize=serial.EIGHTBITS
cereal_data.parity=serial.PARITY_NONE
cereal_data.stopbits=serial.STOPBITS_ONE
cereal_data.xonxoff=False
cereal_data.rtscts=False
cereal_data.dsrdtr=False
day = 3

data_matrix = [[], #Time
               [], #Main Temp
               [], #Temp 2
               [], #Humidity
               [], #Water Depth
               ]
def getTimeDecimal():
    cur_time = datetime.now()
    return cur_time.month*1000000+cur_time.day*10000+cur_time.hour*100+cur_time.minute

try: #will try to add data to the output file
    row = 0
    text_file = open("Output.txt", "r")

    for row in range(0,5):
        text_split = text_file.readline().split(",")
        for num in text_split:
            data_matrix[row].append(int(num))
            
    day = text_file.readline(6)
    
    print("Finish reading file")
    
except IOError:
    print("Output file not found, created one")
    text_file = open("Output.txt", "w")
    text_file.close()

finally:
    serial_data_Array = []
    go = False
    inByte = cereal_data.read()
    if not first_contact : #If connection isn't estb, estb it
        print(inByte);
        first_contact = True
        cur_time = getTimeDecimal()
        #writes time back to arduino
        datadate = str(cur_time);
        while(not go):
            cereal_data.write(datadate+"\n"+str(day)+"\n") #Send the date time
            data = cereal_data.read()
            if data != "A" and data !="":
                time.sleep(2)
                go = True
                cereal_data.flushInput()
                cereal_data.flushOutput()
                cereal_data.flush()
                break
        while 1:
            if go:
                received_data = cereal_data.readline()

                if received_data != "A" and received_data != "":
                    num_array = [int(num) for num in received_data.split(".")] # Turns it into a string
                    text_file = open("Output.txt", "w") #Opens data file

                    data_matrix[0].append(getTimeDecimal())
                    text_file.write(",".join(str(e) for e in data_matrix[0])+"\n")

                    for row in range(0,4):
                        data_matrix[row+1].append(num_array[row])
                        text_file.write(",".join(str(e) for e in data_matrix[row+1])+"\n") #adds it into the textfile

                    day = num[len(num)-1]
                    text_file.write(day) #Write the number of days

                    text_file.close()
                    
                    print(data_matrix)
            
                cereal_data.write(str(day)) # Will stimulate handshake
        
