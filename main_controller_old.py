import serial
import tweepy
import time
import smtplib
from datetime import datetime

first_contact = False # First contact the arduino

cereal_data = serial.Serial("/dev/ttyACM0",9600, timeout=1) #Connect to Arduino via USB on Serial 9600
cereal_data.bytesize=serial.EIGHTBITS
cereal_data.parity=serial.PARITY_NONE
cereal_data.stopbits=serial.STOPBITS_ONE
cereal_data.xonxoff=False
cereal_data.rtscts=False
cereal_data.dsrdtr=False

day = 8

data_matrix = [[], #Time
               [], #Main Temp
               [], #Temp 2
               [], #Humidity
               [], #Water Depth
               ]

#TWITTER STUFF
def get_api(cfg):
  auth = tweepy.OAuthHandler(cfg['consumer_key'], cfg['consumer_secret'])
  auth.set_access_token(cfg['access_token'], cfg['access_token_secret'])
  return tweepy.API(auth)

def main(txt):
  # Fill in the values noted in previous step here
  cfg = {
    "consumer_key"        : "3D7nE3I2C2z5P4vzZfzLcYyPS",
    "consumer_secret"     : "pSlGOEUElWliGS42i0UhSUAfgixUBamHZkXRB0L6zVwtxfgqQS",
    "access_token"        : "879762965007814656-OEJ36590PYGYdcRV22pOMnDFcjOkWq1",
    "access_token_secret" : "1TxsHiOt5GHaGp710xULkkJOog8arw0ZbncQAx6Fg002k"
    }
  api = get_api(cfg)
  tweet = txt
  status = api.update_status(status=tweet)
  if __name__ == "__main__":
    main()

#EMAIL STUFF
def emailMsg(msg):
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login("digitalfooddata@gmail.com", "digitalfooddata7")
    server.sendmail("digitalfooddata@gmail.com", "digitalfooddata@gmail.com", msg)
    server.quit()

#GET TIME
def getTimeDecimal():
    cur_time = datetime.now()
    return cur_time.month*1000000+cur_time.day*10000+cur_time.hour*100+cur_time.minute


#MAIN ---> WHAT IT WILL RUN
try: #will try to open data from the output file
    row = 0
    text_file = open("Output.txt", "r")

    for row in range(0,5): #FIVE ROWS
        text_split = text_file.readline().split(",")
        for num in text_split:
            data_matrix[row].append(int(num)) # RELOADS INTO DATA MATRIX
            
    day = text_file.readline(6) # STORE DAYS
    
    print("Finish reading file")
    
except IOError:
    print("Output file not found, created one")
    text_file = open("Output.txt", "w")
    text_file.close()

finally:
    serial_data_Array = []
    go = False # STARTS COMMUNICATING WITH THE ARDUINO
    inByte = cereal_data.read() # Gets data from arduino
    if not first_contact : #If connection isn't estb, estb it
        print(inByte); # SHOULD BE "A"
        first_contact = True
        cur_time = getTimeDecimal() # Get current time
        #writes time back to arduino
        datadate = str(cur_time); #converts it to string
        while(not go):
            cereal_data.write(datadate+"\n"+str(day)+"\n") #Send the date time
            data = cereal_data.read()
            if data != "A" and data !="":
                time.sleep(2)
                go = True
                #main("I just rebooted! Keep Calm and Grow On!")
                sm = "I just rebooted! Lettuce grow some more! This is day "+ str(day)
                emailMsg(sm)
                cereal_data.flushInput()
                cereal_data.flushOutput()
                cereal_data.flush()
                break
        while 1: # Infinite Loop
            if go:
                received_data = cereal_data.readline()
                print(received_data)
                if received_data != "A" and received_data != "":
                    num_array = [0,0,0,0,0]
                    try:
                        num_array = [int(num) for num in received_data.split(".")] # Turns it into a string
                        if num_array[4] == "" or "0":
                          print("FAILURE")
                        print(num_array)
                    except: # Weird negative value exception
                        print("Weird negative value")
                        print(num_array)

                    text_file = open("Output.txt", "w") #Opens data file

                    data_matrix[0].append(getTimeDecimal())
                    text_file.write(",".join(str(e) for e in data_matrix[0])+"\n")

                    for row in range(0,4):
                        data_matrix[row].append(num_array[row-1])
                        text_file.write(",".join(str(e) for e in data_matrix[row+1])+"\n") #adds it into the textfile

                    day = num[len(num)-1]

                    text_file.close()
                    
                    #print(data_matrix)
            
                cereal_data.write(str(day)) # Will stimulate handshake
