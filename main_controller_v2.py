import serial
import tweepy
import time
import smtplib
import subprocess
import picamera
import os

from datetime import datetime
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email.MIMEMultipart import MIMEMultipart
from os.path import basename
from email import encoders
from email.utils import COMMASPACE, formatdate

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

day = 11

data_matrix = [
               [], #Main Temp - 0
               [], #Ignore - 1
               [], #Humidity - 2
               [], #Water Depth - 3
               [], #Day - 4
               ]

  #TWITTER STUFF
def get_api(cfg):
  auth = tweepy.OAuthHandler(cfg['consumer_key'], cfg['consumer_secret'])
  auth.set_access_token(cfg['access_token'], cfg['access_token_secret'])
  return tweepy.API(auth)

def tweetThis(txt,picFile):
  # Fill in the values noted in previous step here
  cfg = {
    "consumer_key"        : "3D7nE3I2C2z5P4vzZfzLcYyPS",
    "consumer_secret"     : "pSlGOEUElWliGS42i0UhSUAfgixUBamHZkXRB0L6zVwtxfgqQS",
    "access_token"        : "879762965007814656-OEJ36590PYGYdcRV22pOMnDFcjOkWq1",
    "access_token_secret" : "1TxsHiOt5GHaGp710xULkkJOog8arw0ZbncQAx6Fg002k"
    }
  api = get_api(cfg)
  d = datetime.now().strftime('%Y/%m/%d %H:%M:%S');
  prepend = "Auto-Tweet from Digital Food: " + str(d) + "\n"
  tweet = prepend+txt
  #status = api.update_status(status=tweet)
  status = api.update_with_media(picFile, status=tweet)



#EMAIL STUFF
def emailMsg(msg,dataFileName):
    d = datetime.now().strftime('%Y/%m/%d %H:%M:%S');
    subj = "Auto-Email from Digital Food: " + str(d) + "\n"
    
    em = MIMEMultipart()
    em['Subject']=subj
    em['From']="digitalfooddata@gmail.com"
    em['To']="digitalfooddata@gmail.com"
    
    body = msg
    em.attach(MIMEText(msg,'plain'))
    attachment = open(dataFileName,"rb");

    part = MIMEBase('application','octet-stream')
    part.set_payload((attachment).read())
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', "attachment; filename=%s" % dataFileName)
    em.attach(part)
    
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login("digitalfooddata@gmail.com", "digitalfooddata7")
    server.sendmail("digitalfooddata@gmail.com", "digitalfooddata@gmail.com", em.as_string())
    server.quit()

def sendEmail(data,attachFileNM):
  try:
    msg = "Temp: "+str(data[0])+"\nHumidity: "+str(data[2])+"\nWater Depth Reading: "+str(data[3])+"\nToday is day "+str(data[4])
    emailMsg(msg,attachFileNM)
  except:
    print("Sending update email! NO INTERNET!")
    

def sendTweet(data,fileNM):
  try:
    msg = "Temp: "+str(data[0])+"\nHumidity: "+str(data[2])+"\nWater Depth Reading: "+str(data[3])+"\nToday is day "+str(data[4])
    tweetThis(msg,fileNM)
  except:
    print("Tweeting failed! NO INTERNET!")

def takePic(outputFile):
    try:
        print("Taking picture...")
        with picamera.PiCamera() as camera:
            camera.resolution = (1920,1200)
            camera.capture(outputFile);

        print("Successfully taken pic..")
    except:
        print("Couldn't take picture...")

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
    
    cur_time = getTimeDecimal() # Get current time
    prev_time = getTimeDecimal() # Get current time
    
    if not first_contact : #If connection isn't estb, estb it
        print(inByte); # SHOULD BE "A"
        first_contact = True
        
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
                try:
                  #emailMsg(sm)
                  tweetThis(sm)
                except:
                    print("NO INTERNET!")
                cereal_data.flushInput()
                cereal_data.flushOutput()
                cereal_data.flush()
                #prevTime = datetime.now().minute;
                #print(prevTime);
                break
        while 1: # Infinite Loop
            if go:
                received_data = cereal_data.readline()
                #print(received_data[1])
                if received_data != "A" and received_data != "":   
                    num_array = [0,0,0,0,0]
                    try:
                        #num_array = [int(num) for num in received_data.split(".")] # Turns it into a string
                        n_a = received_data.strip('\r\n')
                        num_array_tmp = n_a.split('\t')

                        num_array = list(map(float, num_array_tmp))
                        
                        print(num_array)
##                        if num_array[4] == "" or "0":
##                          print("FAILURE")
                    except: # Weird negative value exception
                        print("Weird negative value")

                    text_file = open("Output.txt", "w") #Opens data file

                    data_matrix[0].append(getTimeDecimal())
                    text_file.write(",".join(str(e) for e in data_matrix[0])+"\n")

                    for row in range(0,4):
                        data_matrix[row+1].append(num_array[row])
                        text_file.write(",".join(str(e) for e in data_matrix[row+1])+"\n") #adds it into the textfile

                    #day = num[len(num)-1]

                    text_file.close()
                    
                    #print(data_matrix)
                    
                    curTime = getTimeDecimal();
##                    print("CurrentTime = "+str(curTime))
##                    print("PrevTime = "+str(prevTime))
##                    print("Delta = "+str(abs(curTime-prevTime)))
                    if(abs(curTime-prevTime)>=15):
                        print("Starting Notifictions...\n")
                        print(num_array)
                        print(curTime)
                        picFileNM = "/home/pi/Pictures/" + str(curTime)+str(".jpeg");
                        
                        print(picFileNM)
                        takePic(picFileNM);
                        prevTime = curTime;
                        
                        msg = received_data
                        print(msg)
                        #+" Humidity: "+str(num_array[2])+" Water Depth Reading: "+str(num_array[3])+" Today is day: "+str(num_array[4])
                        #sendEmail(num_array)
                        emailMsg(msg,picFileNM)
                        sendTweet(num_array,picFileNM);
                        

                        time.sleep(.2); # One minute
            
                cereal_data.write(str(day)) # Will stimulate handshake
