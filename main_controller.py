import serial
import tweepy
import time
import smtplib
from datetime import datetime

prevTime = 0;
curTime = 0;

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

def tweetThis(txt):
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

#EMAIL STUFF
def emailMsg(msg):
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login("digitalfooddata@gmail.com", "digitalfooddata7")
    server.sendmail("digitalfooddata@gmail.com", "digitalfooddata@gmail.com", msg)
    server.quit()

def sendEmail(data):
  
  msg="Temp: "+str(data[0])+"  Humidity: "+str(data[2])+"  Water Depth: "+str(data[3])+" Today is day "+str(data[5]);
  try: 
    emailMsg(msg)
  except:
    print("Sending update email! NO INTERNET!")

def sendTweet(data):
  try: 
    tweetThis("Temp: "+str(data[0])+" F\nHumidity: "+str(data[2])+"\nWater Depth Reading: "+str(data[3])+"\nToday is day "+str(data[5]))
  except:
    print("Tweeting failed! NO INTERNET!")
    
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
##    print(inByte)
##    print(cereal_data)
##    print(cereal_data)
    if not first_contact : #If connection isn't estb, estb it
        print(inByte); # SHOULD BE "A"
        first_contact = True
        cur_time = getTimeDecimal() # Get current time
        #writes time back to arduino
        datadate = str(cur_time); #converts it to string
        print(cereal_data)
        while(not go):
            cereal_data.write(datadate+"\n"+str(day)+"\n") #Send the date time
            data = cereal_data.read()
            
            if data != "A" and data !="":
                time.sleep(2)
                go = True
                sm = "I just rebooted! Lettuce grow some more! This is day "+str(day)
                try: 
                  emailMsg(sm)
                  tweetThis("I just rebooted! It is day "+str(day)+". Keep Calm and Grow On!")
                except:
                  print("NO INTERNET!")
                cereal_data.flushInput()
                cereal_data.flushOutput()
                cereal_data.flush()
                prevTime = datetime.now().minute;
                print(prevTime);
                break
        while 1: # Infinite Loop
            if go:
                received_data = cereal_data.readline()
                print(received_data)
                if received_data != "A" and received_data != "":
                    num_array = [0,0,0,0,0]
                    try:
                        num_array = [int(num) for num in received_data.split(".")] # Turns it into a string
                    except: # Weird negative value exception
                        print("Weird negative value")

                    text_file = open("Output.txt", "w") #Opens data file

                    data_matrix[0].append(getTimeDecimal())
                    text_file.write(",".join(str(e) for e in data_matrix[0])+"\n")

                    for row in range(0,4):
                      data_matrix[row+1].append(num_array[row])
                      text_file.write(",".join(str(e) for e in data_matrix[row+1])+"\n") #adds it into the textfile

                    day = num_array[len(num_array)-1]
                    text_file.write(str(day))

                    text_file.close()
                    
                    print(num_array)
                    curTime = datetime.now().minute;
                    if(abs(curTime-prevTime)>=10):
                      sendEmail(num_array);
                      sendTweet(num_array);
                      prevTime = curTime;
                    time.sleep(.2); # One minute

            
                cereal_data.write(str(day)) # Will stimulate handshake
