import urllib.request
import json

print("vliegtuigen")

with urllib.request.urlopen("https://ipwho.is/", timeout=10) as antwoord:
    locatie = json.load(antwoord)

if locatie["success"]:
    print("Geschatte plaats:", locatie["city"])
else:
    print("Locatie ophalen mislukt.")