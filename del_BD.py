import pymongo

client = pymongo.MongoClient("localhost:27017")
db = client["GreenHouse"]
coll = db["GreenHouse_Values"]
coll.delete_many({})
coll = db["GreenHouse_History"]
coll.delete_many({})

