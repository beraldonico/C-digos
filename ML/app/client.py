import requests
  
# api-endpoint
#192.168.0.211:8000/action?heater=off&AC=off&light=off&humidifier=off&ventilation=off&irrigation=off
URL = "http://192.168.0.211:8000/action"
def send_action(action):
    # defining a params dict for the parameters to be sent to the API
    PARAMS = { "heater": convert_action_to_server(action["heater"]),
                "AC": convert_action_to_server(action["AC"]),
                "light": convert_action_to_server(action["light"]),
                "humidifier": convert_action_to_server(action["humidifier"]),
                "ventilation": convert_action_to_server(action["ventilation"]),
                "irrigation": convert_action_to_server(action["irrigation"])
    }
    # sending get request and saving the response as response object
    try:
        r = requests.get(url = URL, params = PARAMS, timeout=5)
        print(f"GET sended: {r.url}")
    except requests.exceptions.InvalidSchema:
        print(f"Incapable to connect to API endpoint")
    except requests.exceptions.Timeout:
        print(f"Timeout to recieve response")
    except Exception as ex:
        print(f"Other Error msg: {ex}")

def convert_action_to_server(action):
    if action > 0.8:
        return "on"
    else:
        return "off"

if __name__ == "__main__":
    action = {"heater": 0, "AC": 0, "light": 0, "humidifier": 0, "ventilation": 0, "irrigation": 0}
    send_action(action)