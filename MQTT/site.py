# Python3 script to connect to MQTT, read values and write them into MySQL
#
# B. Duijnhouwer
# June, 8th 2020
#
# version: 1.0
#
#
from datetime import datetime
import psycopg2 as pg2
import paho.mqtt.client as mqtt
import json

db = pg2.connect( user="postgres",
                     password="pir2quadrado", database="postgres")
cursor = db.cursor()

broker_address = "farmer.cloudmqtt.com"  # Broker address
port = 14098  # Broker port
user = "zfdpgatg"  # Connection username
password = "QqNg-ir0-N_M"  # Connection password


# The callback for when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    # Print result of connection attempt
    print("Connected with result code {0}".format(str(rc)))
    client.subscribe("spot/Balanca/#")


# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    cursor.execute("select * from sensordata")
    

    now = datetime.now()
    formatted_date = now.strftime('%Y-%m-%d %H:%M:%S')

    payload = json.loads(msg.payload.decode('utf-8'))
   
    peso = float(payload["peso"])
    cerveja = payload["cerveja"]
    print("Peso: "+str(peso))
    print("Tipo da cerveja: "+str(cerveja))
    print("DateTime: "+str(formatted_date))
    
    cur = db.cursor()
    postgres_insert_query = """ INSERT INTO sensordata (peso, cerveja, timestamp) VALUES (%s,%s,%s)"""
    record_to_insert = (peso,cerveja,formatted_date)
    cur.execute(postgres_insert_query, record_to_insert)
    db.commit()
    print("data received and imported in MySQL")



client = mqtt.Client("servidor_mqtt")
client.username_pw_set(user, password=password)
client.on_connect = on_connect  # Define callback function for successful connection
client.on_message = on_message  # Define callback function for receipt of a message
client.connect(broker_address, port=port)  # connect to broker
client.loop_forever()  # Start networking daemon
