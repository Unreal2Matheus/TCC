# Python3 script se conectando ao PostgreSQL e salvando as informações publicadas no servidor mqtt do CLOUD MQTT

#Declara as bibliotecas a serem utilizadas

from datetime import datetime
import psycopg2 as pg2
import paho.mqtt.client as mqtt
import json
# instancia o banco de dados 
db = pg2.connect( user="postgres",password="pir2quadrado", database="postgres")
cursor = db.cursor()

# dados de entrada para a conexão em MQTT
broker_address = "farmer.cloudmqtt.com"  # Broker address
port = 14098  # Broker port
user = "zfdpgatg"  # Connection username
password = "QqNg-ir0-N_M"  # Connection password


# A função callback para quando o servidor MQTT for Conectado , ela ja esta subscrevendo no topico 

def on_connect(client, userdata, flags, rc):
    # Print result of connection attempt
    print("Connected with result code "+str(rc))
# se inscreve no topico spot balança
    client.subscribe("spot/Balanca/#")


# O callback de quando uma mensagem é publicada dentro do servidor .
def on_message(client, userdata, msg):
  
    # os valores a serem escritos dentro da tabela sensordata 
    # nesse caso serão o horario da leitura do peso , a leitura e o tipo de cerveja 
    now = datetime.now()
    formatted_date = now.strftime('%Y-%m-%d %H:%M:%S')
    payload = json.loads(msg.payload.decode('utf-8'))
    peso = float(payload["peso"])
    cerveja = payload["cerveja"]
    
    print("Peso: "+str(peso))
    print("Tipo da cerveja: "+str(cerveja))
    print("DateTime: "+str(formatted_date))
    
    cur = db.cursor()
    # faz uma Query que insere os dados recebidos pelo topico MQTT no banco
    postgres_insert_query = """ INSERT INTO sensordata (peso, cerveja, timestamp) VALUES (%s,%s,%s)"""
    record_to_insert = (peso,cerveja,formatted_date)
    cur.execute(postgres_insert_query, record_to_insert)
    db.commit()
    print("data received and imported in MySQL")


# realiza a conexão do MQTT e mantem ela em loop 
client = mqtt.Client("servidor_mqtt")
client.username_pw_set(username=user, password=password)
client.on_connect = on_connect  # define a função de callback de conexão com sucesso
client.on_message = on_message  # define a função de callback de mensagem publicada
client.connect(host=broker_address, port=port)  # conecta ao broker
client.loop_forever()  # Start networking daemon
