import serial
import time
from datetime import datetime

first_contact = False
serial_data_Array = []
serial_count = 0
cereal_data = serial.Serial('/dev/ttyACM0',9600) #Connect to Arduino via USB on Serial 9600
day = 0

data_matrix = [[], #Time
               [], #Main Temp
               [], #Temp 2
               [], #Humidity
               [], #Water Depth
               ]
def getTimeDecimal():
    cur_time = datetime.now()
    return cur_time.month*100+cur_time.day+cur_time.hour/100+cur_time.minute/10000

try: #will try to add data to the output file
    row = 0
    text_file = open("Output.txt", "r")

    for line in range(1,5):
        text_split = text_file.readline(line).split(",")
        for num in text_split:
            data_matrix[line].append(int(num))

        print(data_matrix[line])
        row += 1
    day = text_file.readline(6)

except FileNotFoundError:
    print("Output file not found, created one")
    text_file = open("Output.txt", "w")
    text_file.close()

finally:
    inByte = cereal_data.readline()
    if not first_contact : #If connection isn't estb, estb it
        if inByte == "A" :
            first_contact = True
            cereal_data.flush() #clear serial data
            cur_time = datetime.now()
            #writes time back to arduino
            cereal_data.write(getTimeDecimal())
    else:
        while True:
            if(cereal_data.in_waiting > 0):
                serial_data_Array.append(inByte) #will store each byte into array
                serial_count+=1 #Increment #
                if(serial_count>4): #If there is five data bytes received
                    text_file = open("Output.txt", "w") #Opens data file

                    #Add current daytime to data matrix MonthMonthDayDay.HrHrMinMin
                    data_matrix[0].append(getTimeDecimal())

                    #Join current data into one string and save in file
                    text_file.write(",".join(str(e) for e in data_matrix[0]))

                    for row in range(len(data_matrix)-1): #doing row - 1 because date row has already been done
                        data_matrix[row+1].append(int(serial_data_Array[row])) #adds in new data in row
                        text_file.write(",".join(str(e) for e in data_matrix[row+1])) #adds it into the textfile

                    day = serial_data_Array[len(serial_data_Array)-1]
                    text_file.write(day) #Write the number of days

                    text_file.close()
                    print(data_matrix)

                    serial_count = 0 #Resets to get data
                    serial_data_Array = []

            cereal_data.write(day) # Will stimulate handshake
            time.sleep(1);
