import urllib.request
import json

print("vliegtuigen")

with urllib.request.urlopen("https://ipwho.is/", timeout=10) as antwoord:
    locatie = json.load(antwoord)

if locatie["success"]:
    print("Geschatte plaats:", locatie["city"])
else:
    print("Locatie ophalen mislukt.")

breedtegraad = 52.38
lengtegraad = 4.82
straal = 25

print("Zoekgebied: omgeving Slotermeer, Amsterdam")


url = f"https://api.adsb.lol/v2/lat/{breedtegraad}/lon/{lengtegraad}/dist/{straal}"

print(url)

with urllib.request.urlopen(url, timeout=10) as antwoord:
    gegevens = json.load(antwoord)

vliegtuigen  = gegevens.get("ac", [])

print("aantal gevonden vliegtuigen:", len(vliegtuigen))
