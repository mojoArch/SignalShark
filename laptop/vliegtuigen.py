import urllib.request
import urllib.error
import json


print(r"""
                 __|__
          -------(_)-------
                  / \

       S I G N A L S H A R K
          Vliegtuigtracker
""")

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

for vliegtuig in vliegtuigen:
    roepnaam = vliegtuig.get("flight",  "").strip()
    
    if not roepnaam:
        roepnaam = "onbekend"
      

    vliegtuigtype = vliegtuig.get("t") or "onbekend"
    registratie = vliegtuig.get("r") or "onbekend"
    hoogte = vliegtuig.get("alt_baro")

    if hoogte == "ground":
        hoogteTekst = "geland"
    elif hoogte is None:
        hoogteTekst = "onbekend"
    else:
        hoogteKm = hoogte * 0.0003048 
        hoogteTekst = f"{hoogteKm:.2f} km"
    snelheid = vliegtuig.get("gs")

    if snelheid is None:
        snelheidTekst = "onbekend"
    else:
        snelheidKmH = snelheid * 1.852
        snelheidTekst = f"{snelheidKmH:.0f} km/u"

    afstand = vliegtuig.get("dst")
    if afstand is None:
        afstandTekst = "onbekend"
    else: 
        afstandKm = afstand * 1.852
        afstandTekst = f"{afstandKm:.1f} km"

    richting = vliegtuig.get("track")
    if richting is None:
        richtingTekst = "onbekend"
    else: 
        richtingTekst = f"{richting:.0f}"
        

if vliegtuigen:
    eersteVliegtuig = vliegtuigen[0]
    roepnaam = eersteVliegtuig.get("flight", "").strip()

    if roepnaam:
        routeUrl = f"https://api.adsbdb.com/v0/callsign/{roepnaam}"
        try:
            with urllib.request.urlopen(routeUrl, timeout=10) as routeAntwoord:
                routeGegevens = json.load(routeAntwoord)

            route = routeGegevens.get("response", {}).get("flightroute")

            if route:
                vertrek = route.get("origin", {}).get("name", "onbekend")
                bestemming = route.get("destination", {}).get("name", "onbekend")
                print("Route:", vertrek, "->", bestemming)
            else:
                print("geen routegegevens gevonden:(")
            
        except urllib.error.HTTPError:
            print("geen routgegevens voor", roepnaam)

    print(f"{roepnaam:<12} | Type: {vliegtuigtype:<8} | Registratie: {registratie:<10} | Hoogte: {hoogteTekst} | Snelheid: {snelheidTekst} | Afstand: {afstandTekst} | Richting: {richtingTekst}°")


