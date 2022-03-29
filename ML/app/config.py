from pydantic import BaseSettings
import os

class CommonSettings(BaseSettings):
    APP_NAME: str = ""
    DEBUG_MODE: bool = True

class DatabaseSettings(BaseSettings):
    #Docker run have argument to create this env var from one file
    DB_URL: str = os.environ['DB_URL'] if "DB_URL" in os.environ else "localhost:27017"
    DB_NAME: str = "GreenHouse"
    DB_VALUES_COLL: str = "GreenHouse_Values"
    DB_HIST_COLL: str = "GreenHouse_History"

class GreenhouseSettings(BaseSettings):
    TEMP_THRESHOLD: float = 28
    RH_THRESHOLD: float = 70
    MOOISTURE_THRESHOLD: float = 60
    LUX_THRESHOLD: float = 5000

class Settings(CommonSettings, DatabaseSettings, GreenhouseSettings):
    pass

settings = Settings()