import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Conectado com sucesso!")

def on_message(client, userdata, msg):
    print(str(msg.topic) + ": " + str(msg.payload))
    if msg.payload.decode("utf-8") == "cao":
        client.publisher("IOT","Cocheto e Lucas caozeiro")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("51.210.110.0", 1883, 60)
client.subscribe("IOT")
client.subscribe("PYTHON")
client.loop_forever()
