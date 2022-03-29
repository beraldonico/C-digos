from config import settings
from collections import OrderedDict
import bson
import time
import pymongo

myclient = pymongo.MongoClient(settings.DB_URL)
mydb = myclient[settings.DB_NAME]
myValuescol = mydb[settings.DB_VALUES_COLL]
myHistorycol = mydb[settings.DB_HIST_COLL]

def get_avg():
    aggregate = myValuescol.aggregate([
        {"$sort": {"timestamp": -1}}, #sort to get the last entries
        {"$limit": 12}, #Last 60 seconds of sensors read
        {"$group": {
                    "_id": "null",
                    "Temp": {"$avg":"$Temp"},
                    "RH": {"$avg": "$RH"},
                    "Soil_Moisture": {"$avg": "$Soil_Moisture"},
                    "LUX_Index": {"$avg": "$LUX_Index"},
                    }
        }])
    for doc in aggregate:
        print(f"Average: {doc}")
        return doc

def get_hist():
    aggregate = myHistorycol.aggregate([
        {"$sort": {"timestamp": -1}}, #sort to get the last entries
        {"$limit": 1} #get last entry
        ]) 
    for doc in aggregate:
        print(f"History: {doc}")
        return doc

def save_hist(history):
    try:
        myHistorycol.insert_one(history)
    except bson.InvalidDocument as ex:
        print(f"Document havent been save because schema is broken: {ex}")
    except Exception as ex:
        print(f"Document havent been save: {ex}")

def update_reward(reward):
    document = get_hist()
    where = { 'timestamp': document["timestamp"] }
    newvalues = { "$set": { 'reward': reward } }
    myHistorycol.update_one(where, newvalues)

def generate_document(values, actions, total_reward, reward):
    document = {"timestamp": round(time.time()),
                "Temp": float(values["Temp"]),
                "RH": float(values["RH"]),
                "Soil_Moisture": float(values["Soil_Moisture"]),
                "LUX_Index": float(values["LUX_Index"]),
                "actions": actions,
                "total reward": total_reward,
                "reward": reward
                }
    print(f"Document to send: {document}")
    return document

if __name__ == "__main__":
    hist = {'timestamp': 1646743350, 'Temp': 27.772499999999997, 'RH': 70.31083333333333, 'Soil_Moisture': 0.0, 'LUX_Index': 2423.75, 'action': OrderedDict([('AC', 0), ('heater', 0), ('humidifier', 0), ('irrigation', 0), ('light', 0), ('ventilation', 0)]), 'total reward': 0, 'reward': 0}
    get_avg()