from pydantic import BaseSettings
import os

class CommonSettings(BaseSettings):
    APP_NAME: str = ""
    DEBUG_MODE: bool = True

class ServerSettings(BaseSettings):
    HOST: str = "0.0.0.0"
    PORT: int = 8000

class DatabaseSettings(BaseSettings):
    #Docker run have argument to create this env var from one file
    DB_URL: str = os.environ['DB_URL'] if "DB_URL" in os.environ else "localhost:27017"
    DB_NAME: str = "GreenHouse"
    DB_COLL: str = "GreenHouse_Values"

class Settings(CommonSettings, ServerSettings, DatabaseSettings):
    pass

settings = Settings()