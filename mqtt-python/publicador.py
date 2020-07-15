import paho.mqtt.client as mqtt

client = mqtt.Client()
client.connect("51.210.110.0", 1883, 60)
while 1:
    canal = input("Canal: ")
    mensagem = input("Mensagem: ")
    client.publish(canal, mensagem)