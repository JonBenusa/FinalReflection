import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO
import serial

#configure pins for bluetooth module
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(4, GPIO.OUT)
GPIO.setup(9, GPIO.IN)

#configure pins for uart connection with STM32
GPIO.setup(0, GPIO.OUT)
GPIO.setup(5, GPIO.IN)
#configure serial settings for uart
#bluetooth = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=5)

#configure serial settings for bluetooth
bluetooth = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=5)
#ensure that there isn't any old connections or data from a previous connection
bluetooth.close()
bluetooth.open()
bluetooth.flushInput()

#function for handling the data
def bluetoothData():
    if bluetooth.inWaiting()==0:
        line = bluetooth.readline().decode('utf-8').rstrip()
        print(line)



def on_connect(client, userdata, flags, rc):
    print("Connected with result code " +str(rc))
    client.subscribe("/esp8266/temp")

def on_message(client, userdata, message):
    print(str(message.payload)+ " received on topic " +str(message.topic))


def main():
    mqtt_client = mqtt.Client()
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect('localhost', 1883, 60)

    mqtt_client.loop_start()

    message = "Testing message!\n"
    bluetooth.write(message.encode())
    bluetoothData()

if __name__ == '__main__':
    print('MQTT to InfluxDGB bridge')
    main()