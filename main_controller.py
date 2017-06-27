import serial
import tweepy
import time
import smtplib
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

#TWITTER STUFF
def get_api(cfg):
  auth = tweepy.OAuthHandler(cfg['consumer_key'], cfg['consumer_secret'])
  auth.set_access_token(cfg['access_token'], cfg['access_token_secret'])
  return tweepy.API(auth)

def main():
  # Fill in the values noted in previous step here
  cfg = {
    "consumer_key"        : "3D7nE3I2C2z5P4vzZfzLcYyPS",
    "consumer_secret"     : "pSlGOEUElWliGS42i0UhSUAfgixUBamHZkXRB0L6zVwtxfgqQS",
    "access_token"        : "879762965007814656-OEJ36590PYGYdcRV22pOMnDFcjOkWq1",
    "access_token_secret" : "1TxsHiOt5GHaGp710xULkkJOog8arw0ZbncQAx6Fg002k"
    }

def tweetThis(txt):
    api = get_api(cfg)
    tweet = txt
    status = api.update_status(status=tweet)
    # Yes, tweet is called 'status' rather confusing
    if __name__ == "__main__":
        main()

def emailMsg(msg):
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login("digitalfooddata@gmail.com", "digitalfooddata7")
    server.sendmail("digitalfooddata@gmail.com", "digitalfooddata@gmail.com", msg)
    server.quit()

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
                tweetThis("I just rebooted! Keep Calm and Grow On!")
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

                    text_file.close()
                    
                    print(data_matrix)
            
                cereal_data.write(str(day)) # Will stimulate handshake
        
